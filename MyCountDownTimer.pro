#-------------------------------------------------
#
# Project created by QtCreator 2017-12-19T01:55:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyCountDownTimer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dialog.cpp \
    settingwindow.cpp \
    screenrect.cpp \

HEADERS += \
        mainwindow.h \
    dialog.h \
    settingwindow.h \
    screenrect.h \

FORMS += \
        mainwindow.ui \
    dialog.ui \
    settingwindow.ui

RESOURCES += \
    resource.qrc
TRANSLATIONS += ru.ts en.ts
#create translations files

#system(lrelease \"$$_PRO_FILE_\")
#tr.commands = lupdate \"$$_PRO_FILE_\" && lrelease \"$$_PRO_FILE_\"
#    PRE_TARGETDEPS += tr
#    QMAKE_EXTRA_TARGETS += tr

DISTFILES +=
