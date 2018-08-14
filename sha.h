#ifndef SHA_H
#define SHA_H
#include <QByteArray>
class SHA
{
public:
    static QByteArray sha3(QByteArray data);
};
#endif // SHA_H
