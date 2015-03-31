TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

SOURCES += ./main.cpp \
    Position.cpp \
    TileType.cpp \
    Tile.cpp

HEADERS += \
    Color.h \
    Position.h \
    TileType.h \
    Shape.h \
    Tile.h
