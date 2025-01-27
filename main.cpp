#include "morpion_games.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    TicTacToe game;
    game.show();
    return app.exec();
}