//====================================================================
//  gzyXML.h
//  created 3.18.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#ifndef GZYXML_H_C1A9C397CF09B78418AD30F93912AA72
#define GZYXML_H_C1A9C397CF09B78418AD30F93912AA72

#include "defines.h"

GZY_NAMESPACE_BEGIN

#define     RESULT_UNKNOWN          -1
#define     RESULT_OK               0
#define     RESULT_BAD_DOC          1
#define     RESULT_LOAD_FAILURE     2
#define     RESULT_FILE_FAILURE     3
#define     RESULT_TAG_NO_NAME      4
#define     RESULT_TAG_ILLEGAL      5

class XMLDocument;
class XMLNode;
//typedef gSharedPtr<XMLNode> XMLNodePtr;
typedef XMLNode * XMLNodePtr;

//#define NEW_XMLNodePtr gSharedPtr<XMLNode>()
#define NEW_XMLNodePtr new XMLNode

#define DEL_PTR delete

class XMLNode
{
    friend class XMLDocument;
public:
    XMLNode();
    ~XMLNode();

public:
    // 返回第一个子节点，无子节点返回nullptr
    XMLNodePtr first_child();

    // 返回指定的孩子节点，可以使用类似路径的索引“aa/bb/cc[2]/dd/”，未找到节点返回nullptr
    XMLNodePtr child(const gString &name_);

    // 遍历查找下一个兄弟节点，无节点返回nullptr
    XMLNodePtr next();

    // 遍历查找上一个兄弟节点，无节点返回nullptr
    XMLNodePtr prev();

    // 遍历同名兄弟节点，类似数组，无节点返回nullptr
    XMLNodePtr array_next();

    // 返回当前节点的名字
    gString name();

    // 返回当前节点的值
    gString value();

    // 返回当前节点的父节点，无父节点返回nullptr
    XMLNodePtr parent();

    // 查找当前节点的属性值，无指定属性返回空字符串
    gString attribute(const gString &name_);

    // 获取此节点拥有的属性名字
    void attributesName(gVector<gString> &list_);

protected:
    bool setName(const gString &name_);
    void setValue(const gString &value_);
    void appendValue(const gString &value_);
    void setAttribute(const gString &name_, const gString &value_);
    void setParent(const XMLNodePtr &parent_);
    void clear();

protected:
    // 添加孩子
    void addChild(const XMLNodePtr &child_);

    // 在map中添加孩子，方便日后查找
    void addChild_map(const XMLNodePtr &child_);

protected:
    // 查看此节点是否已结束
    bool isOver();

    // 设置此节点结束；若已结束，返回false
    bool Over();

private:
    struct Impl;
    Impl *_Impl;
};

class XMLDocument
{
public:
    XMLDocument();
    ~XMLDocument();

public:
    // 从文件读取xml文档解析
    int load_file(const gString &file_path_);

    // 解析xml字符串
    int load_string(const gString &xml_str_);

    // 序列化生成xml字符串
    bool to_string(gString &str_);

public:
    // 清空数据
    void clear();

public:
    // 返回第一个子节点，无子节点返回nullptr
    XMLNodePtr fisrt_child();

    // 返回指定的孩子节点，可以使用类似路径的索引“aa/bb/cc[2]/dd/”，未找到节点返回nullptr
    XMLNodePtr child(const gString &name_);

private:
    struct Impl;
    Impl *_Impl;
};

GZY_NAMESPACE_END

#endif // GZYXML_H_C1A9C397CF09B78418AD30F93912AA72
