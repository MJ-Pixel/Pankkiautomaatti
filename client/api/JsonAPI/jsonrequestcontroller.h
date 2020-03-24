#ifndef JSONREQUESTCONTROLLER_H
#define JSONREQUESTCONTROLLER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QDebug>

class JsonRequestController : public QObject
{
    Q_OBJECT

public:
    explicit JsonRequestController(QObject *parent = 0);
    ~JsonRequestController();

    void request(int type, QString endPoint, QString apiKey, QString params);

private:
    QNetworkAccessManager *requestManager;

private slots:
    void processRequest(QNetworkReply* response);

signals:
    void requestError(int code, QString msg);
    void requestComplete(QString response);
};

#endif // JSONREQUESTCONTROLLER_H
