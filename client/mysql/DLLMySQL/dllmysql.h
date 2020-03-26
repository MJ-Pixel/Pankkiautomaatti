#ifndef DLLMYSQL_H
#define DLLMYSQL_H

#include "DLLMySQL_global.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QtSql>
#include <QString>
#include <QSqlQuery>


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
    static QSqlDatabase& connectToDb();
    static QSqlDatabase& login(int cardid, QString pin);
    //static bool login(int cardid, int pin);
    static QSqlDatabase& withdraw(int id, double amount);
    void payment(double amount, PaymentInfo info);
    void events(QDate dateStart, QDate dateEnd);
    double balance();
    bool makeQuery();
};

QSqlDatabase& DLLMySQL::connectToDb()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mysli.oamk.fi");     // host
    db.setDatabaseName("opisk_t9haju03");            // database
    db.setPort(3306);
    db.setUserName("t9haju03");                // user
    db.setPassword("a6n6QLe8pEC7nJ4j");              // password

    if(db.open()){
        qDebug() << "Connection to database open";
    } else {
        qDebug() << "Driver in use: " + db.driverName();
        qDebug() << "Couldn't open connection to database";
        qDebug() << db.lastError().text();
    }
}

QSqlDatabase& DLLMySQL::login(int cardid, QString pin)
{
    if (QSqlDatabase::contains()){
        QSqlDatabase db = QSqlDatabase::database("MyDbConnection");
        QSqlQuery query;
        query.prepare("SELECT user_id, user_pin FROM kirjautuminen WHERE user_id = ? AND user_pin = ?");
        query.addBindValue(cardid);
        query.addBindValue(pin);
        query.exec();
        if (query.size() > 0){
            qDebug() << "User found";
        } else {
            qDebug() << "User not found";
        }
    } else {
        QSqlDatabase db;
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("mysli.oamk.fi");     // host
        db.setDatabaseName("opisk_t9haju03");            // database
        db.setPort(3306);
        db.setUserName("t9haju03");                // user
        db.setPassword("a6n6QLe8pEC7nJ4j");
    }
}

QSqlDatabase& DLLMySQL::withdraw(int cardid, double amount)
{
    if (QSqlDatabase::contains()){
        QSqlDatabase db = QSqlDatabase::database("MyDbConnection");
        QSqlQuery query;
        query.prepare("SELECT saldo FROM tilitiedot WHERE user_id = ?");
        query.addBindValue(cardid);
        query.exec();
        query.first();
        if (query.size() >= 0){
            qDebug() << "Found user's balance";
            double balance = query.value(0).toDouble();
            qDebug() << "User with ID: " << cardid << "'s balance is " << balance << " euro(s)";
            if(amount > balance){
                qDebug() << "Not enough funds (" << balance << " euro(s)) to complete the withdraw of " << amount << " euro(s)";
            } else if (amount <= balance){
                double math = balance - amount;
                query.prepare("UPDATE tilitiedot SET saldo = ? WHERE user_id = ?");
                query.addBindValue(math);
                query.addBindValue(cardid);
                if(query.exec()){
                    qDebug() << "Withdraw completed successfully";
                } else {
                    qDebug() << "Withdraw failed";
                }
            }
        } else if (query.size() == 0){
            qDebug() << "Didn't find user's balance";
        }
    } else {
        qDebug() << "Couldn't connect to database";
    }
}





#endif // DLLMYSQL_H
