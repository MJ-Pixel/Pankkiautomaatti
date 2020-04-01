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
    static bool login(int cardid, QString pin);
    static bool withdraw(double amount);
    static bool payment(PaymentInfo info);
    static void specificEvents(QString dateStart, QString dateEnd);
    static QVector<QString> events();
    static QString balance();
    static void test();

private:
    static int id;
    static QString my_format;
};

int DLLMySQL::id = 0;

bool DLLMySQL::connectToDb()
{
    bool result = false;

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mysli.oamk.fi");
    db.setDatabaseName("opisk_t9haju03");
    db.setPort(3306);
    db.setUserName("t9haju03");
    db.setPassword("a6n6QLe8pEC7nJ4j");

    if(db.open()){
        qDebug() << "Connection to database open";
        result = true;
    } else {
        qDebug() << "Driver in use: " + db.driverName();
        qDebug() << "Couldn't open connection to database";
        qDebug() << db.lastError().text();
    }
    return result;
}

bool DLLMySQL::login(int cardid, QString pin)
{
    bool result = false;
    if (QSqlDatabase::contains()){
        QSqlDatabase db = QSqlDatabase::database("MyDbConnection");
        QSqlQuery query;
        query.prepare("SELECT user_id, user_pin FROM kirjautuminen WHERE user_id = ? AND user_pin = ?");
        query.addBindValue(cardid);
        query.addBindValue(pin);
        query.exec();
        if (query.size() > 0){
            qDebug() << "User found";
            id = cardid;
            result = true;
        } else {
            qDebug() << "User not found";
        }
    }
    return result;
}

bool DLLMySQL::withdraw(double amount)
{
    bool result = false;
    if (QSqlDatabase::contains()){
        QSqlDatabase db = QSqlDatabase::database("MyDbConnection");
        QSqlQuery query;
        query.prepare("SELECT saldo FROM tilitiedot WHERE user_id = ?");
        query.addBindValue(id);
        query.exec();
        query.first();
        if (query.size() >= 0){
            qDebug() << "Found user's balance in withdraw()";
            double balance = query.value(0).toDouble();
            if(amount > balance){
                qDebug() << "Not enough funds to complete withdraw";
            } else if (amount <= balance){
                double math = balance - amount;
                query.prepare("UPDATE tilitiedot SET saldo = ? WHERE user_id = ?");
                query.addBindValue(math);
                query.addBindValue(id);
                if(query.exec()){
                    query.prepare("INSERT INTO tilitapahtumat (user_id, tyyppi, nimi, iban, bicc, summa, viite, viesti) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
                    result = true;
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
    return result;
}

bool DLLMySQL::payment(DLLMySQL::PaymentInfo info)
{

    bool result = false;

    qDebug() << info.type << info.amount << info.name<< info.iban << info.bicc << info.message << info.reference;

    if (QSqlDatabase::contains()){
        QSqlDatabase db = QSqlDatabase::database("MyDbConnection");
        QSqlQuery query;
        query.prepare("SELECT saldo FROM tilitiedot WHERE user_id = ?");
        query.addBindValue(id);
        query.exec();
        query.first();
        if (query.size() >= 0){
            qDebug() << "Found user's balance in payment()";
            double balance = query.value(0).toDouble();
            if(info.amount > balance){
                qDebug() << "Not enough funds to complete payment";
            } else if (info.amount <= balance){
                double math = balance - info.amount;
                qDebug() << "Math: " << math;
                query.prepare("UPDATE tilitiedot SET saldo = ? WHERE user_id = ?");
                query.addBindValue(math);
                query.addBindValue(id);
                if(query.exec()){
                    qDebug() << "Funds taken from ID's balance, proceeding to save payment info";
                    query.prepare("INSERT INTO tilitapahtumat (user_id, tyyppi, nimi, iban, bicc, summa, viite, viesti) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
                    query.addBindValue(id);
                    query.addBindValue(info.type);
                    query.addBindValue(info.name);
                    query.addBindValue(info.iban);
                    query.addBindValue(info.bicc);
                    query.addBindValue(info.amount);
                    query.addBindValue(info.reference);
                    query.addBindValue(info.message);
                    if(query.exec()){
                        qDebug() << "Payment information inserted successfully";
                        result = true;
                    } else {
                        qDebug() << "Inserting payment information failed";
                    }
                } else {
                    qDebug() << "Payment failed";
                }
            }
        }
    }
    return result;
}

void DLLMySQL::specificEvents(QString dateStart, QString dateEnd)
{
    int index = 0;
    QDebug deb = qDebug();
    qDebug() << "Results for events between dates " << dateStart << " and" << dateEnd;
    if (QSqlDatabase::contains()){
        QSqlDatabase db = QSqlDatabase::database("MyDbConnection");
        QSqlQuery query;
        query.prepare("SELECT * FROM tilitapahtumat WHERE user_id = ? AND time BETWEEN ? AND ? ORDER BY tapahtuma_id DESC");
        query.addBindValue(id);
        query.addBindValue(dateStart);
        query.addBindValue(dateEnd);
        query.exec();
        QSqlRecord rec = query.record();
        while(query.next()){
            for(int i = 0; i < rec.count(); i++){
                deb << query.value(i).toString();
                if(index == 9){
                    deb << endl;
                    index = 0;
                } else {
                    index++;
                }
            }
        }
    }
}

QVector<QString> DLLMySQL::events()
{
    qDebug() << "Results for last 10 events:";
    QVector<QString> stringVector;
    QDebug deb = qDebug();
    if (QSqlDatabase::contains()){
        QSqlDatabase db = QSqlDatabase::database("MyDbConnection");
        QSqlQuery query;
        query.prepare("SELECT * FROM tilitapahtumat WHERE user_id = ? ORDER BY tapahtuma_id DESC LIMIT 10");
        query.addBindValue(id);
        query.exec();
        QSqlRecord rec = query.record();
        while(query.next()){
            for(int j = 0; j < rec.count(); j++){
                deb << query.value(j).toString();
                stringVector.append(query.value(j).toString());
                if(j != 0 && j % 9 == 0){
                    deb << endl;
                }
            }
        }
    }
    return stringVector;
}

QString DLLMySQL::balance()
{
    QString result = "";
    if (QSqlDatabase::contains()){
        QSqlDatabase db = QSqlDatabase::database("MyDbConnection");
        QSqlQuery query;
        query.prepare("SELECT saldo FROM tilitiedot WHERE user_id = ?");
        query.addBindValue(id);
        query.exec();
        query.first();
        if (query.size() >= 0){
            qDebug() << "Found user's balance in balance()";
            double balance = query.value(0).toDouble();
            qDebug() << "User's balance is: " << balance << " euro(s)";
            result = QString::number(balance);
        } else {
            qDebug() << "Couldn't connect to database";
        }
    }
    return result;
}

void DLLMySQL::test()
{
    qDebug() << "test";
}





#endif // DLLMYSQL_H
