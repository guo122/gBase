//====================================================================
//  ODMTest.cpp
//  created 6.3.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include "ODMTest.h"

bool ODMTest::_init = true;

ODMTest::ODMTest()
    : ODMBase("ODMTest")
{

}

ODMTest::ODMTest(const StringList &stringList)
    : ODMBase("ODMTest")
{
    if (stringList.size() == 3)
    {
        _preId = std::stoi(stringList[0]);
        _id = _preId;
        _name = stringList[1];
        _score = std::stoi(stringList[2]);
    }
    else
    {
        _name = "";
        _score = 0;
    }
}

void ODMTest::GetSqlCreateTable(std::string &sql_)
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

void ODMTest::GetSqlSelect(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "select * from TestTable";
}

void ODMTest::GetSqlDelete(std::string &sql_, const int &id_)
{
    GetSqlCreateTable(sql_);
    sql_ += "delete from TestTable where Id='" + std::to_string(id_) + "';";
}

void ODMTest::GetSqlUpdate(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "update TestTable set "
            "Id='" + std::to_string(_id) +
            "',Name='" + _name +
            "',Score='" + std::to_string(_score) +
            "' where Id='" + std::to_string(_preId) + "';";
}

void ODMTest::GetSqlInsert(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "insert into TestTable values('" +
            std::to_string(_id) + "','" +
            _name + "','" +
            std::to_string(_score) + "');";
}
