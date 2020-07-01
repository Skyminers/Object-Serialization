
#ifndef BINARY_H
#define BINARY_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "defineList.h"
#include "buffer.h"

namespace binary{

Buffer buf;

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

template<typename T>
void ariSeria(int id, T data, std::string name){ // 序列化基础数据
    buf.setNext(0);buf.setNext(0); // 设置格式首两位为基础数据类型
    buf.setNBits(4,id); // 设置格式后四位为具体数据类型
    switch(id){ // 根据不同数据类型选用数据存放所使用的位数
        case charID: case uncharID:
            buf.setNBits(8, data); // 8 位数据选用 8位存放
            break;
        case shortID: case unshortID:
            buf.setNBits(16,data); // 16 位数据选用 16位存放
            break;
        case intID: case unintID: case longID: case unlongID:
            buf.setNBits(32,data); // 32 位数据选用 32位存放
            break;
        case longlongID: case unlonglongID:
            buf.setNBits(64,data); // 64 位数据选用 64位存放
            break;
        case floatID: // 等待对接模块的完成
        case doubleID:
        case longdoubleID:
            break;
    }
    // 至此，缓冲区数据完整
}

template<typename T>
void stlSeria(int id, T data, std::string name){
    
}

template<typename T>
void deAriSeria(int id,T &data){
    switch(id){ // 该switch语句根据数据的位数，决定接下来取多少位
        case charID: case uncharID:
            data = buf.getNextN(8);
            break;
        case shortID: case unshortID:
            data = buf.getNextN(16);
            break;
        case intID: case unintID: case longID: case unlongID:
            data = buf.getNextN(32);
            break;
        case longlongID: case unlonglongID:
            data = buf.getNextN(64);
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
void __serialize(T data, std::string name){
    int Tid = getTypeId<T>(); // 获取data的类型
    //std::cerr << "Tid = " << Tid << std::endl;
    if(Tid <= unlonglongID) ariSeria(Tid, data, name); // 基础数据类型函数
    else if(Tid <= mapID) stlSeria(Tid, data, name); // 容器处理函数
    else throw std::string("未定义的数据类型");
}

template<typename T>
void __desetialize(T &data, std::string name){
    int Tid = getTypeId<T>(); // 获取data的类型
    buf.readFromFile(name); // 读入 buf
    int fid = buf.getNextN(2); // 获取数据分类id
    
    if(Tid != buf.getNextN(4)) throw std::string("传入数据类型与文件中数据类型不符");
    
    if(Tid <= unlonglongID) deAriSeria(Tid, data); // 解码基础数据
    else if(Tid <= mapID) deStlSeria(Tid, data); // 解码容器
    else throw std::string("未知的错误");
}

template<typename T>
void serialize(T data, std::string name){
    buf.clear(); // 清空缓存区，准备开始存放数据
    try{
        __serialize(data, name);
        buf.printToFile(name); // 输出到数据文件中
    }
    catch(std::string s){
        std::cerr << s << std::endl;
    }
}

template<typename T>
void desetialize(T &data, std::string name){
    buf.clear(); // 清空缓存区，准备开始存放数据
    try{
        __desetialize(data, name);
    }catch(std::string s){
        std::cerr << s << std::endl;
    }
}

}

#endif