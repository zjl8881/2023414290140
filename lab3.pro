QT += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    departmenteditview.cpp \
    departmentview.cpp \
    doctoreditview.cpp \
    doctorview.cpp \
    idatabase.cpp \
    loghelper.cpp \
    loginview.cpp \
    main.cpp \
    masterview.cpp \
    medicineseditview.cpp \
    medicinesview.cpp \
    patienteditview.cpp \
    patientview.cpp \
    reportworker.cpp \
    signup.cpp \
    statisticscontroller.cpp \
    statisticsview.cpp \
    welcomeview.cpp

HEADERS += \
    departmenteditview.h \
    departmentview.h \
    doctoreditview.h \
    doctorview.h \
    idatabase.h \
    loghelper.h \
    loginview.h \
    masterview.h \
    medicineseditview.h \
    medicinesview.h \
    patienteditview.h \
    patientview.h \
    reportworker.h \
    signup.h \
    statisticscontroller.h \
    statisticstypes.h \
    statisticsview.h \
    welcomeview.h

FORMS += \
    departmenteditview.ui \
    departmentview.ui \
    doctoreditview.ui \
    doctorview.ui \
    loginview.ui \
    masterview.ui \
    medicineseditview.ui \
    medicinesview.ui \
    patienteditview.ui \
    patientview.ui \
    signup.ui \
    statisticsview.ui \
    welcomeview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
