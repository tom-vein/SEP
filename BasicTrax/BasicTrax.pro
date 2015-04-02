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
    AddTileCommand.cpp \
    StartGameCommand.cpp \
    GameBoard.cpp

HEADERS += \
    Color.h \
    Position.h \
    TileType.h \
    Shape.h \
    Tile.h \
    Command.h \
    Game.h \
    Player.h \
    AddTileCommand.h \
    StartGameCommand.h \
    GameBoard.h
