# Object-Serialization

> 面向对象程序设计 大作业

* binary serialization 
* XML serialization

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

## 详细编码方式

### 二进制位：
01 : 表示是那个类型
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
        12 - long double  80位

    8  位
    16 位
    32 位
    64 位
    80 位

### **容器**:
* std::string
* std::pair
* std::vector
* std::list
* std::map

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

### **自定义**:
* struct

自定义一个对象

struct{
    基础数据类型 各3个
    容器类型 各1个
}

共 36 个基础对象
和 5 个容器

这部分分工：
    * cc : 浮点数，数值与IEEE-754二进制码转化；自定义对象
    * lyc : 基础数据类型，容器；



