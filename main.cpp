
#include "binary.h"
using namespace binary;

int main(){
    unsigned long long x = 18446744073709551615ULL,y = 0;
    printf("%llu\n",x);
    serializeAri(x,"data.bin");
    desetializeAri(y,"data.bin");
    int a = 123,b;
    serializeAri(a,"data.bin");
    desetializeAri(b,"data.bin");
    printf("%d\n",b);
    printf("%llu\n",y);

    auto p = std::make_pair(1,1);
    serializeStl(p,"data.bin");
    std::pair<int,int>q;
    deserializeStl(q,"data.bin");
    printf("%d %d\n",q.first,q.second);

    std::vector<long long> ve,vr;
    ve.push_back(22);
    ve.push_back(33);
    serializeStl(ve,"data.bin");
    deserializeStl(vr,"data.bin");
    printf("%lld %lld\n",vr[0],vr[1]);

    std::string s1 = "kajhcoisnjnkj^^&@)od82",s2;
    serializeStl(s1,"data.bin");
    deserializeStl(s2,"data.bin");
    std::cerr << s2 << std::endl;

    std::list<unsigned char> l1,l2;
    l1.push_back(23);
    l1.push_back(45);
    serializeStl(l1,"data.bin");
    deserializeStl(l2,"data.bin");
    auto it = l2.begin();
    unsigned char l2a = *it;++it;
    unsigned char l2b = *it;
    std::cerr << (unsigned int)l2a << " " << (unsigned int)l2b << std::endl;

    std::map<char, int> mp1,mp2;
    mp1['a'] = 233;
    mp1['z'] = 666;
    serializeStl(mp1,"data.bin");
    deserializeStl(mp2,"data.bin");
    std::cerr << mp2['a'] << " " << mp2['z'] << std::endl;

}