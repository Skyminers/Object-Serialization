#ifndef FLOAT_H
#define FLOAT_H

#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

//编码函数：浮点数转化成二进制码

//单精度浮点数转化成32位 IEEE-754编码
unsigned int floatToBinary( float );

//双精度浮点数转化成64位 IEEE-754编码
//精度范围：小数点后15位
unsigned long long doubleToBinary( double );

//long double浮点数转化成80位 IEEE-754编码
//first的第16位+second
//精度范围：小数点后19位
pair<unsigned long long,unsigned long long> longDoubleToBinary( long double );

//译码函数：二进制码转化成浮点数

//精度范围：小数点后6位
float binaryToFloat ( unsigned  int );

//精度范围：小数点后15位
double binaryToDouble(unsigned long long);

//精度范围：小数点后19位
long double binaryToLongDouble(pair<unsigned long long,unsigned long long> x);


#endif