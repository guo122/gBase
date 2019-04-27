//====================================================================
//  ODTimeUtil.cpp
//  created 6.5.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include "ODTimeUtil.h"

ODTimeUtil::ODTimeUtil()
{

}

std::string ODTimeUtil::Timestamp2String(const int &timestamp_, const std::string &format_)
{
    std::string Result = "";
    struct tm *tmpTm;
    time_t lt;
    char str[80];
    lt = timestamp_;
    tmpTm=localtime(&lt);
    strftime(str, 100, format_.c_str(), tmpTm);
    Result = str;
    return Result;
}

std::string ODTimeUtil::Duration2String(const int &timestamp_, const std::string &format_)
{
    std::string Result = "";

    int tmpDay = timestamp_ / 86400;
    int tmpInt = timestamp_ % 86400;

    int tmpHour = tmpInt / 3600;
    tmpInt = tmpInt % 3600;

    int tmpMinute = tmpInt / 60;
    int tmpSecond = tmpInt % 60;

    bool nextTrans = false;
    int numLength = 0;
    std::string tmpStr;
    if (format_.empty())
    {
        // default format
        if (tmpDay)
        {
            Result += std::to_string(tmpDay) + "d ";
        }
        if (tmpHour)
        {
            Result += std::to_string(tmpHour) + "h";
        }
        if (tmpMinute)
        {
            tmpStr = std::to_string(tmpMinute);
            while (tmpStr.length() < 2)
            {
                tmpStr = "0" + tmpStr;
            }
            Result += tmpStr + "m";
        }
        if (Result.empty())
        {
            tmpStr = std::to_string(tmpSecond);
            while (tmpStr.length() < 2)
            {
                tmpStr = "0" + tmpStr;
            }
            Result += tmpStr + "s";
        }
    }
    else if (format_ == "__DIGITAL__")
    {
        // digital format like 00:01:22
        if (tmpDay)
        {
            Result += std::to_string(tmpDay) + "-";
        }
        tmpStr = std::to_string(tmpHour);
        while (tmpStr.length() < 2)
        {
            tmpStr = "0" + tmpStr;
        }
        Result += tmpStr + ":";

        tmpStr = std::to_string(tmpMinute);
        while (tmpStr.length() < 2)
        {
            tmpStr = "0" + tmpStr;
        }
        Result += tmpStr + ":";

        tmpStr = std::to_string(tmpSecond);
        while (tmpStr.length() < 2)
        {
            tmpStr = "0" + tmpStr;
        }
        Result += tmpStr;
    }
    else
    {
        // custom format
        std::for_each(format_.begin(), format_.end(), [&](const char &x){
            if (nextTrans)
            {
                if (x >= 0x30 && x <= 0x39)
                {
                    numLength = x - 0x30;
                }
                else
                {
                    switch (x)
                    {
                    case 'd':tmpStr = std::to_string(tmpDay);break;
                    case 'H':tmpStr = std::to_string(tmpHour);break;
                    case 'M':tmpStr = std::to_string(tmpMinute);break;
                    case 'S':tmpStr = std::to_string(tmpSecond);break;
                    default:tmpStr.clear();break;
                    }
                    while (tmpStr.length() < numLength && !tmpStr.empty())
                    {
                        tmpStr = "0" + tmpStr;
                    }
                    Result += tmpStr;
                    numLength = 0;
                    nextTrans = false;
                }
            }
            else
            {
                if (x == '%')
                {
                    nextTrans = true;
                }
                else
                {
                    Result.push_back(x);
                }
            }
        });
    }
    return Result;
}

bool ODTimeUtil::IsSameDay(const int &timstamp1_, const int &timstamp2_)
{
    struct tm tmpTm1, tmpTm2;
    time_t lt;
    lt = timstamp1_;
    tmpTm1=*localtime(&lt);
    lt = timstamp2_;
    tmpTm2=*localtime(&lt);

    if (tmpTm1.tm_year != tmpTm2.tm_year)
    {
        return false;
    }
    else if (tmpTm1.tm_yday != tmpTm2.tm_yday)
    {
        return false;
    }
    else
    {
        return true;
    }

}

void ODTimeUtil::DateJump(std::string &date_, const int &count_)
{
    struct tm tmpTm;
    tmpTm.tm_year = std::stoi("20" + date_.substr(0, 2)) - 1900;
    tmpTm.tm_mon = std::stoi(date_.substr(3, 2)) - 1;
    tmpTm.tm_mday = std::stoi(date_.substr(6, 2)) + count_;
    tmpTm.tm_hour = 0;
    tmpTm.tm_min = 0;
    tmpTm.tm_sec = 0;
    tmpTm.tm_isdst = 0;
    time_t lt = mktime(&tmpTm);

    char str[80];
    strftime(str, 100, "%y-%m-%d", &tmpTm);
    date_ = str;
}

bool ODTimeUtil::CalcuteBillList(const int &timestamp_, const int &billDates_, int &index_)
{
    index_ = 0;

    struct tm curTm, inTm;
    time_t curTime, lt;

    // current time
    time(&curTime);
    curTm = *localtime(&curTime);
    // in time
    lt = timestamp_;
    inTm = *localtime(&lt);

    if (curTime > lt)
    {
        curTm.tm_mday -= billDates_ - 1;
        inTm.tm_mday -= billDates_ - 1;
        mktime(&curTm);
        mktime(&inTm);
        index_ = ((curTm.tm_year - inTm.tm_year) * 12) + (curTm.tm_mon - inTm.tm_mon);
    }

    return index_ >= 0;
}
