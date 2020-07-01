
#ifndef BINARY_H
#define BINARY_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <list>
#include <map>
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
void __serializeAri(T data){
    int Tid = getTypeId<T>(); // 获取data的类型
    //std::cerr << "Tid = " << Tid << std::endl;
    if(Tid < charID || Tid > unlonglongID) throw std::string("不符合定义的数据类型");

    buf.setNext(0);buf.setNext(0); // 设置格式首两位为基础数据类型
    buf.setNBits(4,Tid); // 设置格式后四位为具体数据类型
    switch(Tid){ // 根据不同数据类型选用数据存放所使用的位数
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
void __desetializeAri(T &data){
    int Tid = getTypeId<T>(); // 获取data的类型
    int fid = buf.getNextN(2); // 获取数据分类id
    if(fid == 3) throw ENDFLAG;
    if(fid != 0) throw std::string("错误的数据分类");
    if(Tid != buf.getNextN(4)) throw std::string("传入数据类型与文件中数据类型不符");
    
    if(Tid < charID || Tid > unlonglongID) throw std::string("不符合定义的数据类型");
    switch(Tid){ // 该switch语句根据数据的位数，决定接下来取多少位
        case charID: case uncharID:
            data = buf.getNextN(8); // 8 位
            break;
        case shortID: case unshortID:
            data = buf.getNextN(16); // 16 位
            break;
        case intID: case unintID: case longID: case unlongID:
            data = buf.getNextN(32); // 32 位
            break;
        case longlongID: case unlonglongID:
            data = buf.getNextN(64); // 64 位
            break;
        case floatID: // 等待对接模块完成
        case doubleID:
        case longdoubleID:
            break;
    }
}

template<typename T>
void serializeAri(T data, std::string name){ // 序列化基础数据类型
    buf.clear(); // 清空缓存区，准备开始存放数据
    try{
        __serializeAri(data);
        buf.printToFile(name); // 输出到数据文件中
    }
    catch(std::string s){
        std::cerr << s << std::endl;
    }
}

template<class T>
void desetializeAri(T &data, std::string name){ // 读取基础数据类型
    buf.clear(); // 清空缓存区，准备开始存放数据
    buf.readFromFile(name); // 读入 buf
    try{
        __desetializeAri(data);
    }catch(std::string s){
        std::cerr << s << std::endl;
    }catch(int x){
        if(x == ENDFLAG) std::cerr << "意外终止" << std::endl;
    }
}

// 要求容器中只能包含基础数据类型否则会编译失败

void __serializeStl(std::string data){ // 序列化STL容器 string
    buf.setNext(0);buf.setNext(1); // 设置格式首两位为容器类型
    buf.setNBits(4,stringID-stringID);// 将相对应的ID进行设置
    auto it = data.begin();
    for(auto it = data.begin();it != data.end(); ++ it)
        __serializeAri(*it); // 依次序列化每个元素
    buf.setNext(1);buf.setNext(1); // 不定长容器结束标志
}

void __deserializeStl(std::string &data){ // 读取序列化STL容器 string
    if(buf.getNextN(2) != 1) throw std::string("错误的数据种类");
    if(buf.getNextN(4) != stringID-stringID) throw std::string("错误的数据类型");
    data.clear(); // 清空 string
    char tmp;
    try{ // 利用 try catch 结构进行边界判定
        while(1){
            __desetializeAri(tmp); // 读入到结束标志时会抛出 ENDFLAG
            data += tmp; // 依次读取序列化数据，并且组合
        }
    }catch(int x){
        if(x == ENDFLAG) return ;
        else std::cerr << "未知的错误" << std::endl;
    }catch(std::string s){
        std::cerr << s << std::endl;
    }
}

template<typename T1, typename T2>
void __serializeStl(std::pair<T1,T2> data){ // 序列化STL容器 pair
    buf.setNext(0);buf.setNext(1); // 设置格式首两位为容器类型
    buf.setNBits(4,pairID-stringID);// 将相对应的ID进行设置
    // 依次序列化两个元素
    __serializeAri(data.first);  
    __serializeAri(data.second); 
}

template<typename T1, typename T2>
void __deserializeStl(std::pair<T1,T2> &data){ // 读取序列化STL容器 pair
    if(buf.getNextN(2) != 1) throw std::string("错误的数据种类");
    if(buf.getNextN(4) != pairID-stringID) throw std::string("错误的数据类型");
    __desetializeAri(data.first); // 依次读取两个序列化数据
    __desetializeAri(data.second);
}

template<typename T>
void __serializeStl(std::vector<T> data){ // 序列化STL容器 vector
    buf.setNext(0);buf.setNext(1); // 设置为容器类型
    buf.setNBits(4,vectorID-stringID);  // 设置对应ID
    for(auto it = data.begin();it != data.end(); ++ it)
        __serializeAri(*it); // 依次遍历元素并序列化
    buf.setNext(1);buf.setNext(1); // 设置终止标记
}

template<typename T>
void __deserializeStl(std::vector<T> &data){ // 读取序列化STL容器 vector
    if(buf.getNextN(2) != 1) throw std::string("错误的数据种类");
    if(buf.getNextN(4) != vectorID-stringID) throw std::string("错误的数据类型");
    data.clear(); // 清空 vector
    T tmp;
    try{ // 利用 try catch 结构进行边界判定
        while(1){
            __desetializeAri(tmp); // 读入到结束标志时会抛出 ENDFLAG
            data.push_back(tmp); // 依次读取序列化数据，并且组合
        }
    }catch(int x){
        if(x == ENDFLAG) return ;
        else std::cerr << "未知的错误" << std::endl;
    }catch(std::string s){
        std::cerr << s << std::endl;
    }
}

template<typename T>
void __serializeStl(std::list<T> data){ // 序列化STL容器 list
    buf.setNext(0);buf.setNext(1); // 设置为容器类型
    buf.setNBits(4,listID-stringID);     // 设置对应ID
    for(auto it = data.begin();it != data.end(); ++ it)
        __serializeAri(*it); // 依次遍历元素并序列化
    buf.setNext(1);buf.setNext(1); // 设置终止标记
}

template<typename T>
void __deserializeStl(std::list<T> &data){ // 序列化STL容器 list
    if(buf.getNextN(2) != 1) throw std::string("错误的数据种类");
    if(buf.getNextN(4) != listID-stringID) throw std::string("错误的数据类型");
    data.clear(); // 清空 list
    T tmp;
    try{ // 利用 try catch 结构进行边界判定
        while(1){
            __desetializeAri(tmp); // 读入到结束标志时会抛出 ENDFLAG
            data.push_back(tmp); // 依次读取序列化数据，并且组合
        }
    }catch(int x){
        if(x == ENDFLAG) return ;
        else std::cerr << "未知的错误" << std::endl;
    }catch(std::string s){
        std::cerr << s << std::endl;
    }
}

template<typename T1, typename T2>
void __serializeStl(std::map<T1,T2> data){ // 序列化STL容器 map
    buf.setNext(0);buf.setNext(1); // 设置为容器类型
    buf.setNBits(4,mapID-stringID);        // 设置对应ID
    for(auto it = data.begin(); it != data.end(); ++ it){
        __serializeAri(it->first); // 依次遍历元素并序列化每一对 key-value
        __serializeAri(it->second);
    }
    buf.setNext(1);buf.setNext(1); // 设置终止标记
}

template<typename T1, typename T2>
void __deserializeStl(std::map<T1,T2> &data){ // 读取序列化STL容器 map
    if(buf.getNextN(2) != 1) throw std::string("错误的数据种类");
    if(buf.getNextN(4) != mapID-stringID) throw std::string("错误的数据类型");
    data.clear();
    T1 x; T2 y;
    try{ // 利用 try catch 结构进行边界判定
        while(1){
            __desetializeAri(x); // 读入到结束标志时会抛出 ENDFLAG
            __desetializeAri(y); // 读入到结束标志时会抛出 ENDFLAG
            data[x] = y; // 依次读取序列化数据，并且组合
        }
    }catch(int x){
        if(x == ENDFLAG) return ;
        else std::cerr << "未知的错误" << std::endl;
    }catch(std::string s){
        std::cerr << s << std::endl;
    }
}


template<typename T>
void serializeStl(T data, std::string name){ // 序列化容器
    buf.clear(); // 清空缓存区，准备开始存放数据
    try{
        __serializeStl(data);
        buf.printToFile(name); // 输出到数据文件中
    }
    catch(std::string s){
        std::cerr << s << std::endl;
    }
}

template<class T>
void deserializeStl(T &data, std::string name){ // 读取容器
    buf.clear(); // 清空缓存区，准备开始存放数据
    buf.readFromFile(name); // 读入 buf
    try{
        __deserializeStl(data);
    }catch(std::string s){
        std::cerr << s << std::endl;
    }
}

}

#endif