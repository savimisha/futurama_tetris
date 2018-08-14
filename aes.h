#ifndef AES_H
#define AES_H
#include <QByteArray>
class AES {
public:
    static QByteArray encrypt(QByteArray data);
    static QByteArray decrypt(QByteArray data);
};
#endif // AES_H
