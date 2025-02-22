QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17 c11 debug

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    credit.cpp \
    depocit.cpp \
    main.cpp \
    mainwindow.cpp \
    plot.cpp \
    qcustomplot.cpp \
    s21_calc.c \
    s21_steck.c \
    s21_valid.c

HEADERS += \
    credit.h \
    depocit.h \
    mainwindow.h \
    plot.h \
    qcustomplot.h \
    s21_calc.h

FORMS += \
    credit.ui \
    depocit.ui \
    mainwindow.ui \
    plot.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
