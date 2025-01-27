#ifndef MORPION_GAMES_H
#define MORPION_GAMES_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

class TicTacToe : public QMainWindow {
    Q_OBJECT

public:
    TicTacToe(QWidget* parent = nullptr);

private slots:
    void handleButtonClick(int row, int col);
    void resetGame();

private:
    void checkGameStatus();
    bool checkWin(char player) const;
    bool checkDraw() const;

    QPushButton* buttons[3][3];
    QLabel* scoreLabel;
    char board[3][3];
    char currentPlayer;
    int playerXPoints;
    int playerOPoints;
    bool gameActive;
};

#endif // MORPION_GAMES_H