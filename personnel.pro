QT += core gui serialport
QT +=sql
QT += printsupport
QT += core gui charts
QT += network
QT += core gui multimedia multimediawidgets
QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ardouino.cpp \
    connection.cpp \
    emission.cpp \
    historique.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    notepade.cpp \
    notifications.cpp \
    personnel.cpp \
    qcustomplot.cpp \
    rana.cpp \
    statistic.cpp


HEADERS += \
    ardouino.h \
    connection.h \
    emission.h \
    historique.h \
    mainwindow.h \
    menu.h \
    notepade.h \
    notifications.h \
    personnel.h \
    qcustomplot.h \
    rana.h \
    statistic.h

FORMS += \
    mainwindow.ui \
    menu.ui \
    notepade.ui \
    rana.ui \
    statistic.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
RESOURCES += \
    pic.qrc \
    resource.qrc


DISTFILES += \
    ../download.png \
    ../qt/pdf.png \
    ../qt/rech.png \
    ../qt/tri.jfif