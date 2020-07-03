#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <list>
#include <map>
#include "defineList.h"
#include "binary.h"
#include "buffer.h"
#include "userDefined.h"

using namespace binary;
using namespace userDefined;
void structToBinary(std::string name){
    buf.clear(); // 清空缓存区，准备开始存放数据
    try{
        __serializeAri(Base._char);
        __serializeAri(Base._uchar);
        __serializeAri(Base._short);
        __serializeAri(Base._ushort);
        __serializeAri(Base._int);
        __serializeAri(Base._uint);
        __serializeAri(Base._long);
        __serializeAri(Base._ulong);
        __serializeAri(Base._llong);
        __serializeAri(Base._ullong);
        __serializeAri(Base._float);
        __serializeAri(Base._double);
        __serializeAri(Base._ldouble);
        __serializeStl(Base._string);
        __serializeStl(Base._pair_int);
        __serializeStl(Base._vector_int);
        __serializeStl(Base._list_int);
        __serializeStl(Base._map_int);
        buf.printToFile(name); // 输出到数据文件中
    }
    catch(std::string s){
        std::cerr << s << std::endl;
    }
}
void BinaryToStruct(std::string name){
    buf.clear(); // 清空缓存区，准备开始存放数据
    buf.readFromFile(name); // 读入 buf
    try{
        __desetializeAri(Base._char);
        __desetializeAri(Base._uchar);
        __desetializeAri(Base._short);
        __desetializeAri(Base._ushort);
        __desetializeAri(Base._int);
        __desetializeAri(Base._uint);
        __desetializeAri(Base._long);
        __desetializeAri(Base._ulong);
        __desetializeAri(Base._llong);
        __desetializeAri(Base._ullong);
        __desetializeAri(Base._float);
        __desetializeAri(Base._double);
        __desetializeAri(Base._ldouble);
        __deserializeStl(Base._string);
        __deserializeStl(Base._pair_int);
        __deserializeStl(Base._vector_int);
        __deserializeStl(Base._list_int);
        __deserializeStl(Base._map_int);
    }catch(std::string s){
        std::cerr << s << std::endl;
    }catch(int x){
        if(x == ENDFLAG) std::cerr << "意外终止" << std::endl;
    }
}