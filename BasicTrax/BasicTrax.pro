TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

SOURCES += ./main.cpp \
    Position.cpp \
    TileType.cpp \
    Tile.cpp \
    Command.cpp \
    Game.cpp \
    Player.cpp \
    GameBoard.cpp \
    Parser.cpp \
    FileManager.cpp

HEADERS += \
    Position.h \
    TileType.h \
    Tile.h \
    Command.h \
    Game.h \
    Player.h \
    GameBoard.h \
    Parser.h \
    FileManager.h \
    Exceptions.h \
    Exceptions.h \
    Color.h
