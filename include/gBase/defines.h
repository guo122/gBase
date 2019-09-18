//====================================================================
//  Defines.h
//  created 5.1.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#ifndef GDEFINES_H_7DE60B12A59FA436C5808FA0B552F981
#define GDEFINES_H_7DE60B12A59FA436C5808FA0B552F981

#include <map>
#include <string>
#include <vector>
#include <algorithm>

#include "config.h"
#include "platform.h"

#define     GZY_NAMESPACE_BEGIN                 namespace gzy {
#define     GZY_NAMESPACE_END                   }

GZY_NAMESPACE_BEGIN

#define     gVector                             std::vector
#define     gString                             std::string
#define     gString_sizetype                    gString::size_type
#define     gString_npos						gString::npos
#define     gMap                                std::map

#define     gToString                           std::to_string
#define     gStoI                               std::stoi
#define     gAtoI                               std::atoi

#define     gMakeShared                         std::make_shared
#define     gSharedPtr                          std::shared_ptr

#define     gForeach                            std::for_each
#define     gFind                               std::find
#define     gSort                               std::sort
#define     gFindIf                             std::find_if
#define     gPair                               std::pair

#define     gStaticPointerCast                  std::static_pointer_cast

typedef     gVector<gString>                    gStringList;
typedef     gVector<gStringList>                gStringTable;

typedef     gSharedPtr<gStringList>             gStringListPtr;

typedef     gMap<gString, gStringList>          gStringListMap;
typedef     gMap<gString, gStringListPtr>       gStringListPtrMap;

typedef     gVector<int>                        gIntList;

GZY_NAMESPACE_END

#endif // GDEFINES_H_7DE60B12A59FA436C5808FA0B552F981
