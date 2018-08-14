#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QGraphicsScene>
#include <QTimeLine>
#include <QTimer>
#include <QGraphicsItemAnimation>
#include "cell.h"
#include "piece.h"
#include "consts.h"
#include "http.h"
#include "answers.h"

#define CORRECT_ANSWER 0
#define INCORRECT_ANSWER 1
#define ALREADY_ENTERED_ANSWER 2


class GameBoard : public QGraphicsScene
{
    Q_OBJECT
public:
    GameBoard(QObject *parent = 0);
    ~GameBoard();
    bool hasActiveTetramino();
    int onAnswerEntered(QString answer);
    int getRemovedLines();
signals:
    void win(QString answer);
    void figureBelow();
    void updateLines(int lines);
    void updateLevel(int level);
public slots:
    void restartGame();
    void keyPressed(int key);
    void addPiece(int piece);
private slots:
    void updateAnimation();
    void fixCurrentPiece();
    void onSuccess(QJsonDocument doc);
    void onSuccess();
    void onFailure(int);
private:
    Cell board_cells[BOARD_WIDTH][BOARD_HEIGHT];
    Piece *currentPiece;
    QTimeLine *timeLine;
    QTimer *timer;
    Http *http;
    Answers *answers;
    QList<QString> *enteredAnswers;
    int removedLines;
    int level;
    bool gameOver;
    bool isOnBorder;
    int gameId;

    void moveLeft();
    void moveRight();
    bool moveDown();
    void fallDown();

    void rotateLeft();
    void rotateRight();
    bool canMovePiece(Piece *piece);
    bool canMoveCell(int x, int y);
    void clearBoard();
    void removeLine(int line);
    void checkLines();
    void checkLevel();
    void checkGameOver();
    void checkWin();
};

#endif // GAMEBOARD_H
