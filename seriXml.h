
#ifndef SERIXML_H
#define SERIXML_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include "defineList.h"
#include "tinyxml2.h"
#include "typeJudger.h"

// 由于该模块包含大量template模版，导致无法分为.h与.cpp文件

namespace xml{

tinyxml2::XMLDocument doc;

template<typename T>
void getValueFrom(T &data, int Tid,tinyxml2::XMLElement *p,std::string s){
    switch(Tid){ // 根据Tid返回对应的类型
        case charID:  data =  (char)p->IntAttribute(s.c_str()); break;
        case uncharID: data =  (unsigned char)p->IntAttribute(s.c_str()); break;
        case shortID: data =  (short)p->IntAttribute(s.c_str()); break;
        case unshortID: data =  (unsigned short)p->IntAttribute(s.c_str()); break;
        case intID: data =  (int)p->IntAttribute(s.c_str()); break;
        case unintID: data =  (unsigned)p->IntAttribute(s.c_str()); break;
        case longID: data =  (long)p->IntAttribute(s.c_str()); break;
        case unlongID: data =  (unsigned long)p->IntAttribute(s.c_str()); break;
        case longlongID: data =  (long long)p->Int64Attribute(s.c_str()); break;
        case unlonglongID: data =  (unsigned long long)p->Unsigned64Attribute(s.c_str()); break;
        case floatID: data =  (float)p->FloatAttribute(s.c_str()); break;
        case doubleID: data =  (double)p->DoubleAttribute(s.c_str()); break;
        case longdoubleID: data =  (long double)p->LongDoubleAttribute(s.c_str()); break;
        default:
            throw std::string("rong Tid, no match type");
    }
}

template<typename T>
void __serializeAri(tinyxml2::XMLElement *root,T data){
    if(root == NULL) throw std::string("error:root pointer is NULL");
    int Tid = getTypeId<T>(); // 获取data的类型
    //std::cerr << "Tid = " << Tid << std::endl;
    if(Tid < charID || Tid > longdoubleID) throw std::string("undefined data type");
    // 获取定义类型，并且新建 xml 节点
    tinyxml2::XMLElement *p = doc.NewElement(getTypeName(Tid).c_str());
    p->SetAttribute("val",data); // 设置其属性值为 data
    root->InsertEndChild(p); // 插入该节点作为根节点的儿子
}

template<typename T>
void __deserializeAri(tinyxml2::XMLElement *root,T &data){
    if(root == NULL) throw std::string("error:root pointer is NULL");
    int Tid = getTypeId<T>(); // 获取data的类型
    if(Tid < charID || Tid > longdoubleID) throw std::string("undefined data type");
    // 获取类型名称，并且查询root中第一个符合条件的节点
    tinyxml2::XMLElement *p = root;
    if(std::string(root->Name()) != getTypeName(Tid)) // 判断是由于可能会直接将该数据节点指针传入
        p = root->FirstChildElement(getTypeName(Tid).c_str());
    if(p == NULL) throw std::string("cannot find this node");
    getValueFrom(data,Tid,p,"val");
    
}

template<typename T>
void serializeAri_xml(T data, std::string name){ // 序列化基础数据类型
    // 清空 xml 文档，并且写入声明
    doc.Parse("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>");
    // 定义根结点
    tinyxml2::XMLElement *p = doc.NewElement("serialization");
    doc.InsertEndChild(p); // 插入根结点
    try{
        __serializeAri(doc.RootElement(),data);
        // 保存 xml 文件
        if(doc.SaveFile(name.c_str())) throw std::string("failed to save file");
    }
    catch(std::string s){
        std::cerr << s << std::endl;
    }
}

template<class T>
void deserializeAri_xml(T &data, std::string name){ // 读取基础数据类型
    try{
        //读取xml文件
        if(doc.LoadFile(name.c_str())) throw std::string("failed to read file");
        __deserializeAri(doc.RootElement(),data);
    }catch(std::string s){
        std::cerr << s << std::endl;
    }catch(int x){
        if(x == ENDFLAG) std::cerr << "unexpected abortion" << std::endl;
    }
}

// 要求容器中只能包含基础数据类型否则会编译失败

void __serializeStl(tinyxml2::XMLElement *root, std::string data){ // 序列化STL容器 string
    if(root == NULL) throw std::string("error:root pointer is NULL");
    tinyxml2::XMLElement *p = doc.NewElement("std_string"); // 设置一级父节点
    p->SetAttribute("val",data.c_str());
    root->InsertEndChild(p);
}

void __deserializeStl(tinyxml2::XMLElement *root, std::string &data){ // 读取序列化STL容器 string
    if(root == NULL) throw std::string("error:root pointer is NULL");
    tinyxml2::XMLElement *p = root;
    // 该判断同__deserializeAri
    if(std::string(root->Name()) != std::string("std_string"))
        p = root->FirstChildElement("std_string"); // 找到 string 节点
    if(p == NULL) throw std::string("cannot find node matching string");
    data = p->Attribute("val");
}

template<typename T1, typename T2>
void __serializeStl(tinyxml2::XMLElement *root, std::pair<T1,T2> data){ // 序列化STL容器 pair
    if(root == NULL) throw std::string("error:root pointer is NULL");
    tinyxml2::XMLElement *rt = doc.NewElement("std_pair"); // 设置一级父节点
    root->InsertEndChild(rt);
    std::string typeName1 = getTypeName(getTypeId<T1>()); // 获取该pair的两个类型
    std::string typeName2 = getTypeName(getTypeId<T2>());
    tinyxml2::XMLElement *p1 = doc.NewElement(typeName1.c_str()); // 创建对应节点
    tinyxml2::XMLElement *p2 = doc.NewElement(typeName2.c_str());
    p1->SetAttribute("val",data.first); // 插入对应值
    p2->SetAttribute("val",data.second);
    rt->InsertEndChild(p1); // 插入对应节点
    rt->InsertEndChild(p2);
}

template<typename T1, typename T2>
void __deserializeStl(tinyxml2::XMLElement *root, std::pair<T1,T2> &data){ // 读取序列化STL容器 pair
    if(root == NULL) throw std::string("error:root pointer is NULL");
    tinyxml2::XMLElement *rt = root;
    // 该判断同__deserializeAri
    if(std::string(root->Name()) != std::string("std_pair"))
        rt = root->FirstChildElement("std_pair"); // 找到 pair 节点
    if(rt == NULL) throw std::string("cannot find node matching pair");
    std::string typeName1 = getTypeName(getTypeId<T1>()); // 获取该pair的两个类型
    std::string typeName2 = getTypeName(getTypeId<T2>());
    tinyxml2::XMLElement *p = rt->FirstChildElement(typeName1.c_str());
    if(p == NULL) throw std::string("cannot find first");
    getValueFrom(data.first,getTypeId<T1>(),p,"val");
    p = p->NextSiblingElement();
    if(p == NULL) throw std::string("cannot find second");
    getValueFrom(data.second,getTypeId<T2>(),p,"val");
}

template<typename T>
void __serializeStl(tinyxml2::XMLElement *root,std::vector<T> data){ // 序列化STL容器 vector
    if(root == NULL) throw std::string("error:root pointer is NULL");
    tinyxml2::XMLElement *rt = doc.NewElement("std_vector"); // 设置一级父节点
    root->InsertEndChild(rt);
    std::string typeName = getTypeName(getTypeId<T>());
    for(auto it = data.begin(); it != data.end(); ++ it){
        tinyxml2::XMLElement *p = doc.NewElement(typeName.c_str()); // 新建子节点
        p->SetAttribute("val",*it); // 将每个值的值储存在子节点当中
        // 插入到 std_vector 中
        rt->InsertEndChild(p);
    }
}

template<typename T>
void __deserializeStl(tinyxml2::XMLElement *root, std::vector<T> &data){ // 读取序列化STL容器 vector
    if(root == NULL) throw std::string("error:root pointer is NULL");
    tinyxml2::XMLElement *rt = root;
    // 该判断同__deserializeAri
    if(std::string(root->Name()) != std::string("std_vector"))
        rt = root->FirstChildElement("std_vector"); // 找到 vector 节点
    if(rt == NULL) throw std::string("cannot find node matching vector");
    int Tid;
    std::string typeName = getTypeName(Tid = getTypeId<T>());
    tinyxml2::XMLElement *p = rt->FirstChildElement(typeName.c_str()); // 找到 vector 节点内的元素
    data.clear(); // 清空 vector ， 准备储存数据
    T tmp;
    while(p != NULL){ // 循环处理每条数据
        getValueFrom(tmp,Tid,p,"val");
        data.push_back(tmp);
        p = p->NextSiblingElement(); // 下一个兄弟节点
    }
}

template<typename T>
void __serializeStl(tinyxml2::XMLElement *root, std::list<T> data){ // 序列化STL容器 list
    if(root == NULL) throw std::string("error:root pointer is NULL");
    tinyxml2::XMLElement *rt = doc.NewElement("std_list"); // 设置一级父节点
    root->InsertEndChild(rt);
    std::string typeName = getTypeName(getTypeId<T>());
    for(auto it = data.begin(); it != data.end(); ++ it){
        tinyxml2::XMLElement *p = doc.NewElement(typeName.c_str()); // 新建子节点
        p->SetAttribute("val",*it); // 将每个值的值储存在子节点当中
        // 插入到 std_list 中
        rt->InsertEndChild(p);
    }
}

template<typename T>
void __deserializeStl(tinyxml2::XMLElement *root,std::list<T> &data){ // 序列化STL容器 list
    if(root == NULL) throw std::string("error:root pointer is NULL");
    tinyxml2::XMLElement *rt = root;
    // 该判断同__deserializeAri
    if(std::string(root->Name()) != std::string("std_list"))
        rt = root->FirstChildElement("std_list"); // 找到 list 节点
    if(rt == NULL) throw std::string("cannot find node matching list");
    int Tid;
    std::string typeName = getTypeName(Tid = getTypeId<T>());
    tinyxml2::XMLElement *p = rt->FirstChildElement(typeName.c_str()); // 找到 list 节点内的元素
    data.clear(); // 清空 list ， 准备储存数据
    T tmp;
    while(p != NULL){ // 循环处理每条数据
        getValueFrom(tmp,Tid,p,"val");
        data.push_back(tmp);
        p = p->NextSiblingElement(); // 下一个兄弟节点
    }
}

template<typename T1, typename T2>
void __serializeStl(tinyxml2::XMLElement *root,std::map<T1,T2> data){ // 序列化STL容器 map
    if(root == NULL) throw std::string("error:root pointer is NULL");
    tinyxml2::XMLElement *rt = doc.NewElement("std_map"); // 设置一级父节点
    root->InsertEndChild(rt);
    for(auto it = data.begin(); it != data.end(); ++ it){
        tinyxml2::XMLElement *p = doc.NewElement("pair"); // 新建子节点
        // 将每个键值对放置于一个节点中，用 key-value 进行储存
        p->SetAttribute("key",it->first);
        p->SetAttribute("value",it->second);
        // 插入到 std_map 中
        rt->InsertEndChild(p);
    }
}

template<typename T1, typename T2>
void __deserializeStl(tinyxml2::XMLElement *root,std::map<T1,T2> &data){ // 读取序列化STL容器 map
    if(root == NULL) throw std::string("error:root pointer is NULL");
    tinyxml2::XMLElement *rt = root;
    // 该判断同__deserializeAri
    if(std::string(root->Name()) != std::string("std_map"))
        rt = root->FirstChildElement("std_map"); // 找到 string 节点
    if(rt == NULL) throw std::string("cannot find node matching map");
    tinyxml2::XMLElement *p = rt->FirstChildElement("pair"); // 找到 map 节点内的元素
    data.clear(); // 清空 map ， 准备储存数据
    int Tid1 = getTypeId<T1>(); T1 tmp1;
    int Tid2 = getTypeId<T2>(); T2 tmp2;
    while(p != NULL){ // 循环处理每条数据
        getValueFrom(tmp1,Tid1,p,"key");
        getValueFrom(tmp2,Tid2,p,"value");
        data[tmp1] = tmp2;
        p = p->NextSiblingElement(); // 下一个兄弟节点
    }
}


template<typename T>
void serializeStl_xml(T data, std::string name){ // 序列化容器
    // 清空 xml 文档，并且写入声明
    doc.Parse("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>");
    // 定义根结点
    tinyxml2::XMLElement *p = doc.NewElement("serialization");
    doc.InsertEndChild(p); // 插入根结点
    try{
        __serializeStl(doc.RootElement(),data );
        if(doc.SaveFile(name.c_str())) throw std::string("failed to write to the file");
    }
    catch(std::string s){
        std::cerr << s << std::endl;
    }
}

template<class T>
void deserializeStl_xml(T &data, std::string name){ // 读取容器
    try{
        //读取xml文件
        if(doc.LoadFile(name.c_str())) throw std::string("failed to read file");
        __deserializeStl(doc.RootElement(),data);
    }catch(std::string s){
        std::cerr << s << std::endl;
    }
}

}

#endif