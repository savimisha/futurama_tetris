#ifndef CONVERT_H
#define CONVERT_H
class Convert{
public:
    static QString bytes2Base64UrlSafe(QByteArray bytes);
    static QByteArray base64UrlSafe2Bytes(QString string);
    static QString bytes2hex(QByteArray bytes);
    static QByteArray hex2bytes(QString hex);
};
#endif // CONVERT_H
