
#include <iostream>

#include <gzyXML/gzyXML.h>

const char * testXML = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<wow _lang=\"e'n\">\
ll&lt;aa<!----><ss/><aa   >.-bb>\/baa<bb>asd</bb>cccccdddd</aa><characters>\
<character index = \"001\" ad=\"vv\" ><name>AAA</name><level>70</level></character>\
<character index=\"002\"><name>BBB</name><level>65</level></character></characters></wow>";

int main(int argc, char *argv[])
{
    std::cout << "Hello World" << std::endl;

    std::string tmpStr = testXML;

    gzy::XMLDocument doc;

    std::cout << doc.load_string(testXML) << std::endl;


    return 0;
}
