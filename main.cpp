
#include "binary.h"
using namespace binary;

int main(){
    unsigned long long x = 18446744073709551615ULL,y = 0;
    printf("%llu\n",x);
    serialize(x,"data.bin");
    desetialize(y,"data.bin");
    printf("%llu\n",y);
}