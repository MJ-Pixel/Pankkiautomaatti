#ifndef DLLMYSQL_H
#define DLLMYSQL_H

#include "DLLMySQL_global.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QtSql>
#include <QString>
#include <QSqlQuery>

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
    static QSqlDatabase& connectToDb();
    static QSqlDatabase& login(int cardid, QString pin);
    //static bool login(int cardid, int pin);
    static QSqlDatabase& withdraw(double amount);
    static QSqlDatabase& payment(PaymentInfo info);
    //static QSqlDatabase& events(QDate dateStart, QDate dateEnd);
    static QSqlDatabase& events();
    static QSqlDatabase& balance();

private:
    static int id;
};

int DLLMySQL::id = 0;

QSqlDatabase& DLLMySQL::connectToDb()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mysli.oamk.fi");
    db.setDatabaseName("opisk_t9haju03");
    db.setPort(3306);
    db.setUserName("t9haju03");
    db.setPassword("a6n6QLe8pEC7nJ4j");

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
            id = cardid;
        } else {
            qDebug() << "User not found";
        }
    }
}

QSqlDatabase& DLLMySQL::withdraw(double amount)
{
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

QSqlDatabase &DLLMySQL::payment(DLLMySQL::PaymentInfo info)
{

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
                    } else {
                        qDebug() << "Inserting payment information failed";
                    }
                } else {
                    qDebug() << "Payment failed";
                }
            }
        }
    }
}

QSqlDatabase &DLLMySQL::events()
{
    int index = 0;
    QDebug deb = qDebug();
    if (QSqlDatabase::contains()){
        QSqlDatabase db = QSqlDatabase::database("MyDbConnection");
        QSqlQuery query;

        for(int i = 0; i < 11; i++){
            query.prepare("SELECT * FROM tilitapahtumat WHERE user_id = ? ORDER BY tapahtuma_id DESC LIMIT 1 OFFSET ?");
            query.addBindValue(id);
            query.addBindValue(i);
            query.exec();
            QSqlRecord rec = query.record();
            while(query.next()){
                for(int j = 0; j < rec.count(); j++){
                    deb << query.value(j).toString();
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
}

QSqlDatabase &DLLMySQL::balance()
{
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
        } else {
            qDebug() << "Couldn't connect to database";
        }
    }
}





#endif // DLLMYSQL_H
