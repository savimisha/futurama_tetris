#-------------------------------------------------
#
# Project created by QtCreator 2017-04-23T13:18:28
#
#-------------------------------------------------

QT       += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += core gui widgets network

TARGET = futurama_tetris
TEMPLATE = app

RC_ICONS += nibbler.ico

SOURCES += main.cpp\
        mainwindow.cpp \
        gameboard.cpp \
    cell.cpp \
    piece.cpp \
    encryption.c \
    rijndael-alg-fst.c \
    aes.cpp \
    convert.cpp \
    sha.cpp \
    answers.cpp \
    sha3.cpp \
    keccak-tiny.c \
    http.cpp

HEADERS  += \
    mainwindow.h \
    gameboard.h \
    cell.h \
    piece.h \
    consts.h \
    encryption.h \
    rijndael-alg-fst.h \
    aes.h \
    convert.h \
    sha.h \
    answers.h \
    sha.h \
    sha3.h \
    keccak-tiny.h \
    http.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

VERSION = 1.0.0.0
QMAKE_TARGET_COMPANY = Encounter
QMAKE_TARGET_PRODUCT = Futurama Tetris
QMAKE_TARGET_DESCRIPTION = For game 11.08.2018
QMAKE_TARGET_COPYRIGHT = AllJuice
