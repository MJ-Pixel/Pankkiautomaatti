#ifndef DLLMYSQL_H
#define DLLMYSQL_H

#include "DLLMySQL_global.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QtSql>
#include <QString>
#include <QSqlQuery>
#include <QVector>

using namespace std;


class DLLMySQL
{
public:
    struct PaymentInfo {
        int type;
        double amount;
        QString name;
        QString iban;
        QString bicc;
        QString message;
        QString reference;
    };
    static bool connectToDb();
    static bool login(QString cardid, QString pin);
    static bool withdraw(double amount);
    static bool payment(PaymentInfo info);
    static QVector<QString> specificEvents(QString dateStart, QString dateEnd);
    static QVector<QString> events();
    static QString balance();
    static void test();

private:
    static int id;
};

#endif // DLLMYSQL_H
