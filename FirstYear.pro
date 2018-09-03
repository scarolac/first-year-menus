QT += core
QT -= gui

CONFIG += c++11

TARGET = FirstYear
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    menus.cpp \
    cs_one.cpp \
    cs_two.cpp \
    principles.cpp \
    utilities.cpp \
    cs1/mod1/lesson1-104-2.cpp \
    cs1/mod1/lesson1-105-5.cpp \
    cs1/mod1/lesson1-106-4.cpp \
    cs1/mod1/lesson2-172-1.cpp \
    cs1/mod1/lesson2-173-5.cpp \
    cs1/mod1/lesson2-176-6.cpp \
    cs1/mod1/lesson3-245-3.cpp \
    cs1/mod1/lesson3-246-6.cpp \
    cs1/mod1/lesson3-300-5.cpp \
    cs1/mod1/lesson4-368-2.cpp \
    cs1/mod1/lesson4-369-5.cpp \
    cs1/mod1/lesson4-373-10.cpp \
    cs1/mod2/lesson5-611-1.cpp \
    cs1/mod2/lesson5-614-7.cpp \
    cs1/mod2/lesson5-617-11.cpp \
    cs1/mod2/lesson6-695-2.cpp \
    cs1/mod2/lesson7-737-5.cpp \
    cs1/mod2/password.cpp \
    cs1/mod2/user.cpp \
    cs1/mod2/lesson7-738-2.cpp \
    cs1/mod2/rational.cpp \
    cs1/mod2/Student.cpp \
    cs1/mod2/StudentException.cpp \
    cs1/mod2/StudentTest.cpp \
    cs1/mod3/lesson9-441-4.cpp \
    cs1/mod3/lesson9-441-5.cpp \
    cs1/mod3/lesson9-699-8.cpp \
    cs1/mod3/list.cpp \
    cs1/mod3/lesson10-498-7.cpp \
    cs1/mod3/lesson10-502-10.cpp \
    cs1/mod3/lesson11-694-1.cpp \
    cs1/mod3/lesson11-699-8.cpp \
    cs1/mod3/lesson12-887-8.cpp \
    cs1/mod3/ShoppingCart.cpp \
    cs1/mod3/pointer_practice.cpp \
    cs2/mod1/statistician_test.cxx \
    cs2/mod1/statistician.cxx \
    cs2/mod1/statexam.cxx \
    cs2/mod1/sequence_exam.cxx \
    cs2/mod1/sequence1.cxx \
    cs2/mod1/sequence_exam2.cxx \
    cs2/mod1/sequence_test.cxx \
    cs2/mod1/sequence2.cxx

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    menus.h \
    cs_one.h \
    cs_two.h \
    principles.h \
    utilities.h \
    cs1/mod1/cs1mod1.h \
    cs1/mod2/cs1mod2.h \
    cs1/mod2/Authenticate.h \
    cs1/mod2/password.h \
    cs1/mod2/user.h \
    cs1/mod2/rational.h \
    cs1/mod2/Student.h \
    cs1/mod2/StudentException.h \
    cs1/mod3/cs1mod3.h \
    cs1/mod3/list.h \
    cs1/mod3/ApplicationException.h \
    cs1/mod3/ShoppingCart.h \
    cs2/mod1/cs2mod1.h \
    cs2/mod1/statistician.h \
    cs2/mod1/sequence1.h \
    cs2/mod1/sequence2.h

DISTFILES +=
