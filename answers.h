#ifndef ANSWERS_H
#define ANSWERS_H
#include <QString>
#include <QMap>
#include "piece.h"
class Answers {
public:
    Answers();
    ~Answers();
private:
    QMap<QString, PieceShape> *answers;
    QString calculateHash(QString data);
    QString salt();
public:
    bool isCorrect(QString answer);
    PieceShape getShape(QString answer);
};
#endif // ANSWERS_H
