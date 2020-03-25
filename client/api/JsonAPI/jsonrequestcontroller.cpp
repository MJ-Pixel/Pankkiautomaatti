#include "jsonrequestcontroller.h"

JsonRequestController::JsonRequestController(QObject *parent) : QObject(parent){}

JsonRequestController::~JsonRequestController(){}

void JsonRequestController::request(int id, int type, QString endPoint, QString apiKey, QString params){
    QNetworkAccessManager *requestManager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QNetworkReply *response;

    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setRawHeader(QByteArray("ApiKey"), QByteArray(apiKey.toUtf8()));
    request.setRawHeader(QByteArray("User-Agent"), QByteArray("Pankkiautomaatti"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/x-www-form-urlencoded"));

    qDebug() << "Initializing request with params: " << type << ", " << endPoint << ", " << apiKey << ", " << params << endl;

    // type 1 == GET, 2 == POST
    if(type == 1){
        request.setUrl(QUrl(endPoint + QString("?") + params));

        response = requestManager->get(request);

        qDebug() << "GET request sent, waiting for response" << endl;

        // using lambda to pass the request id forward
        QObject::connect(requestManager, &QNetworkAccessManager::finished, [this, response, id, requestManager](){
            this->processRequest(id, response);
            delete requestManager;
            delete response;
        });

    }else if(type == 2){
        request.setUrl(QUrl(endPoint));

        response = requestManager->post(request, QByteArray(params.toUtf8()));

        qDebug() << "POST request sent, waiting for response" << endl;

        // using lambda to pass the request id forward
        QObject::connect(requestManager, &QNetworkAccessManager::finished, [this, response, id, requestManager](){
            this->processRequest(id, response);
            delete requestManager;
            delete response;
        });

    }else{
        emit requestError(101, "Invalid request type");
        return;
    }

}

void JsonRequestController::processRequest(int id, QNetworkReply *response){
    QString responsePlain = response->readAll();

    if(response->error()){
        qDebug() << response->errorString() << endl;

        emit requestError(102, "Error in HTTP request");        
        return;
    }

    qDebug() << "Request id: " << id << endl;
    qDebug() << responsePlain << endl;

    emit requestComplete(id, responsePlain);
}
