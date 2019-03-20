
#include <iostream>
#include <sys/timeb.h>
#include <fstream>

#include <gzyXML/gzyXML.h>

const char * testXML = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<wow _lang=\"e'n\">\
ll&lt;aa<!----><ss/><aa   >.-bb>\/baa<bb>asd</bb>cccccdddd</aa><characters>\
<character index = \"001\" ad=\"vv\" ><name>AAA</name><level>70</level></character>\
<character index=\"002\"><name>BBB</name><level>65</level></character></characters></wow>";

void tesssssss(gzy::XMLDocument &doc_, const std::string &name_)
{
    gzy::XMLNodePtr ptr;
    ptr = doc_.child(name_);
    std::cout << "----------------------------------" << std::endl;
    std::cout << name_ << std::endl;
    if (ptr)
    {
        std::cout << ptr->name() << ": " << ptr->value() << std::endl;
    }
    else
    {
        std::cout << "---wrong---" << std::endl;
    }
}

long long getTime(){
    timeb t;
    ftime(&t);
    return t.time * 1000 + t.millitm;
}

int main(int argc, char *argv[])
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

    return 0;
}
