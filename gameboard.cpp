#include <qmath.h>
#include "gameboard.h"
#include "convert.h"
#include "aes.h"
#include "sha.h"
#include "piece.h"

GameBoard::GameBoard(QObject * parent) : QGraphicsScene(parent)
{
    level = 1;
    currentPiece = nullptr;
    gameOver = false;
    isOnBorder = false;
    removedLines = 0;
    QDateTime cd = QDateTime::currentDateTime();
    qsrand(cd.toTime_t());
    gameId = qrand();
    timeLine = new QTimeLine();
    timeLine->setLoopCount(0);
    timer = new QTimer();
    timer->setSingleShot(true);
    http = new Http(API_HOST);
    answers = new Answers();
    enteredAnswers = new QList<QString>();

    connect(timeLine, SIGNAL(valueChanged(qreal)), this, SLOT(updateAnimation()));
    connect(timer, SIGNAL(timeout()), this, SLOT(fixCurrentPiece()));
    connect(http, SIGNAL(onSuccess(QJsonDocument)), this, SLOT(onSuccess(QJsonDocument)));
    connect(http, SIGNAL(onSuccess()), this, SLOT(onSuccess()));
    connect(http, SIGNAL(onFailure(int)), this, SLOT(onFailure(int)));

    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            board_cells[i][j].setPosition(i, j);
            board_cells[i][j].setVisible(false);
            this->addItem(&board_cells[i][j]);
        }
    }
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        auto *cell = new Cell(i, -1);
        this->addItem(cell);
        cell->setVisible(false);
    }

    QPen pen(QColor(71, 71, 71), 1);
    (this->addLine(-1, -BLOCK_SIZE,
                   -1, BOARD_HEIGHT * BLOCK_SIZE + 1, pen))->setVisible(true);
    (this->addLine(BOARD_WIDTH * BLOCK_SIZE + 1, -BLOCK_SIZE,
                   BOARD_WIDTH * BLOCK_SIZE + 1, BOARD_HEIGHT * BLOCK_SIZE + 1, pen))->setVisible(true);
    (this->addLine(-1, BOARD_HEIGHT * BLOCK_SIZE + 1,
                   BOARD_WIDTH * BLOCK_SIZE + 1, BOARD_HEIGHT * BLOCK_SIZE + 1, pen))->setVisible(true);
}

GameBoard::~GameBoard()
{
    this->clear();
    delete timeLine;
    delete timer;
    if (currentPiece != nullptr) {
        delete currentPiece;
    }
    delete http;
    delete answers;
    delete enteredAnswers;
}

int GameBoard::getRemovedLines() {
    return removedLines;
}

int GameBoard::onAnswerEntered(QString answer){
    if (enteredAnswers->contains(answer)){
        return ALREADY_ENTERED_ANSWER;
    }
    auto obj = QJsonObject();
    obj["answer"] = answer;
    auto doc = QJsonDocument(obj);
    http->POST(QString(TEAM) + "/answer", doc);
    if (answers->isCorrect(answer)) {
        enteredAnswers->append(answer);
        emit addPiece(answers->getShape(answer));
        return CORRECT_ANSWER;
    } else  {
        return INCORRECT_ANSWER;
    }
}

void GameBoard::onSuccess() { 
}


void GameBoard::clearBoard()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_HEIGHT; j++)
            board_cells[i][j].setVisible(false);

    if (currentPiece)
    {
        for (int i = 0; i < 4; ++i)
                this->removeItem(&(currentPiece->cells[i]));

        delete(currentPiece);
        currentPiece = nullptr;
    }
    timeLine->stop();
}

void GameBoard::restartGame()
{
    clearBoard();
    gameOver = false;
    removedLines = 0;
    level = 1;
    isOnBorder = false;
    QDateTime cd = QDateTime::currentDateTime();
    qsrand(cd.toTime_t());
    gameId = qrand();
    enteredAnswers->clear();
}


void GameBoard::addPiece(int piece)
{
    if (currentPiece != nullptr) {
        return;
    }
    currentPiece = new Piece((PieceShape)piece);

    for (int i = 0; i < 4; i++)
    {
        this->addItem(&(currentPiece->cells[i]));
    }

    timeLine->stop();
    timeLine->setUpdateInterval(300 / (level + 10) + 1);
    timeLine->start();
}


