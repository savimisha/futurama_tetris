#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->centralWidget->setFocusPolicy(Qt::StrongFocus);

    board = new GameBoard();
    blocked = false;
    tries = 0;
    linesToWin = -1;
    timer = new QTimer();
    timer->setSingleShot(true);

    ui->gvBoard->setRenderHint(QPainter::Antialiasing, true);
    ui->gvBoard->setScene(board);

    http = new Http(API_HOST);

    connect(this, SIGNAL(restartGame()), board, SLOT(restartGame()));
    connect(this, SIGNAL(keyPressed(int)), board, SLOT(keyPressed(int)));
    connect(this, SIGNAL(addPiece(int)), board, SLOT(addPiece(int)));
    connect(board, SIGNAL(win(QString)), this, SLOT(win(QString)));
    connect(board, SIGNAL(figureBelow()), this, SLOT(focusToEditText()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    connect(board, SIGNAL(updateLines(int)), this, SLOT(updateLines(int)));

    connect(http, SIGNAL(onSuccess(QJsonDocument)), this, SLOT(onSuccess(QJsonDocument)));
    http->GET("lines");

}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete http;
}



void MainWindow::fitSceneToView()
{
   ui->gvBoard->fitInView(board->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    fitSceneToView();
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);

    fitSceneToView();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
        case Qt::Key_Down:
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_Up:
            emit keyPressed(event->key());
            break;
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            on_enterAnswerButton_clicked();
            break;
    }
}


void MainWindow::win(QString answer) {
    QMessageBox box;
    box.setStyleSheet("QLabel{min-width: 300px; min-height:50px; font-size:14px;}");
    box.setText("Бей в движок: " + answer);
    box.exec();
}

void MainWindow::timeout() {
    blocked = false;
    tries = 0;
    ui->statusLabel->setText("");
}


void MainWindow::focusToEditText() {
    ui->answerLineEdit->setFocus();
}

void MainWindow::updateLines(int lines){
    if (linesToWin != -1) {
        ui->linesLabel->setText(QString::number(lines) + "/" + QString::number(linesToWin));
    } else  {
        ui->linesLabel->setText(QString::number(lines));
    }
}

void MainWindow::onSuccess(QJsonDocument doc){
    auto obj = doc.object();
    auto linesToWin = obj["lines"].toInt();
    this->linesToWin = linesToWin;
    updateLines(board->getRemovedLines());
}


void MainWindow::on_enterAnswerButton_clicked()
{
    QPalette palette;
    auto text = ui->answerLineEdit->text();
    if (text.isEmpty()) {
        ui->statusLabel->setText("");
        return;
    }
    if (blocked) {
        palette.setColor(QPalette::WindowText, Qt::white);
        ui->statusLabel->setText("Слишком часто!");
        ui->statusLabel->setPalette(palette);
        ui->answerLineEdit->setText("");
        return;
    }
    if (!blocked && tries >= MAX_TRIES) {
        blocked = true;
        timer->start(BLOCKED_TIME);
        palette.setColor(QPalette::WindowText, Qt::white);
        ui->statusLabel->setText("Слишком часто!");
        ui->statusLabel->setPalette(palette);
        ui->answerLineEdit->setText("");
        return;
    }
    if (board->hasActiveTetramino()) {
        palette.setColor(QPalette::WindowText, Qt::white);
        ui->statusLabel->setText("Опусти вниз!");
        ui->statusLabel->setPalette(palette);
        return;
    }
    switch(board->onAnswerEntered(text)) {
    case CORRECT_ANSWER: {
        ui->answerLineEdit->setText("");
        palette.setColor(QPalette::WindowText, QColor(135,253,5));
        ui->statusLabel->setText("Код верный!");
        ui->statusLabel->setPalette(palette);
        ui->correctAnswersListWidget->addItem(text);
        ui->answerLineEdit->clearFocus();
        ui->enterAnswerButton->clearFocus();
        break;
    }
    case INCORRECT_ANSWER: {
        tries++;
        palette.setColor(QPalette::WindowText, Qt::red);
        ui->statusLabel->setText("Код неверный!");
        ui->statusLabel->setPalette(palette);
        break;
    }
    case ALREADY_ENTERED_ANSWER: {
        palette.setColor(QPalette::WindowText, QColor(173,216,230));
        ui->statusLabel->setText("Код уже был!");
        ui->statusLabel->setPalette(palette);
        ui->answerLineEdit->setText("");
        break;
    }
    }
}

void MainWindow::on_restartButton_clicked()
{
    ui->answerLineEdit->setText("");
    ui->statusLabel->setText("");
    ui->linesLabel->setText("0");
    ui->correctAnswersListWidget->clear();
    emit restartGame();
    http->GET("lines");
}

void MainWindow::on_exitButton_clicked()
{
     exit(0);
}
