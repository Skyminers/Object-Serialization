
#ifndef TYPEJUDGER_H
#define TYPEJUDGER_H

#include <string>
#include <iostream>

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
    throw std::string("wrong type");
}

std::string getTypeName(int Tid){
    switch(Tid){ // 根据Tid返回对应的类型
        case charID:  return "char";
        case uncharID: return "unsignedChar";
        case shortID: return "short";
        case unshortID: return "unsigedShort";
        case intID: return "int";
        case unintID: return "unsignedInt";
        case longID: return "long";
        case unlongID: return "unsignedLong";
        case longlongID: return "longLong";
        case unlonglongID: return "unsignedLongLong";
        case floatID: return "float";
        case doubleID: return "double";
        case longdoubleID: return "longDouble";
        default:
            throw std::string("wrong Tid, no match type");
    }
}

#endif