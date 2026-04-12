SOURCES += \
    main.cpp \
    mainwidget.cpp

HEADERS += \
    mainwidget.h

QT += widgets

LIBS += -L$$PWD/libs -lmsdscript
INCLUDEPATH += $$PWD/libs/msdscript