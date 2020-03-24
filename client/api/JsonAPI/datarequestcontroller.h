#ifndef DATAREQUESTCONTROLLER_H
#define DATAREQUESTCONTROLLER_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QDebug>

#include "jsonrequestcontroller.h"

struct PaymentInfo{
    QString name;
    QString iban;
    QString bicc;
    QString message;
    QString reference;
};

class DataRequestController : public QObject
{
    Q_OBJECT

public:
    explicit DataRequestController(QObject *parent = 0);
    ~DataRequestController();

    void login(int cardId, int pin);
    void withdraw(double amount);
    void payment(double amount, struct PaymentInfo info);
    void events(QDate dateStart, QDate dateEnd);

private:
    JsonRequestController *API;

private slots:
    void receiveRequestError(int code, QString msg);
    void receiveRequestComplete(int id, QString response);

signals:
    void loginComplete();
    void withdrawComplete();
    void paymentComplete();
    void eventsComplete();
};

#endif // DATAREQUESTCONTROLLER_H
