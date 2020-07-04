
#include "binary.h"
#include "tinyxml2.h"
#include "seriXml.h"
#include "userDefined.h"

int main(){
    /* test part */

    //二进制的序列化

    //测试基础类型
    char t_char = 'a';
    unsigned char t_uchar = 'b';

    short t_short_min = -32768, t_short_max = 32767;
    unsigned short t_ushort = 65535;

    int t_int_min = -2147483648, t_int_max = 2147483647;
    unsigned int t_uint = 429496729;

    long t_long_min = -2147483648L, t_long_max = 2147483647L;
    unsigned long t_ulong = 4294967295UL;

    long long t_llong_min = -9223372036854775808LL, 
              t_llong_max = 9223372036854775807LL;
    unsigned long long t_ullong = 18446744073709551615ULL;

    float t_float = 321.123456;
    double t_double = 321.123456789012345;
    long double t_ldouble = 321.123456789012345678;

    std::cout<<"Before Serialization:"<<endl;
    printf("t_char = %c, t_uchar = %c\n",t_char, t_uchar);
    printf("t_short_min = %d, t_short_max = %d, t_ushort_ = %u\n", t_short_min, t_short_min, t_ushort);
    printf("t_int_min = %d, t_int_max = %d, t_uint = %u\n", t_int_min, t_int_max, t_uint);
    printf("t_long_min = %ld, t_long_max = %ld, t_ulong = %lu\n", t_long_min, t_long_max, t_ulong);
    printf("t_llong_min = %lld, t_llong_max = %lld, t_ullong = %llu\n", t_llong_min, t_llong_max, t_ullong);
    printf("t_float = %.6f, t_double = %.15lf, t_ldouble = %.19Lf\n", t_float, t_double, t_ldouble);

    //序列化
    binary::serializeAri(t_char, "data.bin");
    binary::deserializeAri(t_char, "data.bin");

    binary::serializeAri(t_uchar, "data.bin");
    binary::deserializeAri(t_uchar, "data.bin");

    binary::serializeAri(t_short_min, "data.bin");
    binary::deserializeAri(t_short_min, "data.bin");

    binary::serializeAri(t_short_max, "data.bin");
    binary::deserializeAri(t_short_max, "data.bin");

    binary::serializeAri(t_ushort, "data.bin");
    binary::deserializeAri(t_ushort, "data.bin");

    binary::serializeAri(t_int_min, "data.bin");
    binary::deserializeAri(t_int_min, "data.bin");

    binary::serializeAri(t_int_max, "data.bin");
    binary::deserializeAri(t_int_max, "data.bin");

    binary::serializeAri(t_uint, "data.bin");
    binary::deserializeAri(t_uint, "data.bin");

    binary::serializeAri(t_long_min, "data.bin");
    binary::deserializeAri(t_long_min, "data.bin");

    binary::serializeAri(t_long_max, "data.bin");
    binary::deserializeAri(t_long_max, "data.bin");

    binary::serializeAri(t_ulong, "data.bin");
    binary::deserializeAri(t_ulong, "data.bin");

    binary::serializeAri(t_llong_min, "data.bin");
    binary::deserializeAri(t_llong_min, "data.bin");

    binary::serializeAri(t_llong_max, "data.bin");
    binary::deserializeAri(t_llong_max, "data.bin");

    binary::serializeAri(t_ullong, "data.bin");
    binary::deserializeAri(t_ullong, "data.bin");

    binary::serializeAri(t_float, "data.bin");
    binary::deserializeAri(t_float, "data.bin");

    binary::serializeAri(t_double, "data.bin");
    binary::deserializeAri(t_double, "data.bin");

    binary::serializeAri(t_ldouble, "data.bin");
    binary::deserializeAri(t_ldouble, "data.bin");

    std::cout<<endl<<"After Serialization:"<<endl;
    printf("t_char = %c, t_uchar = %c\n",t_char, t_uchar);
    printf("t_short_min = %d, t_short_max = %d, t_ushort_ = %u\n", t_short_min, t_short_min, t_ushort);
    printf("t_int_min = %d, t_int_max = %d, t_uint = %u\n", t_int_min, t_int_max, t_uint);
    printf("t_long_min = %ld, t_long_max = %ld, t_ulong = %lu\n", t_long_min, t_long_max, t_ulong);
    printf("t_llong_min = %lld, t_llong_max = %lld, t_ullong = %llu\n", t_llong_min, t_llong_max, t_ullong);
    printf("t_float = %.6f, t_double = %.15lf, t_ldouble = %.19Lf\n", t_float, t_double, t_ldouble);


    unsigned long long x = 18446744073709551615ULL,y = 0;
    printf("%llu\n",x);
    xml::serializeAri_xml(x,"data.xml");
    xml::deserializeAri_xml(y,"data.xml");
    int a = 123,b;
    xml::serializeAri_xml(a,"data.xml");
    xml::deserializeAri_xml(b,"data.xml");
    printf("%llu\n",y);
    printf("%d\n",b);

    long double doublea = 123.321999;
    long double doubleb;
    binary::serializeAri(doublea,"data.bin");
    binary::deserializeAri(doubleb,"data.bin");
    printf("%Lf\n",doubleb);

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

    userDef::Base1._char = 'z';
    userDef::Base1._double = 2020.0202;
    userDef::Base1._vector_int.push_back(10);
    userDef::Base1._vector_int.push_back(22);
    userDef::structToBinary("struct.bin");
    userDef::binaryToStruct("struct.bin");
    printf("%c %lf %d %d\n",userDef::Base2._char,
                            userDef::Base2._double,
                            userDef::Base2._vector_int[0],
                            userDef::Base2._vector_int[1]);

    return 0;
}