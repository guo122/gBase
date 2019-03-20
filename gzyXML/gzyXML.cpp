//====================================================================
//  gzyXML.cpp
//  created 3.18.19
//  written by gzy
//
//  https://github.com/guo122/gzyBase
//====================================================================

#include <map>
#include <vector>

#include "gzyXML.h"

GZY_NAMESPACE_BEGIN

enum meta_type
{
    end = 0,            // tag外
    just_begin,         // 刚刚读取到 < 标志

    // 相对顺序固定
    declaration_over,
    declaration,
    declaration_end,
    decl_attri_name,
    decl_attri_name_end,    //声明属性名字结束，准备读取值
    decl_attri_value_apos,  //声明属性，单引号包围
    decl_attri_value_quot,  //双引号包围

    // 相对顺序固定
    tag,
    tag_end,
    tag_attri_name,
    tag_attri_name_end,     //普通属性名字结束，准备读取值
    tag_attri_value_apos,   //普通属性，单引号包围
    tag_attri_value_quot,   //双引号包围

    end_tag,

    comment,
    error
};

struct XMLNode::Impl
{
    Impl()
        : _name("")
        , _value("")
        , _prev(nullptr)
        , _next(nullptr)
        , _array_next(nullptr)
        , _parent(nullptr)
        , _first_child(nullptr)
        , _last_child(nullptr)
        , _overFlag(false)
    {}

    XMLNodePtr child_Impl(const std::string &name_)
    {
        XMLNodePtr Result = nullptr;
        std::string lastStr = name_;
        std::string idxStr = "";
        std::string curStr = "";
        int index = 0;

        idxStr = lastStr.substr(0, lastStr.find_first_of('/'));
        curStr = idxStr.substr(0, idxStr.find_first_of('['));
        lastStr.erase(0, lastStr.find_first_of('/') + 1);
        // 判断是否有下标
        idxStr.erase(0, idxStr.find_first_of('['));
        if (idxStr.size() > 2)
        {
            idxStr.erase(0, 1);
            idxStr.erase(idxStr.size() - 1, 1);
            index = std::atoi(idxStr.c_str());
        }

        if (!_childrenMap[curStr].empty())
        {
            if (index < 0 || index >= _childrenMap[curStr].size())
            {
                index = 0;
            }
            if (lastStr.empty())
            {
                // 当前目标
                Result = _childrenMap[curStr][index];
            }
            else
            {
                // 递归
                Result = _childrenMap[curStr][index]->_Impl->child_Impl(lastStr);
            }
        }

        return Result;
    }

    std::string _name;
    std::string _value;
    std::map<std::string, std::string> _attriMap;
    std::vector<std::string> _attriNameList;

    XMLNodePtr _prev;
    XMLNodePtr _next;
    // 用于同名tag
    XMLNodePtr _array_next;

    XMLNodePtr _parent;
    XMLNodePtr _first_child;
    XMLNodePtr _last_child;
    std::map<std::string, std::vector<XMLNodePtr>> _childrenMap;

    // 解析xml时判断tag对 是否结束
    bool _overFlag;
};

XMLNode::XMLNode()
    : _Impl(new Impl)
{

}
XMLNode::~XMLNode()
{
    clear();
    delete _Impl;
    _Impl = nullptr;
}

XMLNodePtr XMLNode::first_child()
{
    return _Impl->_first_child;
}

XMLNodePtr XMLNode::child(const std::string &name_)
{
    XMLNodePtr Result = nullptr;
    std::string tmpStr = name_;

    // 格式化字符串
    // 去掉前面多余的正斜线
    if (tmpStr.size() > 0 && tmpStr[0] == '/')
    {
        tmpStr.erase(0, 1);
    }
    // 增加尾部必须的正斜线
    if (tmpStr.size() > 0 && tmpStr[tmpStr.size() - 1] != '/')
    {
        tmpStr.push_back('/');
    }

    Result = _Impl->child_Impl(tmpStr);

    return Result;
}

