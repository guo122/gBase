
#include <iostream>
#include <sys/timeb.h>
#include <fstream>

#include <gzyXML/gzyXML.h>

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

void example()
{
    std::string tmpStr = "";
    // 创建文档，节点
    gzy::XMLDocument doc;
    gzy::XMLNodePtr node;

    // 从字符串解析
    doc.load_string(testXML);
    // 序列化
    doc.to_string(tmpStr);
    // 输出结果
    std::cout << tmpStr << std::endl;
    std::cout << "--------------------------------" << std::endl;

    // 从文件解析
    doc.load_file("../test/test.xml");
    // 序列化
    doc.to_string(tmpStr);
    // 输出结果
    std::cout << tmpStr << std::endl;
    std::cout << "--------------------------------" << std::endl;

    // 获取节点
    node = doc.child("wow/characters/character[1]/name");
    if (node)
    {
        // 获取该节点的值
        std::cout << node->value() << std::endl;

        if (node = node->next())
        {
            // 获取该节点的兄弟节点
            std::cout << node->value() << std::endl;
        }
        if (node = node->parent())
        {
            // 获取父节点的属性
            std::cout << node->attribute("index") << std::endl;
        }
    }
}

void otherExample();

int main(int argc, char *argv[])
{
    // 例子
    example();

    return 0;
}

void otherExample()
{
    long long t_start, t_end;

    std::ofstream ofp;

    ofp.open("../test/tt.xml", std::ios::out);

    std::string tmpStr = "";

    gzy::XMLDocument doc;
    gzy::XMLNodePtr ptr;

    t_start = getTime();
    for (int i = 0; i < 50000; ++i) {
//        doc.load_string(xml_str);
        doc.load_file("../test/test.xml");
        doc.to_string(tmpStr);
    }
    t_end = getTime();
    std::cout << t_end - t_start << std::endl;

    if (ofp.is_open())
    {
        ofp.write(tmpStr.c_str(), tmpStr.size());
    }
    ofp.close();
}
