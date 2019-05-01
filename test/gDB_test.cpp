//====================================================================
//  gDB_test.cpp
//  created 6.3.18
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#include <gtest/gtest.h>

#include <gBase/gDB.h>

struct gMTest : public gzy::gMBase
{
public:
    gMTest(): gMBase("gMTest"){}
    gMTest(const gzy::gStringList &stringList_)
    : gMBase("gMTest")
    {
        if (stringList_.size() == 3)
        {
            _preId = std::stoi(stringList_[0]);
            _id = _preId;
            _name = stringList_[1];
            _score = std::stoi(stringList_[2]);
        }
        else
        {
            _name = "";
            _score = 0;
        }
    }
    
public:
    static void GetSqlCreateTable(std::string &sql_)
    {
        if (_init)
        {
            sql_ = "CREATE TABLE IF NOT EXISTS 'TestTable' ("
            "'Id' integer PRIMARY KEY NOT NULL,"
            "'Name' varchar(128),"
            "'Score' varchar(128));";
            _init = false;
        }
    }
    static void GetSqlSelect(std::string &sql_)
    {
        GetSqlCreateTable(sql_);
        sql_ += "select * from TestTable";
    }
    static void GetSqlDelete(std::string &sql_, const int &id_)
    {
        GetSqlCreateTable(sql_);
        sql_ += "delete from TestTable where Id='" + std::to_string(id_) + "';";
    }
    void GetSqlUpdate(std::string &sql_)
    {
        GetSqlCreateTable(sql_);
        sql_ += "update TestTable set "
        "Id='" + std::to_string(_id) +
        "',Name='" + _name +
        "',Score='" + std::to_string(_score) +
        "' where Id='" + std::to_string(_preId) + "';";
    }
    void GetSqlInsert(std::string &sql_)
    {
        GetSqlCreateTable(sql_);
        sql_ += "insert into TestTable values('" +
        std::to_string(_id) + "','" +
        _name + "','" +
        std::to_string(_score) + "');";
    }
    
public:
    std::string _name;
    int _score;
    
private:
    static bool _init;
};
typedef std::shared_ptr<gMTest> gMTestPtr;

bool gMTest::_init = true;
