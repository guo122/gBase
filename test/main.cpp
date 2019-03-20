
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

    std::ifstream fp("../test/test.xml", std::ios::in);
    std::ofstream ofp("../test/tt.xml", std::ios::out);
    std::string buf;
    std::string xml_str;
    std::string tmpStr = "";
    if (fp.is_open())
    {
        while (getline(fp, buf))
        {
            xml_str += buf + "\n";
        }
    }

    gzy::XMLDocument doc;
    gzy::XMLNodePtr ptr;

    long long t_start, t_end;

    int Result = 0;

    t_start = getTime();

    doc.load_string(xml_str);

    doc.to_string(tmpStr);

    if (ofp.is_open())
    {
        ofp.write(tmpStr.c_str(), tmpStr.size());
    }

//    for (int i = 0; i < 50000; ++i) {
////        doc.load_string(xml_str);
//        doc.load_file("../test/test.xml");
//        ptr = doc.child("wow/characters/character[1]/level");
//        if (ptr)
//        {
//            if (ptr->value() != "65")
//            {
//                Result = 1;
//            }
//        }
//        else
//        {
//            Result = 1;
//        }
//    }


    t_end = getTime();

    std::cout << Result << std::endl;

    std::cout << t_end - t_start << std::endl;




    return 0;
}
