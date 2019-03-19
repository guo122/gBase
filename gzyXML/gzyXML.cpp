//====================================================================
//  gzyXML.cpp
//  created 3.18.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#include <map>
#include <string>
#include <vector>

#include "gzyXML.h"

GZY_NAMESPACE_BEGIN

enum meta_type
{
    end = 0,            // 初始状态
    just_begin,         // 刚刚读取到 < 标志

    // 相对顺序固定
    declaration_over,
    declaration,
    declaration_end,
    decl_attri_name,
    decl_attri_name_end,
    decl_attri_value_apos,
    decl_attri_value_quot,

    // 相对顺序固定
    tag,
    tag_end,
    tag_attri_name,
    tag_attri_name_end,
    tag_attri_value_apos,
    tag_attri_value_quot,

    element,
    element_end,

    end_tag,

    comment,
    comment_1,
    comment_2,
    comment_3,
    comment_4,
    comment_end
};

struct attribute_struct
{
    attribute_struct(const std::string &name_, const std::string &value_)
        : _name(name_)
        , _value(value_)
    {}

    std::string	_name;
    std::string	_value;
};

struct XMLNode::Impl
{
    Impl()
        : _name("")
        , _value("")
        , _parent(nullptr)
        , _overFlag(false)
    {}

    std::string _name;
    std::string _value;
    std::vector<attribute_struct> _attriList;

    XMLNodePtr _parent;
    std::vector<XMLNodePtr> _children;

    bool _overFlag;
};

XMLNode::XMLNode()
    : _Impl(new Impl)
{

}
XMLNode::~XMLNode()
{
    delete _Impl;
    _Impl = nullptr;
}

void XMLNode::SetName(const std::string &name_)
{
    _Impl->_name = name_;
}

std::string XMLNode::GetName()
{
    return _Impl->_name;
}

void XMLNode::SetValue(const std::string &value_)
{
    _Impl->_value = value_;
}

void XMLNode::AppendValue(const std::string &value_)
{
    _Impl->_value += value_;
}

std::string XMLNode::GetValue()
{
    return _Impl->_value;
}

void XMLNode::AddAttribute(const std::string &name_, const std::string &value_)
{
    _Impl->_attriList.push_back(attribute_struct(name_, value_));
}

void XMLNode::AddChild(const XMLNodePtr &child_)
{
    _Impl->_children.push_back(child_);
}

void XMLNode::SetParent(const XMLNodePtr &parent_)
{
    _Impl->_parent = parent_;
}

XMLNodePtr XMLNode::GetParent()
{
    return _Impl->_parent;
}

bool XMLNode::IsOver()
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

    XMLNodePtr _root;
    XMLNodePtr _decl;
    std::map<std::string, bool> _tagMap;
};

XMLDocument::XMLDocument()
    : _Impl(new Impl)
{
}

XMLDocument::~XMLDocument()
{
    delete _Impl;
    _Impl = nullptr;
}

int XMLDocument::load_file(const std::string &file_path_)
{
    int Result = RESULT_UNKNOWN;
    return Result;
}

