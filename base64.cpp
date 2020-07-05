#include <string>
#include <iostream>
#include <cstdio>
#include "base64.h"

using namespace std;

//将input_file中的字符编码后写入到output_file中
void base64::base64Encode(char* filename_input, char* filename_output){
	FILE* pfile1 = fopen(filename_input, "r");
	FILE* pfile2 = fopen(filename_output, "w");

    //每次读取3个字符
	while(fread(input, 3, 1, pfile1)){
		encode(3);
        //printf("%s, %s\n", input, output);
		fwrite(output, 4, 1, pfile2);
	}	
    
    //如果输入文件还没有到结尾，还剩下一个或两个字符
    //这时根据剩余字符个数，选择不同的编码方式
	int k = ftell(pfile1)%3-1;
	if(k > 0){
		fseek(pfile1, -k, SEEK_END);
		encode(k);
        //printf("%d:%s, %s\n", k, input, output);
		fwrite(output, 4, 1, pfile2);
	}
	fclose(pfile1);
	fclose(pfile2);
}

//读取output_file中的内容，解码后写入到input_file中
void base64::base64Decode(char* filename_input, char* filename_output){
	FILE* pfile1 = fopen(filename_input, "w");
	FILE* pfile2 = fopen(filename_output, "r");

    //每次读取4个字符
	while(fread(output, 4, 1, pfile2)){
		int res = decode();
        //返回值为0，说明读到了无效字符
		if(res == 0){
            printf("undefined base64 code\n");
		}
		else{
			fwrite(input, res, 1, pfile1);
		}
	}

    //如果output_file中的字符个数不是4的倍数，说明它不是一个有效的base64编码
	int k = ftell(pfile2)%4;
	if(k != 0){
        printf("wrong bytes number in base64 file.\n");
	}

    fclose(pfile1);
    fclose(pfile2);
}

//输入字符，在base64表中寻找对应的索引，如果字符不在base64表中，返回错误码-1
int base64::getReverseCode(char x){
	int i=0;
	for(int i=0;i<64;i++){
		if(base64::code[i] == x){
			return i;
		}
	}
	if(i == 64){
        //如果输入参数不在base64表中，返回-1
        printf("error code!\n");
		return -1;
	}
}

//将output中的字符解码到input中，返回值为解码后的字符个数
int base64::decode(){
	char buffer[5];
	int i;

    //先根据输入的字符查base64表，找到它们的索引，存在buffer中
	for(i=0;i<4;i++){
		if(output[i] == base64::padding)	break;
		buffer[i] = base64::getReverseCode(output[i]);
        //得到错误的返回值，说明输入的字符并不在base64表中
		if(buffer[i] == -1){
            printf("wrong bytes number in base64 file.\n");
			return 0;
		}
	}

    //根据有效字符个数进行解密，返回解码后的字符数
	if(i == 4){
		input[0] = ((buffer[0] << 2) & 0xFC) | ((buffer[1] >> 4) & 0x03);
		input[1] = ((buffer[1] << 4) & 0xF0) | ((buffer[2] >> 2) & 0x0F);
		input[2] = ((buffer[2] << 6) & 0xC0) | (buffer[3] & 0x3F);
		return 3;
	}
	if(i == 3){
		input[0] = ((buffer[0] << 2) & 0xFC) | ((buffer[1] >> 4) & 0x03);
		input[1] = ((buffer[1] << 4) & 0xF0) | ((buffer[2] >> 2) & 0x0F);
		return 2;
	}
	if(i == 2){
		input[0] = ((buffer[0] << 2) & 0xFC) | ((buffer[1] >> 4) & 0x03);
		return 1;
	}
	return 0;
}

//输入input中需要编码的字符个数， 只能输入1,2,3
//无论input中编码字符的个数为多少，output中的输出都是4个字符，不够用padding来补
void base64::encode(int select){
	if(select == 3){	    //编码字符个数为3
		int index = 0;
		index = ((input[0] & 0xFC)>>2) & 0x3F;
		output[0] = code[index];
		index = 0;
		index = ((input[0] & 0x03) << 4)| ((input[1] & 0xF0) >> 4); 
		output[1] = code[index];
		index = 0;
		index = ((input[1] << 2) & 0x3C)| (input[2] >> 6);
		output[2] = code[index];
		index = 0;
		index = input[2] & 0x3F;
		output[3] = code[index];
	}
	else if(select == 2){	//编码字符个数为2
		int index = 0;
		index = ((input[0] & 0xFC)>>2) & 0x3F;
		output[0] = code[index];
		index = 0;
		index = ((input[0] & 0x03) << 4)| ((input[1] & 0xF0) >> 4); 
		output[1] = code[index];
		index = 0;
		index = (input[1] << 2) & 0x3C;
		output[2] = code[index];
		output[3] = padding;
	}
	else if(select == 1){   //编码字符个数为1
		int index = 0;
		index = ((input[0] & 0xFC)>>2) & 0x3F;
		output[0] = code[index];
		index = 0;
		index = ((input[0] << 4) & 0x30);
		output[1] = code[index];
		output[2] = output[3] = padding;
	}
	else{                   //其他数字，选择参数错误
		printf("select error\n");
	}
}