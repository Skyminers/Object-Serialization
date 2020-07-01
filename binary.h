
#ifndef BINARY_H
#define BINARY_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "defineList.h"

namespace binary{

// 下面的模块用于类型判断
template<typename T1, typename T2>// 不相同类型进入此模块
struct typeSame{operator bool(){return false;}};

template<typename T1> // 相同类型进入此模块
struct typeSame<T1, T1>{operator bool(){return true;}};

template<typename T>
int getTypeId(){ // 该函数返回 T 的类型 ID
    if(typeSame<T,char>()) return charID;
    if(typeSame<T,unsigned char>()) return uncharID;
    if(typeSame<T,short>()) return shortID;
    if(typeSame<T,unsigned short>())return unshortID;
    if(typeSame<T,int>()) return intID;
    if(typeSame<T,unsigned int>()) return unintID;
    if(typeSame<T,long>()) return longID;
    if(typeSame<T,unsigned long>()) return unlongID;
    if(typeSame<T,long long>()) return longlongID;
    if(typeSame<T,unsigned long long >()) return unlonglongID;
    if(typeSame<T,float>()) return floatID;
    if(typeSame<T,double>()) return doubleID;
    if(typeSame<T,long double>()) return longdoubleID;
    throw std::string("错误的传入类型，无法识别");
}

char buf[256]; // 文件IO缓冲
int p ; // 辅助缓冲的指针 p

void readFromFile(std::string fileName){// 该函数从文件中读入数据
    FILE* in = fopen(fileName.c_str(),"rb"); // 打开文件
    if(!in) throw std::string("文件打开失败");
    // 读入2048位二进制
    fread(buf,sizeof(char),sizeof(char)*256,in);
    fclose(in);
}

void printToFile(std::string fileName){// 与上个函数类似，该函数输出到文件
    FILE* out = fopen(fileName.c_str(),"wb");
    if(!out) throw std::string("文件创建/写入失败");
    fwrite(buf,sizeof(char),sizeof(char)*256,out);
    fclose(out);
}

unsigned long long getNextN(int n){ // 获取二进制文件中由[p..p+n)部分组成的数字
    if(p+n >= 256) throw std::string("获取字符越界");
    if(n > 64) throw std::string("获取范围过大，最多获取64位");
    unsigned long long ret = 0;
    // 假设顺序为 buf[0] 0 - 7 , buf[1] 0 - 7
    for(int i=0;i<n;++p,++i){
        //std::cerr << "get " << p << " is " << ((buf[p/8] >> p%8) & 1) << std::endl;
        ret = (ret << 1) | ((buf[p/8] >> (p%8)) & 1);
    }
    return ret;
}

inline void setNext(bool val){// 该函数用于对单点进行赋值
    //std::cerr << "set " << p << " with " << val << std::endl;
    if(val) buf[p/8] |= (1<<(p%8));
    else buf[p/8] &= ~(1<<(p%8));
    ++ p;
}
template<typename T>
inline void setNBits(int n,T data){ // 将data中的低n个bit输出到buf中
    while(n) setNext((data >> --n)&1 );
}

inline void clearBuf(){ // 清空buf
    for(int i=0;i<256;++i) buf[i] = 0;
    p = 0;
}

template<typename T>
void ariSeria(int id, T data, std::string name){ // 序列化基础数据
    setNext(0);setNext(0); // 设置格式首两位为基础数据类型
    setNBits(4,id); // 设置格式后四位为具体数据类型
    switch(id){ // 根据不同数据类型选用数据存放所使用的位数
        case charID: case uncharID:
            setNBits(8, data); // 8 位数据选用 8位存放
            break;
        case shortID: case unshortID:
            setNBits(16,data); // 16 位数据选用 16位存放
            break;
        case intID: case unintID: case longID: case unlongID:
            setNBits(32,data); // 32 位数据选用 32位存放
            break;
        case longlongID: case unlonglongID:
            setNBits(64,data); // 64 位数据选用 64位存放
            break;
        case floatID: // 等待对接模块的完成
        case doubleID:
        case longdoubleID:
            break;
    }
    // 至此，缓冲区数据完整
    try{
        printToFile(name); // 输出到数据文件中
    }catch(std::string s){
        throw s;
    }
}

template<typename T>
void stlSeria(int id, T data, std::string name){

}

template<typename T>
void deAriSeria(int id,T &data){
    switch(id){ // 该switch语句根据数据的位数，决定接下来取多少位
        case charID: case uncharID:
            data = getNextN(8);
            break;
        case shortID: case unshortID:
            data = getNextN(16);
            break;
        case intID: case unintID: case longID: case unlongID:
            data = getNextN(32);
            break;
        case longlongID: case unlonglongID:
            data = getNextN(64);
            break;
        case floatID: // 等待对接模块完成
        case doubleID:
        case longdoubleID:
            break;
    }
}

template<typename T>
void deStlSeria(int id,T &data){

}

template<typename T>
void serialize(T data, std::string name){
    clearBuf(); // 清空缓存区，准备开始存放数据
    int Tid;
    try{
        Tid = getTypeId<T>(); // 获取data的类型
        //std::cerr << "Tid = " << Tid << std::endl;
    }catch(std::string s){
        std::cerr << s << std::endl;
        return ;
    }
    try{
        if(Tid <= unlonglongID) ariSeria(Tid, data, name); // 基础数据类型函数
        else if(Tid <= mapID) stlSeria(Tid, data, name); // 容器处理函数
        else throw std::string("未定义的数据类型");
    }catch(std::string s){
        std::cerr << s << std::endl;
    }
}

template<typename T>
void desetialize(T &data, std::string name){
    clearBuf(); // 清空缓存区，准备开始存放数据
    int Tid;
    try{
        Tid = getTypeId<T>(); // 获取data的类型
        readFromFile(name);
    }catch(std::string s){
        std::cerr << s << std::endl;
        return ;
    }
    int fid = getNextN(2); // 获取数据分类id
    try{
        if(Tid != getNextN(4)) throw std::string("传入数据类型与文件中数据类型不符");
        if(Tid <= unlonglongID) deAriSeria(Tid, data); // 解码基础数据
        else if(Tid <= mapID) deStlSeria(Tid, data); // 解码容器
        else throw std::string("未知的错误");
    }catch(std::string s){
        std::cerr << s << std::endl;
    }

}

}

#endif