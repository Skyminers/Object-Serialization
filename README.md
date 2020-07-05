# Object-Serialization

> 面向对象程序设计 大作业

* binary serialization 
* XML serialization

## 文件结构

![源文件调用结构](https://i.loli.net/2020/07/04/aKDNeRYFgUChifn.png)

* main.cpp : 主函数，用于测试
* binary.h : 包含命名空间 binary, 包含了序列化为二进制串以及读取二进制序列化的函数 (由于该文件大量函数使用了template导致无法将定义与实现分开，所以便全部写在了一个文件中)
* seriXml.h: 包含命名空间 xml ,包含了序列化为xml以及读取序列化xml的函数 (由于该文件大量函数使用了template导致无法将定义与实现分开，所以便全部写在了一个文件中)
* buffer.h & buffer.cpp : 缓冲区管理，主要为binary序列化提供支持，封装了关于二进制串输出到文件的功能，简化binary.h代码
* float.h & float.cpp : IEEE-754编码支持，可以将浮点数在IEEE-754编码与浮点表示之间转化，便于储存浮点数的二进制
* defineList.h : 包含一些常量的定义，主要是对不同类型的编号
* typeJudger.h : 该文件封装对于变量类型的判断的函数
* userDefined.h : 该文件提供了对于用户自定义struct的序列化的支持
* tinyxml2.h & tinyxml2.cpp : 提供了关于xml文件的创建、编辑、查询、保存的功能.
* test.h & test.cpp : 实现整个工程的测试，包含基础数据类型、容器类型、用户自定义类型的两种序列化(二进制与xml)
* base64.h & base64.cpp : 实现将xml文件用base64编码在解密，编码后的文件存储在encode_data.txt中，解密后的文件存储在decode_data.xml中

序列化支持下列

**基础数据类型**：
* char,
* short, int, long, long long
* float, double, long double
* 13个数据类型
**容器**:
* std::string
* std::pair
* std::vector
* std::list
* std::map

**自定义**:
* struct

## binary详细编码方式

### 二进制位：
前两个二进制位表示数据种类
* 00 : 基础数据类型
* 01 : 容器
* 10 : 自定义
* 11 : 未定义 - （在容器中用于结束条件判定）

### 基础数据类型：
    拿出4位二进制, 表示数据类型
        0,1 - char, un       8位
        2,3 - short, un      16位
        4,5 - int, un        32位
        6,7 - long, un       32
        8,9 - long long, un  64位

        10 - float        32位
        11 - double       64位
        12 - long double  80位 (16, 64)

    8  位
    16 位
    32 位
    64 位
    80 位

### **容器**:
* std::string 13  0
* std::pair   14  1
* std::vector 15  2
* std::list   16  3
* std::map    17  4

容器：
    5 种容器
    3位二进制:
    000 : string
        8位 - unit
        从头到尾进行编码
        当读入到未定义类型时，终止
    001 : pair
        xx 位 - 第一个
        xx 位 - 第二个
    010 : vector
        不做特殊化
        从头到尾进行编码
        当读入到未定义类型时，终止
    011 : list
        从头到尾进行编码
        当读入到未定义类型时，终止
    100 : map
        以随意顺序进行编码
        当读入到为定义类型时，终止


## xml详细编码方式

xml 的编码方式简单很多，主要是tinyxml2的使用

根结点使用 <serialization> ，用作标示，不起实际用处
随后如果是基础数据类型或std::string，那么直接添加 <type val="">的标签来保存数值，如:
    <double val="22.33">、<std_string val="2233">

如果是容器并且不是string，那么首先添加一个节点标示这个容器，随后在容器中添加儿子节点

<std_pair>
    <int val="1">       // first
    <double val="33">   // second
</std_pair>

也即儿子节点的顺序是有意义的

<std_vector>
    <int val="1">
    <int val="333">
    <int val="0>
</std_vector>

<std_map>
    <pair key="233" value="666">
    <pair key="666" value="233">
</std_map>

## 自定义的编码方式

* struct

**由于C++语言的限制，我们无法通过一个实例遍历来一个struct的所有成员**
**所以我们选择了一些替代法**

定义一个尽量含有所有类型的struct
同时给出模版以及函数留出空地
用户可以选择:
    * 直接在给出的struct中填写自己所使用的变量，随之将其序列化
    * 按照注释的提示，并且参照模版的写法，完成函数中留给用户填写的模块，进行序列化

自定义编码调用已经完成的序列化函数，对于binary模块，直接按顺序序列化按顺序读取
至于xml由于其是树状结构，我们选择在二级节点处线性存储，如下：

<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<serialization>
    <char val="122"/>
    <unsignedChar val="0"/>
    <short val="0"/>
    <unsigedShort val="0"/>
    <int val="0"/>
    <unsignedInt val="0"/>
    <long val="0"/>
    <unsignedLong val="0"/>
    <longLong val="0"/>
    <unsignedLongLong val="0"/>
    <float val="0"/>
    <double val="2020.0201999999999"/>
    <longDouble val="0"/>
    <std_string val=""/>
    <std_pair>
        <int val="0"/>
        <int val="0"/>
    </std_pair>
    <std_vector>
        <int val="10"/>
        <int val="22"/>
    </std_vector>
    <std_list/>
    <std_map/>
</serialization>

## base64编码方式

*编码过程
每次读取待编码文件的3个字节，共24bits
每隔6bits插入2个bits的0， 扩充成32bits
根据base64表，转换成4个相应的字符
如果文件末尾不足3个字节，用padding字符'='进行填充

*解码过程
每次读取待解码文件的4个字节，忽略掉填充字符'='
将这4个字符，经base64查找到它们的索引，共32bits
去除掉每个字节的最高2位，将32bits转换为24bits
再将这24bits划分为3个字节，变成3个字符
