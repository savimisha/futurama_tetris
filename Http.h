#ifndef HTTP_H
#define HTTP_H

#include <QObject>
#include <QtNetwork>
#include <QJsonDocument>

class Http: public QObject
{
    Q_OBJECT
signals:
    void onSuccess();
    void onSuccess(QJsonDocument doc);
    void onFailure(int);
private slots:
    void replyFinished(QNetworkReply*);
public:
    Http(QString);
    Http();
    ~Http();
    void GET(const QString);
    void POST(const QString, const QJsonDocument);

private:
    QString host;
    QNetworkAccessManager *manager;
};

#endif // HTTP_H
