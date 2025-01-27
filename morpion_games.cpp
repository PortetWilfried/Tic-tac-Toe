#include "morpion_games.h"
#include <QMessageBox>

TicTacToe::TicTacToe(QWidget* parent)
    : QMainWindow(parent),
    currentPlayer('X'),
    playerXPoints(0),
    playerOPoints(0),
    gameActive(true)
{
    QWidget* centralWidget = new QWidget(this);
    QGridLayout* mainLayout = new QGridLayout(centralWidget);

    // Initialisation du tableau
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }

    // Création de la grille
    QGridLayout* gridLayout = new QGridLayout();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            buttons[i][j] = new QPushButton();
            buttons[i][j]->setFixedSize(80, 80);
            buttons[i][j]->setFont(QFont("Arial", 24));
            connect(buttons[i][j], &QPushButton::clicked, [=]() { handleButtonClick(i, j); });
            gridLayout->addWidget(buttons[i][j], i, j);
        }
    }

    // mini menu
    scoreLabel = new QLabel("Score: X - 0 | O - 0");
    QPushButton* resetButton = new QPushButton("Nouvelle partie");
    connect(resetButton, &QPushButton::clicked, this, &TicTacToe::resetGame);

    mainLayout->addLayout(gridLayout, 0, 0, 1, 2);
    mainLayout->addWidget(scoreLabel, 1, 0);
    mainLayout->addWidget(resetButton, 1, 1);

    setCentralWidget(centralWidget);
    setWindowTitle("Tic-Tac-Toe");
    setFixedSize(300, 400);
}

/*Vérifie si une case est vide avant de permettre un clic.
Met à jour l’état de la case, désactive le bouton, et passe au joueur suivant.*/

void TicTacToe::handleButtonClick(int row, int col) {
    if (!gameActive || board[row][col] != ' ') return;

    board[row][col] = currentPlayer;
    buttons[row][col]->setText(QString(currentPlayer));
    buttons[row][col]->setEnabled(false);

    checkGameStatus();
}

/*Appelle checkWin pour vérifier les lignes, colonnes et diagonales.
Appelle checkDraw pour vérifier si la grille est pleine sans vainqueur.*/

void TicTacToe::checkGameStatus() {
    if (checkWin(currentPlayer)) {
        QMessageBox::information(this, "Victoire", QString("Joueur %1 gagne!").arg(currentPlayer));
        (currentPlayer == 'X') ? playerXPoints++ : playerOPoints++;
        scoreLabel->setText(QString("Score: X - %1 | O - %2").arg(playerXPoints).arg(playerOPoints));
        gameActive = false;
    }
    else if (checkDraw()) {
        QMessageBox::information(this, "Match nul", "Aucun gagnant!");
        gameActive = false;
    }
    else {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

bool TicTacToe::checkWin(char player) const {
    // Vérification des lignes/colonnes
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return true;
    }
    // Diagonales
    return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player);
}

bool TicTacToe::checkDraw() const {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == ' ') return false;
    return true;
}

void TicTacToe::resetGame() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
            buttons[i][j]->setText("");
            buttons[i][j]->setEnabled(true);
        }
    }
    currentPlayer = 'X';
    gameActive = true;
}