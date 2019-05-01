//====================================================================
//  gCKK.h
//  created 6.13.18
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#ifndef GCKK_H_F30AA7D86CEC1B0E841433D26DE3F1F7
#define GCKK_H_F30AA7D86CEC1B0E841433D26DE3F1F7

#include "defines.h"

GZY_NAMESPACE_BEGIN

struct gCKK
{
public:
    gCKK();
    ~gCKK();

public:
    // ignore empty ckk
    bool append(const gString &classify_, const gString &kindFirst_, const gString &kindSecond_);

public:
    bool classifyList(gStringList &list);
    bool kindFirstList(gStringList &list, const gString &classify_ = "");
    bool kindSecondList(gStringList &list, const gString &classify_ = "", const gString &kindFirst_ = "");

public:
    void clear();

private:
    struct Impl;
    Impl *_Impl;
};
typedef gSharedPtr<gCKK> gCKKPtr;

GZY_NAMESPACE_END

#endif // GCKK_H_F30AA7D86CEC1B0E841433D26DE3F1F7
