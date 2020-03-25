#ifndef DLLMYSQL_H
#define DLLMYSQL_H

#include "DLLMySQL_global.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QtSql>
#include <QCoreApplication>

class DLLMySQL
{
public:
    static QSqlDatabase& connectToDb();
};

QSqlDatabase& DLLMySQL::connectToDb()
{
    static QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mysli.oamk.fi");     // host
    db.setDatabaseName("opisk_t9haju03");            // database
    db.setPort(3306);
    db.setUserName("t9haju03");                // user
    db.setPassword("a6n6QLe8pEC7nJ4j");              // password

    bool ok = db.open();

    if(ok){
        qDebug() << "Connection to database open";
    } else {
        qDebug() << "Driver in use: " + db.driverName();
        qDebug() << "Couldn't open connection to database";
        qDebug() << db.lastError().text();
    }
    return db;
}

#endif // DLLMYSQL_H
