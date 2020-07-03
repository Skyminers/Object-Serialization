#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cmath>
#include "float.h"
#define BASE_32 126
#define BASE_64 1022
#define BASE_80 16382

using namespace std;
//把float类型转化成IEEE-745的二进制编码
unsigned int floatToBinary( float x ){
	unsigned int res = 0;
    //符号位,当浮点数为负数是置1，否则置0
    bool sign = false;
    if(x < 0)   sign = true;
    
    unsigned int exp;  //指数 8bits
    unsigned int fra;   //底数 23bits

    //x是无穷大
    if( isinf(x) ){
        exp = 0xFF;
        fra = 0;
    }
    //x是非法数字
    else if( isnan(x) ){
        exp = 0xFF;
        fra = 0x7FFFFF;
    }
    else{
        if(sign)    x = -x;
        int e = 0;
        fra = frexp(x, &e) *((int)2<<23);
		if( e <= -BASE_32){		//浮点数过小，表示为0 
			fra = 0;
			exp = 0;
		} 
		else{
			exp = e + BASE_32;
			if(exp > 0xFF){		//exp只有8位，超过8位就不能表示 
				exp = 0xFF;
				fra = 0;
			}
		}
    }
    
    //置符号位 
	if(sign)	res = 1;
	res = res << 31;
	
	//置指数位
	res = res | exp << 23;
	
	//置底数位
	fra = fra & 0x7FFFFF;	//保留后23位 
	res = res | fra; 
	
	return res; 
}

unsigned long long doubleToBinary( double x ){
	unsigned long long res = 0;
    //符号位,当浮点数为负数是置1，否则置0
    bool sign = false;
    if(x < 0)   sign = true;
    
    unsigned long long exp;  	  //指数 11bits
    unsigned long long fra;       //底数  52bits

    //x是无穷大
    if( isinf(x) ){
        exp = 0x7FF;
        fra = 0;
    }
    //x是非法数字
    else if( isnan(x) ){
        exp = 0x7FF;
        fra = 0xFFFFFFFFFFFFF;
    }
    else{
        if(sign)    x = -x;
        int e = 0;
        fra = frexpl((long double)x, &e) *((long long)2<<52);
		if( e <= -BASE_64){		//浮点数过小，表示为0 
			fra = 0;
			exp = 0;
		} 
		else{
			exp = e + BASE_64;
			if(exp > 0x7FF){	//exp只有11位，超过11位就不能表示 
				exp = 0x7FF;
				fra = 0;
			}
		}
    }
    
    //置符号位 
	if(sign)	res = 1;
	res = res << 63;
	
	//置指数位
	res = res | exp << 52;
	
	//置底数位
	fra = fra & 0xFFFFFFFFFFFFF;	//保留后52位 
	res = res | fra; 
	
	return res; 
}
 
pair<unsigned long long,unsigned long long> longDoubleToBinary( long double x ){
	
    //符号位,当浮点数为负数是置1，否则置0
    bool sign = false;
    if(x < 0)   sign = true;
    
    unsigned long long exp;  	  //指数  15bits
    unsigned long long fra;       //底数  64bits

    //x是无穷大
    if( isinf(x) ){
        exp = 0x7FFF;
        fra = 0;
    }
    //x是非法数字
    else if( isnan(x) ){
        exp = 0x7FFF;
        fra = 0xFFFFFFFFFFFFFFFF;
    }
    else{
        if(sign)    x = -x;
        int e = 0;
        long double f;
        f = frexp(x, &e);
        f = f*2-1;
        fra = ldexp(f, 64);

		if( e <= -BASE_80){		//浮点数过小，表示为0 
			fra = 0;
			exp = 0;
		} 
		else{
			exp = e + BASE_80;
			if(exp > 0x7FFF){	//exp只有15位，超过15位就不能表示 
				exp = 0x7FFF;
				fra = 0;
			}
		}
    }
    
    //置符号位 
    unsigned long long high = 0, low = 0;	
	//high的低16位是res的高16位， low是res的低64位 
	if(sign)	high = 1;
	high = high << 15;

	//置指数位
	exp = exp & 0x7FFF;
	high = high | exp;
	
	//置底数位
	low = fra; 

	pair<unsigned long long,unsigned long long> res;
	res.first = high;
	res.second = low;
	return res; 
}

float binaryToFloat ( unsigned int x ){
	float res;
	bool sign = x & 0x80000000;			//获取最高位：符号位
	unsigned int exp = (x & 0x7F800000) >> 23;	//获取指数
	unsigned int fra = x & 0x7FFFFF;				//获取小数
	
	float fraction = (float)fra/((unsigned int)2<<22);
	fraction += 1;						//在这个地方+1

	if(exp == 0xFF){
		if(fra == (unsigned int)2<<23 ){
			return sign ? -1.0/0.0 : 1.0/0.0;
		}
		else{
			return sign ? 0.0/0.0 : -(0.0/0.0);
		}
	}
	res = ldexp(fraction, exp-127 )*(sign ? -1: 1);

	return res;
}

double binaryToDouble(unsigned long long x){
	double res;
	bool sign = x & 0x8000000000000000; 
	unsigned long long exp = (x & 0x7FF0000000000000) >> 52;
	unsigned long long fra = x & 0xFFFFFFFFFFFFF;
		
	double fraction = (double)fra/((unsigned long long)2<<51);
	fraction += 1;
	if(exp == 0x7FF){
		if(fra == (unsigned long long)2<<52 ){
			return sign ? -1.0/0.0 : 1.0/0.0;
		}
		else{
			return sign ? 0.0/0.0 : -(0.0/0.0);
		}
	}
	res = ldexp(fraction, exp-1023 )*(sign ? -1: 1);
	return res;
}

long double binaryToLongDouble(pair<unsigned long long,unsigned long long> x){
	long double res;
	bool sign = x.first & 0x8000;
	unsigned long long exp = x.first & 0x7FFF;
	unsigned long long fra = x.second;			
	
	long double fraction = ldexp(fra, -64);
	fraction += 1;

	if(exp == 0x7FFF){
		if(fra == (unsigned long long)2<<63 ){
			return sign ? -1.0/0.0 : 1.0/0.0;
		}
		else{
			return sign ? 0.0/0.0 : -(0.0/0.0);
		}
	}
	res = ldexp(fraction, exp-16383 )*(sign ? -1: 1);
	return res;
}
