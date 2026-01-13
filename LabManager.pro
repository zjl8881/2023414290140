QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    dialog_reserve.cpp \
    dialogadddevice.cpp \
    main.cpp \
    mainwindow.cpp \
    stats_worker.cpp

HEADERS += \
    dbmanager.h \
    dialog_reserve.h \
    dialogadddevice.h \
    mainwindow.h \
    stats_worker.h

FORMS += \
    dialog_reserve.ui \
    dialogadddevice.ui \
    mainwindow.ui