XMLNodePtr XMLNode::next()
{
    return _Impl->_next;
}

XMLNodePtr XMLNode::prev()
{
    return _Impl->_prev;
}

XMLNodePtr XMLNode::array_next()
{
    return _Impl->_array_next;
}

bool XMLNode::setName(const std::string &name_)
{
    bool Result = false;
    typeof (std::find(name_.begin(), name_.end(), '/')) it;
    if ( (it = std::find(name_.begin(), name_.end(), '/')) == name_.end() &&
         (it = std::find(name_.begin(), name_.end(), '[')) == name_.end() &&
         (it = std::find(name_.begin(), name_.end(), ']')) == name_.end())
    {
        _Impl->_name = name_;
        Result = true;
    }

    return Result;
}

std::string XMLNode::name()
{
    return _Impl->_name;
}

void XMLNode::setValue(const std::string &value_)
{
    _Impl->_value = value_;
}

void XMLNode::appendValue(const std::string &value_)
{
    _Impl->_value += value_;
}

std::string XMLNode::value()
{
    return _Impl->_value;
}

void XMLNode::setAttribute(const std::string &name_, const std::string &value_)
{
    _Impl->_attriMap[name_] = value_;
    auto it = std::find(_Impl->_attriNameList.begin(), _Impl->_attriNameList.end(), name_);
    if (it == _Impl->_attriNameList.end())
    {
        _Impl->_attriNameList.push_back(name_);
    }
}

void XMLNode::addChild(const XMLNodePtr &child_)
{
    if (!_Impl->_first_child)
    {
        _Impl->_first_child = _Impl->_last_child = child_;
    }
    else
    {
        _Impl->_last_child->_Impl->_next = child_;
        child_->_Impl->_prev = _Impl->_last_child;
        _Impl->_last_child = child_;
    }
}

void XMLNode::addChild_map(const XMLNodePtr &child_)
{
    int tmpSize = 0;
    if (child_ && !child_->name().empty())
    {
        _Impl->_childrenMap[child_->name()].push_back(child_);
        tmpSize = _Impl->_childrenMap[child_->name()].size();
        if (tmpSize > 1)
        {
            _Impl->_childrenMap[child_->name()][tmpSize - 1]->_Impl->_array_next = child_;
        }
    }
}

void XMLNode::setParent(const XMLNodePtr &parent_)
{
    _Impl->_parent = parent_;
}

void XMLNode::clear()
{
    XMLNodePtr last_cur = nullptr;
    XMLNodePtr cur = nullptr;
    for (cur = _Impl->_first_child; cur != nullptr; cur = cur->_Impl->_next)
    {
        if (last_cur)
        {
            DEL_PTR last_cur;
            last_cur = nullptr;
        }
        cur->clear();
        last_cur = cur;

    }
    if (last_cur)
    {
        DEL_PTR last_cur;
        last_cur = nullptr;
    }
    _Impl->_first_child = nullptr;
}

XMLNodePtr XMLNode::parent()
{
    return _Impl->_parent;
}

std::string XMLNode::attribute(const std::string &name_)
{
    return _Impl->_attriMap[name_];
}

void XMLNode::attributesName(std::vector<std::string> &list_)
{
    list_.clear();
    list_.insert(list_.end(), _Impl->_attriNameList.begin(), _Impl->_attriNameList.end());
}

bool XMLNode::isOver()
{
    return _Impl->_overFlag;
}
bool XMLNode::Over()
{
    bool Result = !_Impl->_overFlag;
    _Impl->_overFlag = true;
    return Result;
}

struct XMLDocument::Impl
{
    Impl()
        : _root(nullptr)
        , _decl(nullptr)
    {}

