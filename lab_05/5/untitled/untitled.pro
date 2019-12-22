TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        executer.cpp \
        generator.cpp \
        log_generator.cpp \
        main.cpp \
        myqueue.cpp \
        mytime.cpp

HEADERS += \
    executer.h \
    generator.h \
    log_generator.h \
    myqueue.h \
    mytime.h \
    struct.h
