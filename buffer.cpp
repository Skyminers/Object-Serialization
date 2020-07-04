
#include "buffer.h"
#include <iostream>

Buffer::Buffer(){
    clear();
}

void Buffer::readFromFile(std::string fileName){// 该函数从文件中读入数据
    FILE* in = fopen(fileName.c_str(),"rb"); // 打开文件
    if(!in) throw std::string("failed to open file");
    // 读入2048位二进制
    fread(buf,sizeof(char),sizeof(char)*256,in);
    fclose(in);
}

void Buffer::printToFile(std::string fileName){// 与上个函数类似，该函数输出到文件
    FILE* out = fopen(fileName.c_str(),"wb");
    if(!out) throw std::string("failed to create file");
    fwrite(buf,sizeof(char),sizeof(char)*256,out);
    fclose(out);
}

unsigned long long Buffer::getNextN(int n){ // 获取二进制文件中由[p..p+n)部分组成的数字
    if(p+n >= 256*8) throw std::string("chars are out of range");
    if(n > 64) throw std::string("out of range, the most is 64-byte");
    unsigned long long ret = 0;
    // 假设顺序为 buf[0] 0 - 7 , buf[1] 0 - 7
    for(int i=0;i<n;++p,++i){
        //std::cerr << "get " << p << " is " << ((buf[p/8] >> p%8) & 1) << std::endl;
        ret = (ret << 1) | ((buf[p/8] >> (p%8)) & 1);
    }
    return ret;
}

void Buffer::setNext(bool val){// 该函数用于对单点进行赋值
    //std::cerr << "set " << p << " with " << val << std::endl;
    if(val) buf[p/8] |= (1<<(p%8));
    else buf[p/8] &= ~(1<<(p%8));
    ++ p;
}

void Buffer::setNBits(int n,unsigned long long data){ // 将data中的低n个bit输出到buf中
    while(n) setNext((data >> --n)&1 );
}

void Buffer::clear(){ // 清空buf
    for(int i=0;i<256;++i) buf[i] = 0;
    p = 0;
}