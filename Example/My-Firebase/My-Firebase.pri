
SOURCES += \
        $$PWD/firebase.cpp \
        $$PWD/datasnapshot.cpp \
        $$PWD/json.cpp \
        $$PWD/myorm.cpp

HEADERS += \
        $$PWD/firebase.h \
        $$PWD/datasnapshot.h \
        $$PWD/json.h \
        $$PWD/myorm.h \
        $$PWD/mypropertyhelper.h

INCLUDEPATH += $$PWD/Tables
include(Tables/Tables.pri)