    // pos2_ 为超尾 下标
    bool XMLSlice(const std::string &xml_, int &pos1_, const int &pos2_, std::string &str_)
    {
        bool Result = false;
        if (pos1_ >= 0 && pos1_ < xml_.size() &&
                pos2_ >= 0 && pos2_ < xml_.size() &&
                pos1_ <= pos2_)
        {
            str_ = xml_.substr(pos1_, pos2_ - pos1_);
            pos1_ = -1;
            Result = true;
        }
        return Result;
    }

    void ToString_Impl(const XMLNodePtr &ptr_, const std::string &indent_, std::string &str_, std::vector<std::string> &attriList_)
    {
        std::string tmpStr;
        typeof (std::find(tmpStr.begin(), tmpStr.end(), ' ')) it;
        XMLNodePtr cur = nullptr;
        str_ += "\n" + indent_ + "<" + ptr_->name();
        ptr_->attributesName(attriList_);
        for (const auto &x: attriList_)
        {
            // 添加属性
            tmpStr = ptr_->attribute(x);
            it = std::find(tmpStr.begin(), tmpStr.end(), '\'');
            if (it == tmpStr.end())
            {
                str_ += " " + x + "='" + tmpStr + "'";
            }
            else
            {
                str_ += " " + x + "=\"" + tmpStr + "\"";
            }
        }
        if (!ptr_->first_child() && ptr_->value().empty())
        {
            // 提前结束
            str_ += "/>";
        }
        else
        {
            str_ += ">" + ptr_->value();

            for (cur = ptr_->first_child(); cur != nullptr; cur = cur->next())
            {
                // 子节点
                ToString_Impl(cur, indent_ + "    ", str_, attriList_);
            }
            if (ptr_->first_child())
            {
                str_ += "\n" + indent_;
            }
            str_ += "</" + ptr_->name() + ">";
        }
    }

    XMLNodePtr _root;
    XMLNodePtr _decl;
};

XMLDocument::XMLDocument()
    : _Impl(new Impl)
{
}

XMLDocument::~XMLDocument()
{
    clear();
    delete _Impl;
    _Impl = nullptr;
}

int XMLDocument::load_file(const std::string &file_path_)
{
    int Result = RESULT_UNKNOWN;

    FILE * fp(fopen(file_path_.c_str(), "rb"));

    if (fp)
    {
        fseek(fp, 0, SEEK_END);
        long long length = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        char * buf = static_cast<char *>(malloc(length + 1));
        fread(buf, 1, length, fp);

        Result = load_string(buf);

        if (buf)
        {
            delete [] buf;
        }
    }
    else
    {
        Result = RESULT_FILE_FAILURE;
    }
    fclose(fp);

    return Result;
}

