#include "http.h"

Http::Http(QString host)
{
    this->host = host;
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}
Http::~Http()
{
    disconnect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    delete manager;
}

void Http::GET(const QString url)
{
    QSslConfiguration sslConfiguration(QSslConfiguration::defaultConfiguration());
    sslConfiguration.setProtocol(QSsl::TlsV1_2);
    QNetworkRequest request = QNetworkRequest(QUrl(host + url));
    request.setSslConfiguration(sslConfiguration);
    manager->get(request);
}

void Http::POST(const QString url, const QJsonDocument body)
{
    QSslConfiguration sslConfiguration(QSslConfiguration::defaultConfiguration());
    sslConfiguration.setProtocol(QSsl::TlsV1_2);
    QNetworkRequest request = QNetworkRequest(QUrl(host + url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setSslConfiguration(sslConfiguration);
    manager->post(request, body.toJson(QJsonDocument::Compact));
}

void Http::replyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        auto data = reply->readAll();
        if (data.length() == 0) {
            emit onSuccess();
        } else {
            QJsonParseError error;
            auto doc = QJsonDocument::fromJson(data, &error);
            if (error.error == QJsonParseError::NoError)
            {
                emit onSuccess(doc);
            } else {
                emit onFailure(-1000);
            }
        }
    } else {
        emit onFailure((int)reply->error());
    }
}