void GameBoard::keyPressed(int key) {
    if (gameOver)
        return;

    switch (key) {
        case Qt::Key_Down:
            fallDown();
            break;
        case Qt::Key_Left:
            moveLeft();
            break;
        case Qt::Key_Right:
            moveRight();
            break;
        case Qt::Key_Up:
            rotateRight();
            break;
    }
}


bool GameBoard::canMoveCell(int x, int y)
{
    if (x < 0 || x > (BOARD_WIDTH - 1) * BLOCK_SIZE)
        return false;

    if (y > (BOARD_HEIGHT - 1) * BLOCK_SIZE)
        return false;

    int lx = x / BLOCK_SIZE;
    int ly = y / BLOCK_SIZE;

    if (board_cells[lx][ly].isVisible())
        return false;

    if (y % BLOCK_SIZE > 0 && board_cells[lx][ly + 1].isVisible())
        return false;

    return true;
}

void GameBoard::moveLeft() {
    if (currentPiece == nullptr) {
        return;
    }
    for (int i = 0; i < 4; ++i)
    {
        int xx = currentPiece->cells[i].x();
        int yy = currentPiece->cells[i].y();

        if (!canMoveCell(xx - BLOCK_SIZE, yy))
            return;
    }

    currentPiece->addX(-BLOCK_SIZE);
}


bool GameBoard::canMovePiece(Piece *piece){
    auto canMove = true;

    for (int i = 0; i < 4; ++i)
    {
        int xx = piece->cells[i].x();
        int yy = piece->cells[i].y();

        if (!canMoveCell(xx, yy + MOVE_DOWN_STEP))
        {
            canMove = false;
            break;
        }
    }
    return canMove;
}

bool GameBoard::moveDown()
{
    if (currentPiece == nullptr) {
        return false;
    }

    if (canMovePiece(currentPiece)) {
        currentPiece->addY(MOVE_DOWN_STEP);
        return true;
    }

    if (!canMovePiece(currentPiece))
    {
        timeLine->stop();
        timer->start(TIME_FOR_CHANGE_ON_BORDER);
        isOnBorder = true;
        return false;
    }
    return true;

}

void GameBoard::fixCurrentPiece(){
    isOnBorder = false;
    if (currentPiece == nullptr) {
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        int lx = currentPiece->cells[i].x() / BLOCK_SIZE;
        int ly = currentPiece->cells[i].y() / BLOCK_SIZE;
        if (ly >= 0 && !board_cells[lx][ly].isVisible())
        {
            board_cells[lx][ly].setColor(currentPiece->cells[i].getColor());
            board_cells[lx][ly].setVisible(true);
        }
        this->removeItem(&(currentPiece->cells[i]));
    }

    emit figureBelow();
    delete(currentPiece);
    currentPiece = nullptr;

    checkGameOver();
    checkLines();
    timeLine->stop();
    checkWin();
}

void GameBoard::fallDown()
{
    if (isOnBorder) {
        return;
    }
    if(!gameOver) {
        timeLine->stop();
        timeLine->setUpdateInterval(1);
        timeLine->resume();
    }
}

void GameBoard::checkLines()
{
    bool filledLine;
    for (int i = BOARD_HEIGHT - 1; i > 0; --i)
    {
        filledLine = true;
        for (int j = 0; j < BOARD_WIDTH; ++j)
        {
            if (!board_cells[j][i].isVisible())
                filledLine = false;
        }
        if (filledLine)
        {
            removeLine(i++);
            checkLevel();
            removedLines++;
            emit updateLines(removedLines);
        }
    }
}

void GameBoard::removeLine(int line)
{
    for (int i = 0; i < BOARD_WIDTH; ++i)
        board_cells[i][line].setVisible(false);

    for (int i = line; i > 0; --i)
    {
        for (int j = 0; j < BOARD_WIDTH; ++j)
        {
            board_cells[j][i].setVisible(board_cells[j][i - 1].isVisible());
        }
    }
}

void GameBoard::checkLevel()
{
    if (removedLines % LEVEL_LINES == 0)
    {
        level++;
        emit updateLevel(level);
    }
}

void GameBoard::checkGameOver()
{
    for (int i = 0; i < BOARD_WIDTH; ++i)
        if (board_cells[i][0].isVisible())
        {
            gameOver = true;
        }
}