int XMLDocument::load_string(const std::string &xml_str_)
{
    int Result = RESULT_UNKNOWN;

    clear();

    meta_type curType = meta_type::end;
    int markPos = -1;
    std::string lastAttriName = "";
    std::string tmpStr = "";
    XMLNodePtr cur = nullptr;
    XMLNodePtr tmpNodePtr = nullptr;

    _Impl->_decl = NEW_XMLNodePtr;

    for (size_t i = 0; i < xml_str_.size(); ++i)
    {
        switch (curType)
        {
        case meta_type::end:
            if (xml_str_[i] == '<')
            {
                curType = meta_type::just_begin;
                if (cur && _Impl->XMLSlice(xml_str_, markPos, i, tmpStr))
                {
                    if (cur->value().empty() && !tmpStr.empty())
                    {
                        cur->setValue(tmpStr.substr(0, tmpStr.find_last_of('\n')));
                    }
                }
            }
            else
            {
                if (markPos <= 0)
                {
                    markPos = i;
                }
            }
            break;

        case meta_type::just_begin:
            if (xml_str_[i] == '?')
            {
                curType = meta_type::declaration;
                cur = _Impl->_decl;
                markPos = i + 1;
            }
            else if (xml_str_[i] == '!')
            {
                curType = meta_type::comment;
                if (i + 5 < xml_str_.size() &&
                        xml_str_[i + 1] == '-' &&
                        xml_str_[i + 2] == '-')
                {
                    i = i + 2;
                }
                else
                {
                    Result = RESULT_BAD_DOC;
                    curType = meta_type::error;
                }
            }
            else if (xml_str_[i] == '/')
            {
                curType = meta_type::end_tag;
                markPos = i + 1;
            }
            else if ((xml_str_[i] >= 'a' && xml_str_[i] <= 'z') ||
                     (xml_str_[i] >= 'A' && xml_str_[i] <= 'Z') ||
                     xml_str_[i] == '_'
                     )
            {
                curType = meta_type::tag;
                markPos = i;

                tmpNodePtr = NEW_XMLNodePtr;

                if (!_Impl->_root)
                {
                    cur = _Impl->_root = tmpNodePtr;
                }
                else
                {
                    if (cur)
                    {
                        cur->addChild(tmpNodePtr);
                        tmpNodePtr->setParent(cur);
                        cur = tmpNodePtr;
                    }
                    else
                    {
                        Result = RESULT_UNKNOWN;
                        curType = meta_type::error;
                    }
                }
            }
            else
            {
                Result = RESULT_BAD_DOC;
                curType = meta_type::error;
            }
            break;

        case meta_type::end_tag:
            // 读取结束tag
            if (xml_str_[i] == '>' || xml_str_[i] == ' ')
            {
                if (!_Impl->XMLSlice(xml_str_, markPos, i, tmpStr))
                {
                    Result = RESULT_BAD_DOC;
                    curType = meta_type::error;
                }
                else
                {
                    // 匹配名字，是否配对
                    if (cur && cur->name() == tmpStr && cur->Over())
                    {
                        if (cur->parent())
                        {
                            // 将子节点添加到父节点map中
                            cur->parent()->addChild_map(cur);
                        }

                        cur = cur->parent();
                    }
                    else
                    {
                        Result = RESULT_BAD_DOC;
                        curType = meta_type::error;
                    }
                }
            }
            if (xml_str_[i] == '>')
            {
                curType = meta_type::end;
                if (!cur)
                {
                    Result = RESULT_OK;
                }
            }
            break;

        case meta_type::comment:
            if (xml_str_[i] == '-')
            {
                if ((i + 2) < xml_str_.size() &&
                        xml_str_[i + 1] == '-' &&
                        xml_str_[i + 2] == '>')
                {
                    curType = meta_type::end;
                    i = i + 2;
                }
                else
                {
                    Result = RESULT_BAD_DOC;
                    curType = meta_type::error;
                }
            }
            break;

        case meta_type::declaration:
            if (xml_str_[i] == ' ')
            {
                curType = meta_type::declaration_end;

                if (!_Impl->XMLSlice(xml_str_, markPos, i, tmpStr))
                {
                    Result = RESULT_UNKNOWN;
                    curType = meta_type::error;
                }
                if (tmpStr.empty())
                {
                    Result = RESULT_TAG_NO_NAME;
                    curType = meta_type::error;
                }
                if (!cur->setName(tmpStr))
                {
                    Result = RESULT_TAG_ILLEGAL;
                    curType = meta_type::error;
                }
            }
            break;

        case meta_type::declaration_end:
            if (xml_str_[i] == '?')
            {
                curType = meta_type::declaration_over;
            }
            else if ((xml_str_[i] >= 'a' && xml_str_[i] <= 'z') ||
                    (xml_str_[i] >= 'A' && xml_str_[i] <= 'Z'))
            {
                curType = meta_type::decl_attri_name;
                markPos = i;
            }
            else if (xml_str_[i] != ' ')
            {
                Result = RESULT_BAD_DOC;
                curType = meta_type::error;
            }
            break;

        case meta_type::declaration_over:
            if (xml_str_[i] == '>')
            {
                curType = meta_type::end;
            }
            else
            {
                Result = RESULT_BAD_DOC;
                curType = meta_type::error;
            }
            break;

        case meta_type::tag:
            if (xml_str_[i] == '>')
            {
                // 读取完毕无属性的tag
                curType = meta_type::end;
                if (!_Impl->XMLSlice(xml_str_, markPos, i, tmpStr))
                {
                    Result = RESULT_UNKNOWN;
                    curType = meta_type::error;
                }
                if ((i - 1) >= 0 && xml_str_[i - 1] == '/')
                {
                    // 此无属性tag提前结束
                    if (!cur || !cur->Over())
                    {
                        Result = RESULT_BAD_DOC;
                        curType = meta_type::error;
                    }
                    tmpStr.erase(tmpStr.size() - 1, 1);
                }
                if (tmpStr.empty())
                {
                    Result = RESULT_TAG_NO_NAME;
                    curType = meta_type::error;
                }
                if (!cur->setName(tmpStr))
                {
                    Result = RESULT_TAG_ILLEGAL;
                    curType = meta_type::error;
                }
                if (cur->isOver())
                {
                    if (cur->parent())
                    {
                        // 将子节点添加到父节点map中
                        cur->parent()->addChild_map(cur);
                    }
                    cur = cur->parent();
                    if (!cur)
                    {
                        Result = RESULT_OK;
                    }
                }
            }
            else if (xml_str_[i] == ' ')
            {
                curType = meta_type::tag_end;
                if (!_Impl->XMLSlice(xml_str_, markPos, i, tmpStr))
                {
                    Result = RESULT_UNKNOWN;
                    curType = meta_type::error;
                }
                if (tmpStr.empty())
                {
                    Result = RESULT_TAG_NO_NAME;
                    curType = meta_type::error;
                }
                if (!cur->setName(tmpStr))
                {
                    Result = RESULT_TAG_ILLEGAL;
                    curType = meta_type::error;
                }
            }
            break;

        case meta_type::tag_end:
            // tag名字已读取，准备读属性或结束标志 >
            if (xml_str_[i] == '>')
            {
                // 结束tag
                curType = meta_type::end;
                if ((i - 1) >= 0 && xml_str_[i - 1] == '/')
                {
                    // 单标签，同时开始结束
                    if (cur && cur->Over())
                    {
                        if (cur->parent())
                        {
                            // 将子节点添加到父节点map中
                            cur->parent()->addChild_map(cur);
                        }
                        cur = cur->parent();
                    }
                    else
                    {
                        Result = RESULT_BAD_DOC;
                        curType = meta_type::error;
                    }
                }
            }
            else if ((xml_str_[i] >= 'a' && xml_str_[i] <= 'z') ||
                    (xml_str_[i] >= 'A' && xml_str_[i] <= 'Z') ||
                     xml_str_[i] == '_')
            {
                curType = meta_type::tag_attri_name;
                markPos = i;
            }
            else if (xml_str_[i] != ' ')
            {
                Result = RESULT_BAD_DOC;
                curType = meta_type::error;
            }
            break;

        case meta_type::decl_attri_name:
        case meta_type::tag_attri_name:
            if (xml_str_[i] == ' ' || xml_str_[i] == '=')
            {
                // 依赖meta_type中元素顺序 状态变成对应的 _end
                curType = static_cast<meta_type>(static_cast<int>(curType) + 1);

                // in
                if (!_Impl->XMLSlice(xml_str_, markPos, i, lastAttriName))
                {
                    Result = RESULT_UNKNOWN;
                    curType = meta_type::error;
                }
            }
            break;

        case meta_type::decl_attri_name_end:
        case meta_type::tag_attri_name_end:
            if (xml_str_[i] == '\'')
            {
                // 依赖meta_type中元素顺序 状态变成对应的 _apos
                curType = static_cast<meta_type>(static_cast<int>(curType) + 1);
                markPos = i + 1;
            }
            else if (xml_str_[i] == '"')
            {
                // 依赖meta_type中元素顺序 状态变成对应的 _quot
                curType = static_cast<meta_type>(static_cast<int>(curType) + 2);
                markPos = i + 1;
            }
            break;

        case meta_type::decl_attri_value_apos:
        case meta_type::tag_attri_value_apos:
            if (xml_str_[i] == '\'')
            {
                // 依赖meta_type中元素顺序 返回 decl_end 或 tag_end 状态
                curType = static_cast<meta_type>(static_cast<int>(curType) - 3);

                if (!_Impl->XMLSlice(xml_str_, markPos, i, tmpStr))
                {
                    Result = RESULT_UNKNOWN;
                    curType = meta_type::error;
                }
                cur->setAttribute(lastAttriName, tmpStr);
            }
            break;

        case meta_type::decl_attri_value_quot:
        case meta_type::tag_attri_value_quot:
            if (xml_str_[i] == '"')
            {
                // 依赖meta_type中元素顺序 返回 decl_end 或 tag_end 状态
                curType = static_cast<meta_type>(static_cast<int>(curType) - 4);

                if (!_Impl->XMLSlice(xml_str_, markPos, i, tmpStr))
                {
                    Result = RESULT_UNKNOWN;
                    curType = meta_type::error;
                }
                cur->setAttribute(lastAttriName, tmpStr);
            }
            break;

        case meta_type::error:
            i = xml_str_.size() - 1;
            break;
        }
    }

    return Result;
}

