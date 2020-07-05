
#include "test.h"
#include "base64.h"

void binaryTest();
void xmlTest();

int main(){
    /* test part */
    binaryTest();
    xmlTest();

    /* bonus1 part */
    base64 foo;
    foo.base64Encode("data.xml", "encode_data.txt");
    foo.base64Decode("decode_data.xml", "encode_data.txt");
    return 0;
}