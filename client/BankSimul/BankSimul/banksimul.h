#ifndef BANKSIMUL_H
#define BANKSIMUL_H

#include <QObject>
#include <QString>
#include <QTimer>
#include "include/dllmysql.h"
#include "include/dllsarjaportti.h"

class BankSimul : public QObject
{
    Q_OBJECT

public:
    explicit BankSimul(QObject *parent = 0);
    ~BankSimul();

    void login(QString cardId, QString password);
    QString loadBalance();
    bool withdraw(double amount);
    bool payment();
signals:
    void loginComplete(bool success);
    void readComplete(QString cardId);

private:
    DLLSarjaPortti *serialReader;
    DLLMySQL *db;
};

#endif // BANKSIMUL_H
