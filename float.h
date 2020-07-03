#ifndef FLOAT_H
#define FLOAT_H

#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

//编码函数
unsigned int floatToBinary( float );
unsigned long long doubleToBinary( double );
pair<long long, long long> longDoubleToBinary( long double );

//译码函数
float binaryToFloat ( int );
double binaryToDouble( long long);
long double binaryToLongDouble(pair<long long, long long> x);


#endif