bool XMLDocument::to_string(std::string &str_)
{
    bool Result = false;

    std::vector<std::string> list;
    std::string tmpStr = "";
    typeof (std::find(tmpStr.begin(), tmpStr.end(), ' ')) it;
    if (_Impl->_root && _Impl->_decl)
    {
        str_.clear();
        Result = true;

        if (!_Impl->_decl->name().empty())
        {
            str_ += "<?" + _Impl->_decl->name();

            _Impl->_decl->attributesName(list);
            for (const auto &x: list)
            {
                tmpStr = _Impl->_decl->attribute(x);
                it = std::find(tmpStr.begin(), tmpStr.end(), '\'');
                if (it == tmpStr.end())
                {
                    str_ += " " + x + "='" + tmpStr + "'";
                }
                else
                {
                    str_ += " " + x + "=\"" + tmpStr + "\"";
                }
            }

            str_ += "?>";
        }

        _Impl->ToString_Impl(_Impl->_root, "", str_, list);
    }

    return Result;
}

void XMLDocument::clear()
{
    if (_Impl->_decl)
    {
        DEL_PTR _Impl->_decl;
        _Impl->_decl = nullptr;
    }
    if (_Impl->_root)
    {
        _Impl->_root->clear();
        DEL_PTR _Impl->_root;
        _Impl->_root = nullptr;
    }
}

XMLNodePtr XMLDocument::fisrt_child()
{
    XMLNodePtr Result = _Impl->_root;
    return Result;
}

XMLNodePtr XMLDocument::child(const std::string &name_)
{
    XMLNodePtr Result = nullptr;
    std::string lastStr = name_;
    std::string curStr;
    // 去掉前面多余的正斜线
    if (lastStr.size() > 0 && lastStr[0] == '/')
    {
        lastStr.erase(0, 1);
    }
    // 增加尾部必须的正斜线
    if (lastStr.size() > 0 && lastStr[lastStr.size() - 1] != '/')
    {
        lastStr.push_back('/');
    }
    curStr = lastStr.substr(0, lastStr.find_first_of('/'));
    lastStr.erase(0, lastStr.find_first_of('/') + 1);

    if (_Impl->_root && curStr == _Impl->_root->name())
    {
        if (lastStr.empty())
        {
            Result = _Impl->_root;
        }
        else
        {
            Result = _Impl->_root->child(lastStr);
        }
    }

    return Result;
}

GZY_NAMESPACE_END
