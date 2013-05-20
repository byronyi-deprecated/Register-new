TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Menu.cpp \
    Database.cpp \
    Utils.cpp

HEADERS += \
    Menu.h \
    Database.h \
    Record.h \
    HashTable.h \
    DoublyLinkedList.h \
    Utils.h

