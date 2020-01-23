#-------------------------------------------------
#
# Project created by QtCreator 2020-01-05T19:25:45
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sklep
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += /usr/include/postgresql

LIBS += -L/usr/lib -lpq
LIBS += -lssh

SOURCES += main.cpp\
        mainwindow.cpp \
    sklep.cpp \
    nowy_uzytkownik.cpp \
    moje_zamowienia.cpp \
    produkt.cpp \
    zamowienie.cpp \
    po_zamowieniu.cpp \
    sklep_pracownik.cpp \
    dodaj_produkt.cpp \
    edytuj_produkt.cpp \
    zamowienia_pracownik.cpp \
    produkt_pracownik.cpp \
    externs.cpp \
    ocena.cpp

HEADERS  += mainwindow.h \
    sklep.h \
    nowy_uzytkownik.h \
    moje_zamowienia.h \
    produkt.h \
    zamowienie.h \
    po_zamowieniu.h \
    sklep_pracownik.h \
    dodaj_produkt.h \
    edytuj_produkt.h \
    zamowienia_pracownik.h \
    produkt_pracownik.h \
    externs.h \
    ocena.h

FORMS    += mainwindow.ui \
    sklep.ui \
    nowy_uzytkownik.ui \
    moje_zamowienia.ui \
    produkt.ui \
    zamowienie.ui \
    po_zamowieniu.ui \
    sklep_pracownik.ui \
    dodaj_produkt.ui \
    edytuj_produkt.ui \
    zamowienia_pracownik.ui \
    produkt_pracownik.ui \
    ocena.ui
