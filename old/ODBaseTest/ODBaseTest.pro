QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gtest_main.cc \
    ODSqliteHandle_test.cpp \
    ODTimeUtilTest.cpp \
    ODVectorUtilTest.cpp \
    ODCKKTest.cpp

INCLUDEPATH += $$PWD/../3rd/gtest
DEPENDPATH += $$PWD/../3rd/gtest
INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

LIBS += -lsqlite3

macx: LIBS += -L$$PWD/../3rd/gtest/lib/ -lgtest
macx: PRE_TARGETDEPS += $$PWD/../3rd/gtest/lib/libgtest.a

macx: LIBS += -L$$PWD/../build-ODMBase-Desktop_Qt_5_11_0_clang_64bit-Debug/ -lODMBase
macx: PRE_TARGETDEPS += $$PWD/../build-ODMBase-Desktop_Qt_5_11_0_clang_64bit-Debug/libODMBase.a

macx: LIBS += -L$$PWD/../build-ODUtil-Desktop_Qt_5_11_0_clang_64bit-Debug/ -lODUtil
macx: PRE_TARGETDEPS += $$PWD/../build-ODUtil-Desktop_Qt_5_11_0_clang_64bit-Debug/libODUtil.a