int XMLDocument::load_string(const std::string &xml_str_)
{
    int Result = RESULT_UNKNOWN;

    meta_type curType = meta_type::end;
    int markPos = -1;
    std::string lastAttriName = "";
    std::string tmpStr = "";
    XMLNodePtr cur = nullptr;
    XMLNodePtr tmpNodePtr = nullptr;

    _Impl->_decl = std::make_shared<XMLNode>();

    char tmpC;

    for (size_t i = 0; i < xml_str_.size(); ++i)
    {
        tmpC = xml_str_[i];
        if (curType == meta_type::end)
        {
            if (xml_str_[i] == '<')
            {
                curType = meta_type::just_begin;
            }
            else
            {
                curType = meta_type::element;
                markPos = i;
            }
        }
        else if (curType == meta_type::element)
        {
            if (xml_str_[i] == '<' && cur)
            {
                curType = meta_type::just_begin;
                if (!_Impl->XMLSlice(xml_str_, markPos, i, tmpStr))
                {
                    Result = RESULT_UNKNOWN;
                    break;
                }
                cur->AppendValue(tmpStr);
            }
        }
        else if (curType == meta_type::just_begin)
        {
            if (xml_str_[i] == '?')
            {
                curType = meta_type::declaration;
                cur = _Impl->_decl;
                markPos = i + 1;
            }
            else if (xml_str_[i] == '!')
            {
                curType = meta_type::comment;
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

                tmpNodePtr = std::make_shared<XMLNode>();

                if (!_Impl->_root)
                {
                    cur = _Impl->_root = tmpNodePtr;
                }
                else
                {
                    if (cur)
                    {
                        cur->AddChild(tmpNodePtr);
                        tmpNodePtr->SetParent(cur);
                        cur = tmpNodePtr;
                    }
                    else
                    {
                        Result = RESULT_UNKNOWN;
                        break;
                    }
                }
            }
            else
            {
                Result = RESULT_BAD_DOC;
                break;
            }
        }
        else if (curType == meta_type::end_tag)
        {
            if (xml_str_[i] == '>' || xml_str_[i] == ' ')
            {
                if (!_Impl->XMLSlice(xml_str_, markPos, i, tmpStr))
                {
                    Result = RESULT_BAD_DOC;
                    break;
                }
                else
                {
                    if (cur && cur->GetName() == tmpStr && cur->Over())
                    {
                        cur = cur->GetParent();
                    }
                    else
                    {
                        Result = RESULT_BAD_DOC;
                        break;
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
        }
        else if (curType == meta_type::comment)
        {
            if (xml_str_[i] == '-')
            {
                curType = meta_type::comment_1;
            }
            else
            {
                Result = RESULT_BAD_DOC;
                break;
            }
        }
        else if (curType == meta_type::comment_1)
        {
            if (xml_str_[i] == '-')
            {
                curType = meta_type::comment_2;
            }
            else
            {
                Result = RESULT_BAD_DOC;
                break;
            }
        }
        else if (curType == meta_type::comment_2)
        {
            if (xml_str_[i] == '-')
            {
                curType = meta_type::comment_3;
            }
        }
        else if (curType == meta_type::comment_3)
        {
            if (xml_str_[i] == '-')
            {
                curType = meta_type::comment_4;
            }
            else
            {
                Result = RESULT_BAD_DOC;
                break;
            }
        }
        else if (curType == meta_type::comment_4)
        {
            if (xml_str_[i] == '>')
            {
                curType = meta_type::end;
            }
            else
            {
                Result = RESULT_BAD_DOC;
                break;
            }
        }
        else if (curType == meta_type::declaration)
        {
            if (xml_str_[i] == ' ')
            {
                curType = meta_type::declaration_end;

                if (!_Impl->XMLSlice(xml_str_, markPos, i, tmpStr))
                {
                    Result = RESULT_UNKNOWN;
                    break;
                }
                cur->SetName(tmpStr);
            }
        }
        else if (curType == meta_type::declaration_end)
        {
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
                break;
            }
        }
        else if (curType == meta_type::declaration_over)
        {
            if (xml_str_[i] == '>')
            {
                curType = meta_type::end;
            }
            else
            {
                Result = RESULT_BAD_DOC;
                break;
            }
        }
        else if (curType == meta_type::tag)
        {
            if (xml_str_[i] == '>')
            {
                curType = meta_type::end;
                if (!_Impl->XMLSlice(xml_str_, markPos, i, tmpStr))
                {
                    Result = RESULT_UNKNOWN;
                    break;
                }
                cur->SetName(tmpStr);
                if ((i - 1) >= 0 && xml_str_[i - 1] == '/')
                {
                    if (cur && cur->Over())
                    {
                        cur = cur->GetParent();
                    }
                    else
                    {
                        Result = RESULT_BAD_DOC;
                        break;
                    }
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
                    break;
                }
                cur->SetName(tmpStr);
            }
        }
        else if (curType == meta_type::tag_end)
        {
            if (xml_str_[i] == '>')
            {
                curType = meta_type::end;
                if ((i - 1) >= 0 && xml_str_[i - 1] == '/')
                {
                    if (cur && cur->Over())
                    {
                        cur = cur->GetParent();
                    }
                    else
                    {
                        Result = RESULT_BAD_DOC;
                        break;
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
                break;
            }
        }
        else if (curType == meta_type::decl_attri_name ||
                 curType == meta_type::tag_attri_name)
        {
            if (xml_str_[i] == ' ' || xml_str_[i] == '=')
            {
                // 依赖meta_type中元素顺序 状态变成对应的 _end
                curType = static_cast<meta_type>(static_cast<int>(curType) + 1);

                // in
                if (!_Impl->XMLSlice(xml_str_, markPos, i, lastAttriName))
                {
                    Result = RESULT_UNKNOWN;
                    break;
                }
            }
        }
        else if (curType == meta_type::decl_attri_name_end ||
                 curType == meta_type::tag_attri_name_end)
        {
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
        }
        else if (curType == meta_type::decl_attri_value_apos ||
                 curType == meta_type::tag_attri_value_apos)
        {
            if (xml_str_[i] == '\'')
            {
                // 依赖meta_type中元素顺序 返回 decl_end 或 tag_end 状态
                curType = static_cast<meta_type>(static_cast<int>(curType) - 3);

                // in
                if (!_Impl->XMLSlice(xml_str_, markPos, i, tmpStr))
                {
                    Result = RESULT_UNKNOWN;
                    break;
                }
                cur->AddAttribute(lastAttriName, tmpStr);
            }
        }
        else if (curType == meta_type::decl_attri_value_quot ||
                 curType == meta_type::tag_attri_value_quot)
        {
            if (xml_str_[i] == '"')
            {
                // 依赖meta_type中元素顺序 返回 decl_end 或 tag_end 状态
                curType = static_cast<meta_type>(static_cast<int>(curType) - 4);

                // in
                if (!_Impl->XMLSlice(xml_str_, markPos, i, tmpStr))
                {
                    Result = RESULT_UNKNOWN;
                    break;
                }
                cur->AddAttribute(lastAttriName, tmpStr);
            }
        }
    }

    return Result;
}

bool XMLDocument::to_string(std::string &str_)
{
    bool Result = false;
    return Result;
}

XMLNodePtr XMLDocument::fisrt_child()
{
    XMLNodePtr Result = _Impl->_root;
    return Result;
}

XMLNodePtr XMLDocument::child(const std::string &name_)
{
    XMLNodePtr Result = nullptr;
    return Result;
}

GZY_NAMESPACE_END
