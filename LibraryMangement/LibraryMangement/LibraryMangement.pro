QT       += core gui widgets sql printsupport
TARGET = LibraryManagement
TEMPLATE = app
CONFIG += c++17

# 文件夹路径（你的项目无单独include/src/ui，直接用当前结构）
SOURCES += main.cpp \
           idatabase.cpp \
           loginview.cpp \
           mainwindow.cpp \
           masterview.cpp \
           patientediview.cpp \
           patientview.cpp \
           welcomeview.cpp

HEADERS  += idatabase.h \
            loginview.h \
            mainwindow.h \
            masterview.h \
            patientediview.h \
            patientview.h \
            welcomeview.h

# 仅保留你的mainwindow.ui
FORMS    += mainwindow.ui

# SQLite数据库配置
QT += sql
CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/bin/Debug
} else {
    DESTDIR = $$PWD/bin/Release
}

# 忽略编译警告（可选）
QMAKE_CXXFLAGS += -Wno-deprecated-declarations
