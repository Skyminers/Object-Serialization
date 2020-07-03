#ifndef USERDEFINED_H
#define USERDEFINED_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <list>
#include <map>
#include "defineList.h"
#include "buffer.h"

namespace userDefined{
    using namespace std;
    //构建一个基础类，其他用户自定义类型都要赋值到它上才能进行转化
    struct userDefined{

        //基础数据类型
    	char _char;
    	unsigned char _uchar;

        short _short;
        unsigned short _ushort;

        int _int;
        unsigned int _uint;

        long _long;
        unsigned long _ulong;

        long long _llong;
        unsigned long long _ullong;

        float _float;
        double _double;
        long double _ldouble;

        //模板数据类型
        std::string _string;
        std::pair<int, int> _pair_int;
        std::vector<int> _vetor_int;
        std::list<int> _list_int;
        std::map<int, int> _map_int;

        userDefined();
        void structToBinary();
        void BinaryToStruct();
    };
    
}

#endif