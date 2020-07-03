
#include "binary.h"
#include "tinyxml2.h"
#include "seriXml.h"
using namespace binary;

int main(){
    unsigned long long x = 18446744073709551615ULL,y = 0;
    printf("%llu\n",x);
    xml::serializeAri_xml(x,"data.xml");
    xml::desetializeAri_xml(y,"data.xml");
    int a = 123,b;
    xml::serializeAri_xml(a,"data.xml");
    xml::desetializeAri_xml(b,"data.xml");
    printf("%llu\n",y);
    printf("%d\n",b);

    double doublea = 123.321;
    double doubleb;
    xml::serializeAri_xml(doublea,"data.xml");
    xml::desetializeAri_xml(doubleb,"data.xml");
    printf("%lf\n",doubleb);

    auto p = std::make_pair(1,1);
    xml::serializeStl_xml(p,"data.xml");
    std::pair<int,int>q;
    xml::deserializeStl_xml(q,"data.xml");
    printf("%d %d\n",q.first,q.second);

    std::vector<long long> ve,vr;
    ve.push_back(22);
    ve.push_back(33);
    xml::serializeStl_xml(ve,"data.xml");
    xml::deserializeStl_xml(vr,"data.xml");
    printf("%lld %lld\n",vr[0],vr[1]);

    std::string s1 = "kajhcoisnjnkj^^&@)od82",s2;
    xml::serializeStl_xml(s1,"data.xml");
    xml::deserializeStl_xml(s2,"data.xml");
    std::cerr << s2 << std::endl;

    std::list<unsigned char> l1,l2;
    l1.push_back(23);
    l1.push_back(45);
    xml::serializeStl_xml(l1,"data.xml");
    xml::deserializeStl_xml(l2,"data.xml");
    auto it = l2.begin();
    unsigned char l2a = *it;++it;
    unsigned char l2b = *it;
    std::cerr << (unsigned int)l2a << " " << (unsigned int)l2b << std::endl;

    std::map<char, int> mp1,mp2;
    mp1['a'] = 233;
    mp1['z'] = 666;
    xml::serializeStl_xml(mp1,"data.xml");
    xml::deserializeStl_xml(mp2,"data.xml");
    std::cerr << mp2['a'] << " " << mp2['z'] << std::endl;

}