#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QShowEvent>
#include <QKeyEvent>
#include <QIcon>
#include <QDir>
#include <QList>
#include <QTimer>
#include <gameboard.h>
#include <cell.h>
#include <piece.h>
#include <consts.h>
#include "answers.h"
#include "http.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void restartGame();
    void addPiece(int piece);
    void keyPressed(int key);

private slots:
    void win(QString answer);
    void timeout();
    void updateLines(int lines);
    void on_enterAnswerButton_clicked();
    void on_restartButton_clicked();
    void on_exitButton_clicked();
    void onSuccess(QJsonDocument doc);
public slots:
    void focusToEditText();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    GameBoard *board;
    QTimer *timer;
    Http *http;
    int tries;
    bool blocked;
    int linesToWin;
    void fitSceneToView();
};

#endif // MAINWINDOW_H