void GameBoard::checkWin() {
    QJsonArray boardArray = QJsonArray();
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        QJsonArray a = QJsonArray();
        for (int j = 0; j < BOARD_WIDTH; j++) {
            a.append(board_cells[j][i].isVisible());
        }
        boardArray.append(a);
    }
    auto answersArray = QJsonArray();
    for (QString a: *enteredAnswers) {
        answersArray.append(a);
    }
    auto doc = QJsonDocument(boardArray);
    auto shaBoard = SHA::sha3(doc.toJson());
    auto encBoard = Convert::bytes2Base64UrlSafe(AES::encrypt(doc.toJson()));
    doc = QJsonDocument(answersArray);
    auto shaAnswers = SHA::sha3(doc.toJson());
    auto encAnswers = Convert::bytes2Base64UrlSafe(AES::encrypt(doc.toJson()));
    auto removedLinesBytes = QString::number(removedLines).toUtf8();
    auto encRemovedLines = Convert::bytes2Base64UrlSafe(AES::encrypt(removedLinesBytes));
    auto shaRemovedLines = SHA::sha3(removedLinesBytes);
    auto encSalt = QString(ENC_SALT);
    auto dec = AES::decrypt(Convert::base64UrlSafe2Bytes(encSalt));
    auto salt = SHA::sha3(SHA::sha3(dec) + QByteArray::fromHex(QString("c6bb8bac3d74dfc7f20efd477352c1ca").toUtf8()));
    auto signature = Convert::bytes2Base64UrlSafe(SHA::sha3(shaBoard
                                                            + QByteArray::fromHex(QString("b9e714343567c0a497e54257835516afc3f81a7e1d55498b71fc605cadca275e").toUtf8())
                                                            + shaAnswers
                                                            + salt
                                                            + shaRemovedLines));
    auto obj = QJsonObject();
    obj["board"] = encBoard;
    obj["answers"] = encAnswers;
    obj["removed_lines"] = encRemovedLines;
    obj["game_id"] = gameId;
    doc = QJsonDocument(obj);
    http->POST(QString(TEAM) + "/check/" + signature, doc);
}

void GameBoard::onSuccess(QJsonDocument doc){
    auto obj = doc.object();
    auto status = obj["status"].toInt();
    if (status == 0) {
        QString answer = obj["answer"].toString();
        if (!answer.isEmpty()) {
            emit win(answer);
        }
    }
}

void GameBoard::onFailure(int status) {
}

void GameBoard::moveRight() {
    if (currentPiece == nullptr) {
        return;
    }
    for (int i = 0; i < 4; ++i)
    {
        int xx = currentPiece->cells[i].x();
        int yy = currentPiece->cells[i].y();

        if (!canMoveCell(xx + BLOCK_SIZE, yy))
            return;
    }
    currentPiece->addX(BLOCK_SIZE);
}

void GameBoard::rotateLeft() {
    if (currentPiece == nullptr) {
        return;
    }
    if (isOnBorder) {
        return;
    }
    if (currentPiece->getShape() == PieceShape::SquareShape) {
        return;
    }
    for (int i = 0; i < 4; ++i)
    {
        int xx = currentPiece->cells[i].x() - currentPiece->getX();
        int yy = currentPiece->cells[i].y() - currentPiece->getY();


        if (!canMoveCell(currentPiece->getX() + yy,currentPiece->getY() - xx))
            return;
    }

    currentPiece->rotateLeft();
}

void GameBoard::rotateRight() {
    if (currentPiece == nullptr) {
        return;
    }
    if (isOnBorder) {
        return;
    }
    if (currentPiece->getShape() == PieceShape::SquareShape) {
        return;
    }
    for (int i = 0; i < 4; ++i)
    {
        int xx = currentPiece->cells[i].x() - currentPiece->getX();
        int yy = currentPiece->cells[i].y() - currentPiece->getY();

        if (!canMoveCell(currentPiece->getX() - yy,currentPiece->getY() + xx)) {
            return;
        }
    }

    currentPiece->rotateRight();
}

bool GameBoard::hasActiveTetramino() {
    return currentPiece != nullptr;
}

void GameBoard::updateAnimation() {

    if (!gameOver) {
        moveDown();
    }
}


