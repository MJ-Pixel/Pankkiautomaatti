#include "datarequestcontroller.h"

DataRequestController::DataRequestController(QObject *parent) : QObject(parent){
    API = new JsonRequestController(this);
}

DataRequestController::~DataRequestController(){
    delete API;
}

void DataRequestController::login(int cardId, int pin){
    qDebug() << cardId << " " << pin << endl;
}

void DataRequestController::withdraw(double amount){
    qDebug() << amount << endl;
}

void DataRequestController::payment(double amount, PaymentInfo info){
    qDebug() << amount << " " << endl;
}

void DataRequestController::events(QDate dateStart, QDate dateEnd){
    qDebug() << dateStart << " " << dateEnd << endl;
}

void DataRequestController::receiveRequestError(int code, QString msg){
    qDebug() << code << " " << msg << endl;
}

void DataRequestController::receiveRequestComplete(int id, QString response){
    qDebug() << id << " " << response << endl;
}
