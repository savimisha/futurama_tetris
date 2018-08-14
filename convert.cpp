#include <QString>
#include "convert.h"

QString Convert::bytes2Base64UrlSafe(QByteArray bytes)
{
    QString base64(bytes.toBase64());
    base64 = base64.replace(QString("+"), QString("-"));
    base64 = base64.replace(QString("/"), QString("_"));
    base64 = base64.replace(QString("="), QString(""));
    return base64;
}

QByteArray Convert::base64UrlSafe2Bytes(QString string)
{
    auto base64 = string.replace(QString("-"), QString("+"));
    base64 = base64.replace(QString("_"), QString("/"));
    base64.append(QString("=="));
    return QByteArray::fromBase64(base64.toUtf8());
}

QString Convert::bytes2hex(QByteArray bytes)
{
    return QString(bytes.toHex());
}

QByteArray Convert::hex2bytes(QString hex)
{
    return QByteArray::fromHex(hex.toUtf8());
}


