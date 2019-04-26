
#include <iostream>
#include <sys/timeb.h>
#include <fstream>

#include <gzyBase/gXml.h>
#include <gtest/gtest.h>

const char * testXML = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<wow _lang=\"e'n\">\
ll&lt;aa<!----><ss/><aa   >.-bb>\/baa<bb>asd</bb>cccccdddd</aa><characters>\
<character index = \"001\" ad=\"vv\" ><name>AAA</name><level>70</level></character>\
<character index=\"002\"><name>BBB</name><level>65</level></character></characters></wow>";

long long getTime(){
    timeb t;
    ftime(&t);
    return t.time * 1000 + t.millitm;
}

TEST(gXml, Example)
{
    //todo
    std::string tmpStr = "";
    gzy::XMLDocument doc;
    gzy::XMLNodePtr node;

    doc.load_string(testXML);
    doc.to_string(tmpStr);
    std::cout << tmpStr << std::endl;
    std::cout << "--------------------------------" << std::endl;

    doc.load_file("../test/test.xml");
    doc.to_string(tmpStr);
    std::cout << tmpStr << std::endl;
    std::cout << "--------------------------------" << std::endl;

    node = doc.child("wow/characters/character[1]/name");
    if (node)
    {
        std::cout << node->value() << std::endl;

        if (node = node->next())
        {
            std::cout << node->value() << std::endl;
        }
        if (node = node->parent())
        {
            std::cout << node->attribute("index") << std::endl;
        }
    }
}

TEST(gXml, OtherExample)
{
    //todo
    long long t_start, t_end;

    std::ofstream ofp;

    ofp.open("../test/tt.xml", std::ios::out);

    std::string tmpStr = "";

    gzy::XMLDocument doc;
    gzy::XMLNodePtr ptr;
    doc.load_file("../test/test.xml");
    doc.to_string(tmpStr);

    t_start = getTime();
    for (int i = 0; i < 500000; ++i) {
//        doc.load_string(xml_str);
        doc.load_file("../test/test.xml");
//        doc.load_string(tmpStr);
        doc.to_string(tmpStr);
//        doc.to_string(tmpStr);
    }
    t_end = getTime();
    std::cout << t_end - t_start << std::endl;

    if (ofp.is_open())
    {
        ofp.write(tmpStr.c_str(), tmpStr.size());
    }
    ofp.close();

    std::cin >> tmpStr;
}
