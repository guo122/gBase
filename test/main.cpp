
#include <iostream>

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

int main(int argc, char *argv[])
{
    gzy::XMLDocument doc;
    gzy::XMLNodePtr ptr;

    std::string tmpStr = "";

    if (doc.load_file("../test/test.xml") == RESULT_OK)
    {
//        tesssssss(doc, "wow/characters/character");
//        tesssssss(doc, "wow/characters/character/name");
//        tesssssss(doc, "/wow/characters/character[1]/level[]");
//        tesssssss(doc, "/wow/characters/character[2]/level");
//        tesssssss(doc, "/wow/characters/character[-2]/level");
//        tesssssss(doc, "/wow/characters/character[345]/level");
//        tesssssss(doc, "/wow/characters/character[]/level");
//        tesssssss(doc, "/wow/characters/character[v]/level");

//        tesssssss(doc, "/wow/ss");
//        tesssssss(doc, "/wow/aa");

        ptr = doc.child("wow/characters/character");

        if (ptr)
        {
            std::cout << ptr->child("name")->name() << ": " << ptr->child("name")->value() << std::endl;
            ptr = ptr->next();
        }
        if (ptr)
        {
            std::cout << ptr->child("name")->name() << ": " << ptr->child("name")->value() << std::endl;
            ptr = ptr->next();
        }
        if (ptr)
        {
            std::cout << ptr->name() << ": " << ptr->value() << std::endl;
            ptr = ptr->next();
        }

    }

    return 0;
}
