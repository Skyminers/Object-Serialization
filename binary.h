
#ifndef BINARY_H
#define BINARY_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
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
    throw string("错误的传入类型，无法识别");
}

template<typename T>
void serialize(T data, std::string name){
    try{
        getTypeId<T>();
    }catch(string s){
        std::cerr << s << std::endl;
        return ;
    }

}

}

#endif