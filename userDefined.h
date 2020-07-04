#ifndef USERDEFINED_H
#define USERDEFINED_H

#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <list>
#include <map>
#include "defineList.h"
#include "binary.h"
#include "tinyxml2.h"
#include "seriXml.h"

// 在此处 define USER_STRUCT 后即可在注释指定位置写入自定义内容
// #define USER_STRUCT

namespace userDef{

    //构建一个基础类，其他用户自定义类型都要赋值到它上才能进行转化
    struct BaseClass{
#ifndef USER_STRUCT
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
        std::vector<int> _vector_int;
        std::list<int> _list_int;
        std::map<int, int> _map_int;
#else
        // 此处可以写用户自定以的结构体内容
        // 需要与下面的内容相对应
#endif
    }Base1,Base2;
    void structToBinary(std::string name); // 序列化为binary
    void binaryToStruct(std::string name); // 读取binary的序列化
    void structToXml(std::string name); // 序列化为xml
    void xmlToStruct(std::string name); // 读取xml的序列化

void structToBinary(std::string name){
    binary::buf.clear(); // 清空缓存区，准备开始存放数据
    try{
#ifndef USER_STRUCT
        // 此处为已定义模版，用户可以直接使用该模版
        // 依次序列化每个成员
        binary::__serializeAri(Base1._char);
        binary::__serializeAri(Base1._uchar);
        binary::__serializeAri(Base1._short);
        binary::__serializeAri(Base1._ushort);
        binary::__serializeAri(Base1._int);
        binary::__serializeAri(Base1._uint);
        binary::__serializeAri(Base1._long);
        binary::__serializeAri(Base1._ulong);
        binary::__serializeAri(Base1._llong);
        binary::__serializeAri(Base1._ullong);
        binary::__serializeAri(Base1._float);
        binary::__serializeAri(Base1._double);
        binary::__serializeAri(Base1._ldouble);
        binary::__serializeStl(Base1._string);
        binary::__serializeStl(Base1._pair_int);
        binary::__serializeStl(Base1._vector_int);
        binary::__serializeStl(Base1._list_int);
        binary::__serializeStl(Base1._map_int);
#else
        // 此处为用户自定义模版实现部分
        // 由于C++语言的限制
        // 用户需要在此处按照上面模版格式来依次写入自定义的每个成员
        // 从而进行序列化
        // 示例: binary::__serializeAri(ClassName.variableName); (如果是基础数据类型)
        // binary::__serializeStl(ClassName.variableName); (如果是STL容器)
        
#endif
        binary::buf.printToFile(name); // 输出到数据文件中
    }
    catch(std::string s){
        std::cerr << s << std::endl;
    }
}

void binaryToStruct(std::string name){
    binary::buf.clear(); // 清空缓存区，准备开始存放数据
    binary::buf.readFromFile(name); // 读入 buf
    try{
#ifndef USER_STRUCT
        // 依次读取每个序列化成员，顺序与序列化顺序相同
        binary::__deserializeAri(Base2._char);
        binary::__deserializeAri(Base2._uchar);
        binary::__deserializeAri(Base2._short);
        binary::__deserializeAri(Base2._ushort);
        binary::__deserializeAri(Base2._int);
        binary::__deserializeAri(Base2._uint);
        binary::__deserializeAri(Base2._long);
        binary::__deserializeAri(Base2._ulong);
        binary::__deserializeAri(Base2._llong);
        binary::__deserializeAri(Base2._ullong);
        binary::__deserializeAri(Base2._float);
        binary::__deserializeAri(Base2._double);
        binary::__deserializeAri(Base2._ldouble);
        binary::__deserializeStl(Base2._string);
        binary::__deserializeStl(Base2._pair_int);
        binary::__deserializeStl(Base2._vector_int);
        binary::__deserializeStl(Base2._list_int);
        binary::__deserializeStl(Base2._map_int);
#else
    // 此处为用户自定义模版实现部分
    // 由于C++语言的限制
    // 用户需要在此处按照上面模版格式来依次写入自定义的每个成员
    // 从而进行序列化
    // 注：此处所填写的内容需要与序列化部分顺序完全一致，否则可能会出现错误
    // 示例: binary::__deserializeAri(ClassName.variableName); (如果是基础数据类型)
    // binary::__deserializeStl(ClassName.variableName); (如果是STL容器

#endif
    }catch(std::string s){
        std::cerr << s << std::endl;
    }catch(int x){
        if(x == ENDFLAG) std::cerr << "unexpected abortion" << std::endl;
    }
}

void structToXml(std::string name){
    // 清空 xml 文档，并且写入声明
    xml::doc.Parse("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>");
    // 定义根结点
    tinyxml2::XMLElement *p = xml::doc.NewElement("serialization");
    xml::doc.InsertEndChild(p); // 插入根结点
    tinyxml2::XMLElement *root = xml::doc.RootElement();
    try{
#ifndef USER_STRUCT
        // 此处为已定义模版，用户可以直接使用该模版
        // 依次序列化每个成员
        xml::__serializeAri(root,Base1._char);
        xml::__serializeAri(root,Base1._uchar);
        xml::__serializeAri(root,Base1._short);
        xml::__serializeAri(root,Base1._ushort);
        xml::__serializeAri(root,Base1._int);
        xml::__serializeAri(root,Base1._uint);
        xml::__serializeAri(root,Base1._long);
        xml::__serializeAri(root,Base1._ulong);
        xml::__serializeAri(root,Base1._llong);
        xml::__serializeAri(root,Base1._ullong);
        xml::__serializeAri(root,Base1._float);
        xml::__serializeAri(root,Base1._double);
        xml::__serializeAri(root,Base1._ldouble);
        xml::__serializeStl(root,Base1._string);
        xml::__serializeStl(root,Base1._pair_int);
        xml::__serializeStl(root,Base1._vector_int);
        xml::__serializeStl(root,Base1._list_int);
        xml::__serializeStl(root,Base1._map_int);
#else
        // 此处为用户自定义模版实现部分
        // 由于C++语言的限制
        // 用户需要在此处按照上面模版格式来依次写入自定义的每个成员
        // 从而进行序列化
        // 示例: xml::__serializeAri(root,ClassName.variableName); (如果是基础数据类型)
        // xml::__serializeStl(root,ClassName.variableName); (如果是STL容器)

#endif
        if(xml::doc.SaveFile(name.c_str())) throw std::string("failed to write data");
    }
    catch(std::string s){
        std::cerr << s << std::endl;
    }
}

template<typename T>
inline void deseriXmlAri(tinyxml2::XMLElement* &p, T &x){
    if(p == NULL) throw std::string("error:p is NULL");
    xml::__deserializeAri(p,x);
    p=p->NextSiblingElement();
}

template<typename T>
inline void deseriXmlStl(tinyxml2::XMLElement* &p, T &x){
    if(p == NULL) throw std::string("error:p is NULL");
    xml::__deserializeStl(p,x);
    p=p->NextSiblingElement();
}

void xmlToStruct(std::string name){
    try{
        //读取xml文件
        if(xml::doc.LoadFile(name.c_str())) throw std::string("failed to read text");
        tinyxml2::XMLElement *root = xml::doc.RootElement();
        tinyxml2::XMLElement *p = root->FirstChildElement();
#ifndef USER_STRUCT
        // 此处为已定义模版，用户可以直接使用该模版
        // 此处顺序与序列化顺序相同
        deseriXmlAri(p,Base2._char);
        deseriXmlAri(p,Base2._uchar);
        deseriXmlAri(p,Base2._short);
        deseriXmlAri(p,Base2._ushort);
        deseriXmlAri(p,Base2._int);
        deseriXmlAri(p,Base2._uint);
        deseriXmlAri(p,Base2._long);
        deseriXmlAri(p,Base2._ulong);
        deseriXmlAri(p,Base2._llong);
        deseriXmlAri(p,Base2._ullong);
        deseriXmlAri(p,Base2._float);
        deseriXmlAri(p,Base2._double);
        deseriXmlAri(p,Base2._ldouble);
        deseriXmlStl(p,Base2._string);
        deseriXmlStl(p,Base2._pair_int);
        deseriXmlStl(p,Base2._vector_int);
        deseriXmlStl(p,Base2._list_int);
        deseriXmlStl(p,Base2._map_int);
#else
        // 此处为用户自定义模版实现部分
        // 由于C++语言的限制
        // 用户需要在此处按照上面模版格式来依次写入自定义的每个成员
        // 从而进行序列化
        // 示例: deseriXmlAri(p,ClassName.variableName); (如果是基础数据类型)
        // deseriXmlStl(p,ClassName.variableName); (如果是STL容器)

#endif
        //__deserializeStl(doc.RootElement(),data);
    }catch(std::string s){
        std::cerr << s << std::endl;
    }
}
}

#endif