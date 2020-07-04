#include "binary.h"
#include "tinyxml2.h"
#include "seriXml.h"
#include "userDefined.h"
#include "test.h"

void binaryTest(){
    cout<<"------------------------binary serialization/deserialization------------------------ "<<endl;
    cout << ">>>>>>>>>basic type:"<<endl<<endl;
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

    //序列化和反序列化
    binary::serializeAri(t_char, "data.bin");
    t_char = 0;
    binary::deserializeAri(t_char, "data.bin");

    binary::serializeAri(t_uchar, "data.bin");
    t_uchar = 0;
    binary::deserializeAri(t_uchar, "data.bin");

    binary::serializeAri(t_short_min, "data.bin");
    t_short_min = 0;
    binary::deserializeAri(t_short_min, "data.bin");

    binary::serializeAri(t_short_max, "data.bin");
    t_short_max = 0;
    binary::deserializeAri(t_short_max, "data.bin");

    binary::serializeAri(t_ushort, "data.bin");
    t_ushort = 0;
    binary::deserializeAri(t_ushort, "data.bin");

    binary::serializeAri(t_int_min, "data.bin");
    t_int_min = 0;
    binary::deserializeAri(t_int_min, "data.bin");

    binary::serializeAri(t_int_max, "data.bin");
    t_int_max = 0;
    binary::deserializeAri(t_int_max, "data.bin");

    binary::serializeAri(t_uint, "data.bin");
    t_uint = 0;
    binary::deserializeAri(t_uint, "data.bin");

    binary::serializeAri(t_long_min, "data.bin");
    t_long_min = 0;
    binary::deserializeAri(t_long_min, "data.bin");

    binary::serializeAri(t_long_max, "data.bin");
    t_long_max = 0;
    binary::deserializeAri(t_long_max, "data.bin");

    binary::serializeAri(t_ulong, "data.bin");
    t_ulong = 0;
    binary::deserializeAri(t_ulong, "data.bin");

    binary::serializeAri(t_llong_min, "data.bin");
    t_llong_min = 0;
    binary::deserializeAri(t_llong_min, "data.bin");

    binary::serializeAri(t_llong_max, "data.bin");
    t_llong_max = 0;
    binary::deserializeAri(t_llong_max, "data.bin");

    binary::serializeAri(t_ullong, "data.bin");
    t_ullong = 0;
    binary::deserializeAri(t_ullong, "data.bin");

    binary::serializeAri(t_float, "data.bin");
    t_float = 0;
    binary::deserializeAri(t_float, "data.bin");

    binary::serializeAri(t_double, "data.bin");
    t_double = 0;
    binary::deserializeAri(t_double, "data.bin");

    binary::serializeAri(t_ldouble, "data.bin");
    t_ldouble = 0;
    binary::deserializeAri(t_ldouble, "data.bin");

    std::cout<<endl<<"After Serialization:"<<endl;
    printf("t_char = %c, t_uchar = %c\n",t_char, t_uchar);
    printf("t_short_min = %d, t_short_max = %d, t_ushort_ = %u\n", t_short_min, t_short_min, t_ushort);
    printf("t_int_min = %d, t_int_max = %d, t_uint = %u\n", t_int_min, t_int_max, t_uint);
    printf("t_long_min = %ld, t_long_max = %ld, t_ulong = %lu\n", t_long_min, t_long_max, t_ulong);
    printf("t_llong_min = %lld, t_llong_max = %lld, t_ullong = %llu\n", t_llong_min, t_llong_max, t_ullong);
    printf("t_float = %.6f, t_double = %.15lf, t_ldouble = %.19Lf\n", t_float, t_double, t_ldouble);

    //测试容器类型
    cout<<endl<< ">>>>>>>>>STL type:"<<endl<<endl;

    //类型定义
    std::string t_string = "This is a string";

    std::pair<long long,long long> t_pair_ll_ll;
    t_pair_ll_ll.first = 9223372036854775807LL;
    t_pair_ll_ll.second =  9223372036854775807LL;
    std::pair<long double, long double> t_pair_ld_ld;
    t_pair_ld_ld.first = 321.123456789012345678;
    t_pair_ld_ld.second = 321.123456789012345678;
    std::pair<long long, long double> t_pair_ll_ld;
    t_pair_ll_ld.first = 9223372036854775807LL;
    t_pair_ll_ld.second = 321.123456789012345678;

    std::vector<long long> t_vector_ll;
    t_vector_ll.push_back(9223372036854775807LL);
    t_vector_ll.push_back(-9223372036854775808LL);
    t_vector_ll.push_back(1234567890987654LL);

    std::vector<long double> t_vector_ld;
    t_vector_ld.push_back(321.123456789012345678);
    t_vector_ld.push_back(373921.273792378217);
    t_vector_ld.push_back(0.987654321);

    std::list<long long> t_list_ll;
    t_list_ll.push_back(11111111111111LL);
    t_list_ll.push_back(22222222222222LL);
    t_list_ll.push_back(33333333333333LL);

    std::list<long double> t_list_ld;
    t_list_ld.push_back(1111.11111111111);
    t_list_ld.push_back(2222.22222222222);
    t_list_ld.push_back(3333.33333333333);

    std::map<long long, long long> t_map_ll_ll;
    t_map_ll_ll[9223372036854775807LL] = 9223372036854775807LL;
    t_map_ll_ll[-9223372036854775808LL] = -9223372036854775808LL;
    
    std::map<long double, long double> t_map_ld_ld;
    t_map_ld_ld[321.123456789012345678] = 321.123456789012345678;
    t_map_ld_ld[1111.2222] = 2222.1111;
    t_map_ld_ld[0.12345] = 12345.0;

    std::map<long long, long double> t_map_ll_ld;
    t_map_ll_ld[9223372036854775807LL] = 321.123456789012345678;
    t_map_ll_ld[-9223372036854775808LL] = -321.123456789012345678;
    t_map_ll_ld[123456789LL] = 0.123456789;

    cout<<"before serialization:"<<endl;
    cout<<"t_string:"<<t_string<<endl;
    printf("t_pair_ll_ll:(%lld, %lld)\n", t_pair_ll_ll.first, t_pair_ll_ll.second);
    printf("t_pair_ld_ld:(%0.18Lf, %0.18Lf)\n", t_pair_ld_ld.first, t_pair_ld_ld.second);
    printf("t_pair_ll_ld:(%lld, %0.18Lf)\n", t_pair_ll_ld.first, t_pair_ll_ld.second);
    printf("t_vector_ll:{%lld, %lld, %lld}\n", t_vector_ll[0], t_vector_ll[1], t_vector_ll[2]);
    printf("t_vector_ld:{%0.18Lf, %0.18Lf, %0.18Lf}\n", t_vector_ld[0], t_vector_ld[1], t_vector_ld[2]);

    std::list<long long>::iterator plist_ll = t_list_ll.begin();
    printf("t_list_ll:{%lld, %lld, %lld}\n", *plist_ll++, *plist_ll++, *plist_ll++);
    std::list<long double>::iterator plist_ld= t_list_ld.begin();
    printf("t_list_ld:{%.18Lf, %.18Lf, %.18Lf}\n", *plist_ld++, *plist_ld++, *plist_ld++);

    std::map<long long, long long>::iterator p_map_ll_ll = t_map_ll_ll.begin();
    printf("t_map_ll_ll:{(%lld, %lld), ", p_map_ll_ll->first, (p_map_ll_ll)->second); p_map_ll_ll++;
    printf("(%lld, %lld)}\n",p_map_ll_ll->first, (p_map_ll_ll)->second );

    std::map<long double, long double>::iterator p_map_ld_ld = t_map_ld_ld.begin();
    printf("t_map_ld_ld:{(%.15Lf, %.15Lf),", p_map_ld_ld->first, (p_map_ld_ld)->second);p_map_ld_ld++;
    printf("(%.15Lf, %.15Lf),",p_map_ld_ld->first, p_map_ld_ld->second);p_map_ld_ld++;
    printf("(%.15Lf, %.15Lf)}\n",p_map_ld_ld->first, p_map_ld_ld->second);

    std::map<long long, long double>::iterator p_map_ll_ld = t_map_ll_ld.begin();
    printf("t_map_ll_ld:{(%lld, %.15Lf),", p_map_ll_ld->first, (p_map_ll_ld)->second);p_map_ll_ld++;
    printf("(%lld, %.15Lf),",p_map_ll_ld->first, p_map_ll_ld->second);p_map_ll_ld++;
    printf("(%lld, %.15Lf)}\n",p_map_ll_ld->first, p_map_ll_ld->second);

    cout<<endl<<"after serialization:"<<endl;
    binary::serializeStl(t_string, "data.bin");
    t_string = "";
    binary::deserializeStl(t_string, "data.bin");
    cout<<"t_string:"<<t_string<<endl;

    binary::serializeStl(t_pair_ll_ll, "data.bin");
    t_pair_ll_ll.first = t_pair_ll_ll.second = 0;
    binary::deserializeStl(t_pair_ll_ll, "data.bin");
    printf("t_pair_ll_ll:(%lld, %lld)\n", t_pair_ll_ll.first, t_pair_ll_ll.second);

    binary::serializeStl(t_pair_ld_ld, "data.bin");
    t_pair_ld_ld.first = t_pair_ld_ld.second = 0;
    binary::deserializeStl(t_pair_ld_ld, "data.bin");
    printf("t_pair_ld_ld:(%0.18Lf, %0.18Lf)\n", t_pair_ld_ld.first, t_pair_ld_ld.second);

    binary::serializeStl(t_pair_ll_ld, "data.bin");
    t_pair_ll_ld.first = t_pair_ll_ld.second = 0;
    binary::deserializeStl(t_pair_ll_ld, "data.bin");
    printf("t_pair_ll_ld:(%lld, %0.18Lf)\n", t_pair_ll_ld.first, t_pair_ll_ld.second);

    binary::serializeStl(t_vector_ll, "data.bin");
    t_vector_ll.clear();
    binary::deserializeStl(t_vector_ll, "data.bin");
    printf("t_vector_ll:{%lld, %lld, %lld}\n", t_vector_ll[0], t_vector_ll[1], t_vector_ll[2]);

    binary::serializeStl(t_vector_ld, "data.bin");
    t_vector_ld.clear();
    binary::deserializeStl(t_vector_ld, "data.bin");
    printf("t_vector_ld:{%0.18Lf, %0.18Lf, %0.18Lf}\n", t_vector_ld[0], t_vector_ld[1], t_vector_ld[2]);

    binary::serializeStl(t_list_ll, "data.bin");
    t_list_ll.clear();
    binary::deserializeStl(t_list_ll, "data.bin");
    plist_ll = t_list_ll.begin();
    printf("t_list_ll:{%lld, %lld, %lld}\n", *plist_ll++, *plist_ll++, *plist_ll++);

    binary::serializeStl(t_list_ld,"data.bin");
    t_list_ld.clear();
    binary::deserializeStl(t_list_ld, "data.bin");
    plist_ld= t_list_ld.begin();
    printf("t_list_ld:{%.18Lf, %.18Lf, %.18Lf}\n", *plist_ld++, *plist_ld++, *plist_ld++);

    binary::serializeStl(t_map_ll_ll, "data.bin");
    t_map_ll_ll.clear();
    binary::deserializeStl(t_map_ll_ll, "data.bin");
    p_map_ll_ll = t_map_ll_ll.begin();
    printf("t_map_ll_ll:{(%lld, %lld), ", p_map_ll_ll->first, (p_map_ll_ll)->second); p_map_ll_ll++;
    printf("(%lld, %lld)}\n",p_map_ll_ll->first, (p_map_ll_ll)->second ); 

    binary::serializeStl(t_map_ld_ld, "data.bin");
    t_map_ld_ld.clear();
    binary::deserializeStl(t_map_ld_ld, "data.bin");
    p_map_ld_ld = t_map_ld_ld.begin();
    printf("t_map_ld_ld:{(%.15Lf, %.15Lf),", p_map_ld_ld->first, (p_map_ld_ld)->second);p_map_ld_ld++;
    printf("(%.15Lf, %.15Lf),",p_map_ld_ld->first, p_map_ld_ld->second);p_map_ld_ld++;
    printf("(%.15Lf, %.15Lf)}\n",p_map_ld_ld->first, p_map_ld_ld->second);   

    binary::serializeStl(t_map_ll_ld, "data.bin");
    t_map_ll_ld.clear();
    binary::deserializeStl(t_map_ll_ld, "data.bin");
    p_map_ll_ld = t_map_ll_ld.begin();
    printf("t_map_ll_ld:{(%lld, %.15Lf),", p_map_ll_ld->first, (p_map_ll_ld)->second);p_map_ll_ld++;
    printf("(%lld, %.15Lf),",p_map_ll_ld->first, p_map_ll_ld->second);p_map_ll_ld++;
    printf("(%lld, %.15Lf)}\n",p_map_ll_ld->first, p_map_ll_ld->second);

    //自定义类型序列化
    cout <<endl<< ">>>>>>>>>user defined type:"<<endl;
    struct students{
        string name;
        long long ID_number;
        double avg_score;
        std::list<int> course_list;
        //map->first = courseID  map->second = score
        std::map<int, int> score_list;
        //pair->first = studentID pair->second = teacherID
        std::pair<int, int> tutor;
    }stu;
    for(int i=0; i<10; i++){
        stu.course_list.push_back(202000+i);
        stu.score_list.insert(pair<int, int>(202000+i, 80+i));
    }
    stu.tutor.first = 123456;
    stu.tutor.second = 654321;
    stu.name = "Lisa";
    stu.avg_score = 80.32;
    stu.ID_number = 654321;

    cout<<endl<<"before serialization:"<<endl;
    cout<<"name:"<<stu.name <<endl;
    printf("studentID:%lld\navg_score:%lf\n",stu.ID_number ,stu.avg_score );

    cout<<"course_list:";
    std::list<int>::iterator plist= stu.course_list.begin();
    for(int i=0;i<10;i++){
        if(i!=9)
            printf("%d, ", *plist++);
        else
            printf("%d", *plist);
    }
    cout<<endl;

    cout<<"score_list:";
    std::map<int, int>::iterator pmap = stu.score_list.begin();
    for(int i=0;i<10;i++){
        if(i!=9)
            printf("(%d, %d), ", pmap->first, pmap->second );
        else
            printf("(%d, %d)", pmap->first, pmap->second);
        pmap++;
    }
    cout<<endl;
    printf("tutor:%d, %d\n", stu.tutor.first, stu.tutor.second);

    //序列化和反序列化
    userDef::Base1._string = stu.name;
    userDef::Base1._llong = stu.ID_number;
    userDef::Base1._double = stu.avg_score;
    userDef::Base1._list_int = stu.course_list;
    userDef::Base1._map_int = stu.score_list;
    userDef::Base1._pair_int = stu.tutor;

    userDef::structToBinary("struct.bin");
    userDef::binaryToStruct("struct.bin");

    cout<<endl<<"after serialization:"<<endl;
    cout<<"name:"<<userDef::Base2._string<<endl;
    printf("studentID:%lld\navg_score:%lf\n",userDef::Base2._llong, userDef::Base2._double);

    cout<<"course_list:";
    plist= stu.course_list.begin();
    for(int i=0;i<10;i++){
        if(i!=9)
            printf("%d, ", *plist++);
        else
            printf("%d", *plist);
    }
    cout<<endl;

    cout<<"score_list:";
    pmap = stu.score_list.begin();
    for(int i=0;i<10;i++){
        if(i!=9)
            printf("(%d, %d), ", pmap->first, pmap->second );
        else
            printf("(%d, %d)", pmap->first, pmap->second);
        pmap++;
    }
    cout<<endl;
    printf("tutor:%d, %d\n", stu.tutor.first, stu.tutor.second);

}

