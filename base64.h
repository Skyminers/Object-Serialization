#ifndef BASE64_H
#define BASE64_H

#include <string.h>

class base64{
	private:
		char input[5];       //待编码或已解码
		char output[5];      //已编码或待解码
		char padding = '=';  //填充字符
		char code[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
						 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
						 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
						 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
						 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 
						 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
						 'w', 'x', 'y', 'z', '0', '1', '2', '3',
						 '4', '5', '6', '7', '8', '9', '+', '/'};
		
	public:
		base64(){
			memset(input, 0, 5);
			memset(output, 0, 5);
		}

        //将input中的字符编码到output中
		void encode(int select);

        //将output中的字符解码到input中
		int decode();

        //将input_file的内容编码到output_file
		void base64Encode(char* filename_input, char* filename_output);

        //将output_file的内容解码到input_file中
		void base64Decode(char* filename_input, char* filename_output);

        //输入一个字符，根据base64表，返回它的索引
		int getReverseCode(char x);
};

#endif
