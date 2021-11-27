QT -= qt core gui

TARGET = KitsunemimiHanamiDatabase
TEMPLATE = lib
CONFIG += c++17
VERSION = 0.1.0

LIBS += -L../../libKitsunemimiArgs/src -lKitsunemimiArgs
LIBS += -L../../libKitsunemimiArgs/src/debug -lKitsunemimiArgs
LIBS += -L../../libKitsunemimiArgs/src/release -lKitsunemimiArgs
INCLUDEPATH += ../../libKitsunemimiArgs/include

LIBS += -L../../libKitsunemimiConfig/src -lKitsunemimiConfig
LIBS += -L../../libKitsunemimiConfig/src/debug -lKitsunemimiConfig
LIBS += -L../../libKitsunemimiConfig/src/release -lKitsunemimiConfig
INCLUDEPATH += ../../libKitsunemimiConfig/include

LIBS += -L../../libKitsunemimiIni/src -lKitsunemimiIni
LIBS += -L../../libKitsunemimiIni/src/debug -lKitsunemimiIni
LIBS += -L../../libKitsunemimiIni/src/release -lKitsunemimiIni
INCLUDEPATH += ../../libKitsunemimiIni/include

LIBS += -L../../libKitsunemimiCommon/src -lKitsunemimiCommon
LIBS += -L../../libKitsunemimiCommon/src/debug -lKitsunemimiCommon
LIBS += -L../../libKitsunemimiCommon/src/release -lKitsunemimiCommon
INCLUDEPATH += ../../libKitsunemimiCommon/include

LIBS += -luuid

INCLUDEPATH += $$PWD \
               $$PWD/../include

HEADERS += \
    ../include/libKitsunemimiHanamiDatabase/args.h \
    ../include/libKitsunemimiHanamiDatabase/defines.h \
    ../include/libKitsunemimiHanamiDatabase/config.h \
    ../include/libKitsunemimiHanamiDatabase/uuid.h \
    ../include/libKitsunemimiHanamiDatabase/structs.h \
    ../include/libKitsunemimiHanamiDatabase/enums.h \
    ../include/libKitsunemimiHanamiDatabase/generic_main.h \
    ../include/libKitsunemimiHanamiDatabase/component_support.h

SOURCES += \
    config.cpp