void xmlTest(){
    cout<<"------------------------xml serialization/deserialization------------------------ "<<endl;
    cout << ">>>>>>>>>base type:"<<endl<<endl;
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

    //序列化和反序列化
    xml::serializeAri_xml(t_char, "data.xml");
    t_char = 0;
    xml::deserializeAri_xml(t_char, "data.xml");

    xml::serializeAri_xml(t_uchar, "data.xml");
    t_uchar = 0;
    xml::deserializeAri_xml(t_uchar, "data.xml");

    xml::serializeAri_xml(t_short_min, "data.xml");
    t_short_min = 0;
    xml::deserializeAri_xml(t_short_min, "data.xml");

    xml::serializeAri_xml(t_short_max, "data.xml");
    t_short_max = 0;
    xml::deserializeAri_xml(t_short_max, "data.xml");

    xml::serializeAri_xml(t_ushort, "data.xml");
    t_ushort = 0;
    xml::deserializeAri_xml(t_ushort, "data.xml");

    xml::serializeAri_xml(t_int_min, "data.xml");
    t_int_min = 0;
    xml::deserializeAri_xml(t_int_min, "data.xml");

    xml::serializeAri_xml(t_int_max, "data.xml");
    t_int_max = 0;
    xml::deserializeAri_xml(t_int_max, "data.xml");

    xml::serializeAri_xml(t_uint, "data.xml");
    t_uint = 0;
    xml::deserializeAri_xml(t_uint, "data.xml");

    xml::serializeAri_xml(t_long_min, "data.xml");
    t_long_min = 0;
    xml::deserializeAri_xml(t_long_min, "data.xml");

    xml::serializeAri_xml(t_long_max, "data.xml");
    t_long_max = 0;
    xml::deserializeAri_xml(t_long_max, "data.xml");

    xml::serializeAri_xml(t_ulong, "data.xml");
    t_ulong = 0;
    xml::deserializeAri_xml(t_ulong, "data.xml");

    xml::serializeAri_xml(t_llong_min, "data.xml");
    t_llong_min = 0;
    xml::deserializeAri_xml(t_llong_min, "data.xml");

    xml::serializeAri_xml(t_llong_max, "data.xml");
    t_llong_max = 0;
    xml::deserializeAri_xml(t_llong_max, "data.xml");

    xml::serializeAri_xml(t_ullong, "data.xml");
    t_ullong = 0;
    xml::deserializeAri_xml(t_ullong, "data.xml");

    xml::serializeAri_xml(t_float, "data.xml");
    t_float = 0;
    xml::deserializeAri_xml(t_float, "data.xml");

    xml::serializeAri_xml(t_double, "data.xml");
    t_double = 0;
    xml::deserializeAri_xml(t_double, "data.xml");

    xml::serializeAri_xml(t_ldouble, "data.xml");
    t_ldouble = 0;
    xml::deserializeAri_xml(t_ldouble, "data.xml");

    std::cout<<endl<<"After Serialization:"<<endl;
    printf("t_char = %c, t_uchar = %c\n",t_char, t_uchar);
    printf("t_short_min = %d, t_short_max = %d, t_ushort_ = %u\n", t_short_min, t_short_min, t_ushort);
    printf("t_int_min = %d, t_int_max = %d, t_uint = %u\n", t_int_min, t_int_max, t_uint);
    printf("t_long_min = %ld, t_long_max = %ld, t_ulong = %lu\n", t_long_min, t_long_max, t_ulong);
    printf("t_llong_min = %lld, t_llong_max = %lld, t_ullong = %llu\n", t_llong_min, t_llong_max, t_ullong);
    printf("t_float = %.6f, t_double = %.15lf, t_ldouble = %.19Lf\n", t_float, t_double, t_ldouble);

    //测试容器类型
    cout <<endl<< ">>>>>>>>>STL type:"<<endl<<endl;

    //类型定义
    std::string t_string = "This is a string";

    std::pair<long long,long long> t_pair_ll_ll;
    t_pair_ll_ll.first = 9223372036854775807LL;
    t_pair_ll_ll.second =  9223372036854775807LL;
    std::pair<long double, long double> t_pair_ld_ld;
    t_pair_ld_ld.first = 321.123456789012345678;
    t_pair_ld_ld.second = 321.123456789012345678;
    std::pair<long long, long double> t_pair_ll_ld;
    t_pair_ll_ld.first = 9223372036854775807LL;
    t_pair_ll_ld.second = 321.123456789012345678;

    std::vector<long long> t_vector_ll;
    t_vector_ll.push_back(9223372036854775807LL);
    t_vector_ll.push_back(-9223372036854775808LL);
    t_vector_ll.push_back(1234567890987654LL);

    std::vector<long double> t_vector_ld;
    t_vector_ld.push_back(321.123456789012345678);
    t_vector_ld.push_back(373921.273792378217);
    t_vector_ld.push_back(0.987654321);

    std::list<long long> t_list_ll;
    t_list_ll.push_back(11111111111111LL);
    t_list_ll.push_back(22222222222222LL);
    t_list_ll.push_back(33333333333333LL);

    std::list<long double> t_list_ld;
    t_list_ld.push_back(1111.11111111111);
    t_list_ld.push_back(2222.22222222222);
    t_list_ld.push_back(3333.33333333333);

    std::map<long long, long long> t_map_ll_ll;
    t_map_ll_ll[9223372036854775807LL] = 9223372036854775807LL;
    t_map_ll_ll[-9223372036854775808LL] = -9223372036854775808LL;
    
    std::map<long double, long double> t_map_ld_ld;
    t_map_ld_ld[321.123456789012345678] = 321.123456789012345678;
    t_map_ld_ld[1111.2222] = 2222.1111;
    t_map_ld_ld[0.12345] = 12345.0;

    std::map<long long, long double> t_map_ll_ld;
    t_map_ll_ld[9223372036854775807LL] = 321.123456789012345678;
    t_map_ll_ld[-9223372036854775808LL] = -321.123456789012345678;
    t_map_ll_ld[123456789LL] = 0.123456789;

    cout<<"before serialization:"<<endl;
    cout<<"t_string:"<<t_string<<endl;
    printf("t_pair_ll_ll:(%lld, %lld)\n", t_pair_ll_ll.first, t_pair_ll_ll.second);
    printf("t_pair_ld_ld:(%0.18Lf, %0.18Lf)\n", t_pair_ld_ld.first, t_pair_ld_ld.second);
    printf("t_pair_ll_ld:(%lld, %0.18Lf)\n", t_pair_ll_ld.first, t_pair_ll_ld.second);
    printf("t_vector_ll:{%lld, %lld, %lld}\n", t_vector_ll[0], t_vector_ll[1], t_vector_ll[2]);
    printf("t_vector_ld:{%0.18Lf, %0.18Lf, %0.18Lf}\n", t_vector_ld[0], t_vector_ld[1], t_vector_ld[2]);

    std::list<long long>::iterator plist_ll = t_list_ll.begin();
    printf("t_list_ll:{%lld, %lld, %lld}\n", *plist_ll++, *plist_ll++, *plist_ll++);
    std::list<long double>::iterator plist_ld= t_list_ld.begin();
    printf("t_list_ld:{%.18Lf, %.18Lf, %.18Lf}\n", *plist_ld++, *plist_ld++, *plist_ld++);

    std::map<long long, long long>::iterator p_map_ll_ll = t_map_ll_ll.begin();
    printf("t_map_ll_ll:{(%lld, %lld), ", p_map_ll_ll->first, (p_map_ll_ll)->second); p_map_ll_ll++;
    printf("(%lld, %lld)}\n",p_map_ll_ll->first, (p_map_ll_ll)->second );

    std::map<long double, long double>::iterator p_map_ld_ld = t_map_ld_ld.begin();
    printf("t_map_ld_ld:{(%.15Lf, %.15Lf),", p_map_ld_ld->first, (p_map_ld_ld)->second);p_map_ld_ld++;
    printf("(%.15Lf, %.15Lf),",p_map_ld_ld->first, p_map_ld_ld->second);p_map_ld_ld++;
    printf("(%.15Lf, %.15Lf)}\n",p_map_ld_ld->first, p_map_ld_ld->second);

    std::map<long long, long double>::iterator p_map_ll_ld = t_map_ll_ld.begin();
    printf("t_map_ll_ld:{(%lld, %.15Lf),", p_map_ll_ld->first, (p_map_ll_ld)->second);p_map_ll_ld++;
    printf("(%lld, %.15Lf),",p_map_ll_ld->first, p_map_ll_ld->second);p_map_ll_ld++;
    printf("(%lld, %.15Lf)}\n",p_map_ll_ld->first, p_map_ll_ld->second);

    cout<<endl<<"after serialization:"<<endl;
    xml::serializeStl_xml(t_string, "data.xml");
    t_string = "";
    xml::deserializeStl_xml(t_string, "data.xml");
    cout<<"t_string:"<<t_string<<endl;

    xml::serializeStl_xml(t_pair_ll_ll, "data.xml");
    t_pair_ll_ll.first = t_pair_ll_ll.second = 0;
    xml::deserializeStl_xml(t_pair_ll_ll, "data.xml");
    printf("t_pair_ll_ll:(%lld, %lld)\n", t_pair_ll_ll.first, t_pair_ll_ll.second);

    xml::serializeStl_xml(t_pair_ld_ld, "data.xml");
    t_pair_ld_ld.first = t_pair_ld_ld.second = 0;
    xml::deserializeStl_xml(t_pair_ld_ld, "data.xml");
    printf("t_pair_ld_ld:(%0.18Lf, %0.18Lf)\n", t_pair_ld_ld.first, t_pair_ld_ld.second);

    xml::serializeStl_xml(t_pair_ll_ld, "data.xml");
    t_pair_ll_ld.first = t_pair_ll_ld.second = 0;
    xml::deserializeStl_xml(t_pair_ll_ld, "data.xml");
    printf("t_pair_ll_ld:(%lld, %0.18Lf)\n", t_pair_ll_ld.first, t_pair_ll_ld.second);

    xml::serializeStl_xml(t_vector_ll, "data.xml");
    t_vector_ll.clear();
    xml::deserializeStl_xml(t_vector_ll, "data.xml");
    printf("t_vector_ll:{%lld, %lld, %lld}\n", t_vector_ll[0], t_vector_ll[1], t_vector_ll[2]);

    xml::serializeStl_xml(t_vector_ld, "data.xml");
    t_vector_ld.clear();
    xml::deserializeStl_xml(t_vector_ld, "data.xml");
    printf("t_vector_ld:{%0.18Lf, %0.18Lf, %0.18Lf}\n", t_vector_ld[0], t_vector_ld[1], t_vector_ld[2]);

    xml::serializeStl_xml(t_list_ll, "data.xml");
    t_list_ll.clear();
    xml::deserializeStl_xml(t_list_ll, "data.xml");
    plist_ll = t_list_ll.begin();
    printf("t_list_ll:{%lld, %lld, %lld}\n", *plist_ll++, *plist_ll++, *plist_ll++);

    xml::serializeStl_xml(t_list_ld,"data.xml");
    t_list_ld.clear();
    xml::deserializeStl_xml(t_list_ld, "data.xml");
    plist_ld= t_list_ld.begin();
    printf("t_list_ld:{%.18Lf, %.18Lf, %.18Lf}\n", *plist_ld++, *plist_ld++, *plist_ld++);

    xml::serializeStl_xml(t_map_ll_ll, "data.xml");
    t_map_ll_ll.clear();
    xml::deserializeStl_xml(t_map_ll_ll, "data.xml");
    p_map_ll_ll = t_map_ll_ll.begin();
    printf("t_map_ll_ll:{(%lld, %lld), ", p_map_ll_ll->first, (p_map_ll_ll)->second); p_map_ll_ll++;
    printf("(%lld, %lld)}\n",p_map_ll_ll->first, (p_map_ll_ll)->second ); 

    xml::serializeStl_xml(t_map_ld_ld, "data.xml");
    t_map_ld_ld.clear();
    xml::deserializeStl_xml(t_map_ld_ld, "data.xml");
    p_map_ld_ld = t_map_ld_ld.begin();
    printf("t_map_ld_ld:{(%.15Lf, %.15Lf),", p_map_ld_ld->first, (p_map_ld_ld)->second);p_map_ld_ld++;
    printf("(%.15Lf, %.15Lf),",p_map_ld_ld->first, p_map_ld_ld->second);p_map_ld_ld++;
    printf("(%.15Lf, %.15Lf)}\n",p_map_ld_ld->first, p_map_ld_ld->second);   

    xml::serializeStl_xml(t_map_ll_ld, "data.xml");
    t_map_ll_ld.clear();
    xml::deserializeStl_xml(t_map_ll_ld, "data.xml");
    p_map_ll_ld = t_map_ll_ld.begin();
    printf("t_map_ll_ld:{(%lld, %.15Lf),", p_map_ll_ld->first, (p_map_ll_ld)->second);p_map_ll_ld++;
    printf("(%lld, %.15Lf),",p_map_ll_ld->first, p_map_ll_ld->second);p_map_ll_ld++;
    printf("(%lld, %.15Lf)}\n",p_map_ll_ld->first, p_map_ll_ld->second);

    //自定义类型序列化
    cout <<endl<< ">>>>>>>>>user defined type:"<<endl;
    struct students{
        string name;
        long long ID_number;
        double avg_score;
        std::list<int> course_list;
        //map->first = courseID  map->second = score
        std::map<int, int> score_list;
        //pair->first = studentID pair->second = teacherID
        std::pair<int, int> tutor;
    }stu;
    for(int i=0; i<10; i++){
        stu.course_list.push_back(202000+i);
        stu.score_list.insert(pair<int, int>(202000+i, 80+i));
    }
    stu.tutor.first = 123456;
    stu.tutor.second = 654321;
    stu.name = "Lisa";
    stu.avg_score = 80.32;
    stu.ID_number = 654321;

    cout<<endl<<"before serialization:"<<endl;
    cout<<"name:"<<stu.name <<endl;
    printf("studentID:%lld\navg_score:%lf\n",stu.ID_number ,stu.avg_score );

    cout<<"course_list:";
    std::list<int>::iterator plist= stu.course_list.begin();
    for(int i=0;i<10;i++){
        if(i!=9)
            printf("%d, ", *plist++);
        else
            printf("%d", *plist);
    }
    cout<<endl;

    cout<<"score_list:";
    std::map<int, int>::iterator pmap = stu.score_list.begin();
    for(int i=0;i<10;i++){
        if(i!=9)
            printf("(%d, %d), ", pmap->first, pmap->second );
        else
            printf("(%d, %d)", pmap->first, pmap->second);
        pmap++;
    }
    cout<<endl;
    printf("tutor:%d, %d\n", stu.tutor.first, stu.tutor.second);

    //序列化和反序列化
    userDef::Base1._string = stu.name;
    userDef::Base1._llong = stu.ID_number;
    userDef::Base1._double = stu.avg_score;
    userDef::Base1._list_int = stu.course_list;
    userDef::Base1._map_int = stu.score_list;
    userDef::Base1._pair_int = stu.tutor;

    userDef::structToXml("data.xml");
    userDef::xmlToStruct("data.xml");

    cout<<endl<<"after serialization:"<<endl;
    cout<<"name:"<<userDef::Base2._string<<endl;
    printf("studentID:%lld\navg_score:%lf\n",userDef::Base2._llong, userDef::Base2._double);

    cout<<"course_list:";
    plist= stu.course_list.begin();
    for(int i=0;i<10;i++){
        if(i!=9)
            printf("%d, ", *plist++);
        else
            printf("%d", *plist);
    }
    cout<<endl;

    cout<<"score_list:";
    pmap = stu.score_list.begin();
    for(int i=0;i<10;i++){
        if(i!=9)
            printf("(%d, %d), ", pmap->first, pmap->second );
        else
            printf("(%d, %d)", pmap->first, pmap->second);
        pmap++;
    }
    cout<<endl;
    printf("tutor:%d, %d\n", stu.tutor.first, stu.tutor.second);
}