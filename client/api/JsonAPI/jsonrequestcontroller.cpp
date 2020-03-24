#include "jsonrequestcontroller.h"

JsonRequestController::JsonRequestController(QObject *parent) : QObject(parent)
{
    this->requestManager = new QNetworkAccessManager(this);
}

JsonRequestController::~JsonRequestController(){
    delete this->requestManager;
}

void JsonRequestController::request(int type, QString endPoint, QString apiKey, QString params){
    QNetworkRequest request;
    QNetworkReply *response;

    request.setRawHeader(QByteArray("ApiKey"), QByteArray(apiKey.toUtf8()));
    request.setRawHeader(QByteArray("User-Agent"), QByteArray("Pankkiautomaatti"));

    qDebug() << "Initializing request with params: " << type << ", " << endPoint << ", " << apiKey << ", " << params << endl;

    // type 1 == GET, 2 == POST
    if(type == 1){
        request.setUrl(QUrl(endPoint));

        response = this->requestManager->get(request);

        qDebug() << "GET request sent, waiting for response" << endl;

        QObject::connect(this->requestManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(processRequest(QNetworkReply*)));

    }else if(type == 2){
        request.setUrl(QUrl(endPoint));

        response = this->requestManager->get(request);

        qDebug() << "POST request sent, waiting for response" << endl;

        QObject::connect(this->requestManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(processRequest(QNetworkReply*)));
    }else{
        emit requestError(101, "Invalid request type");
        return;
    }

}


void JsonRequestController::processRequest(QNetworkReply *response){
    if(response->error()){
        emit requestError(102, "Error in HTTP request");
        qDebug() << response->errorString() << endl;
        return;
    }

    qDebug() << response->readAll() << endl;
    emit requestComplete(response->readAll());
}
