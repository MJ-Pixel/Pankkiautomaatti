/*
#include "dllmysql.h"
#include "C:\Users\Hadis\Documents\Qt\Olio-ohjelmoinnin_jatkokurssi\MyDLL\mydll.h"

void DLLMySQL::connectToDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("MYSQL");
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
}

bool DLLMySQL::connectToDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("MYSQL");
    db.setHostName("mysli.oamk.fi");     // host
    db.setDatabaseName("opisk_t9haju03");            // database
    db.setPort(3306);
    db.setUserName("t9haju03");                // user
    db.setPassword("a6n6QLe8pEC7nJ4j");              // password

    bool ok = db.open();

    if(ok){
        qDebug() << "Connection to database open";
        return true;
    } else {
        qDebug() << "Driver in use: " + db.driverName();
        qDebug() << "Couldn't open connection to database";
        qDebug() << db.lastError().text();
        return false;
    }
}

int DLLMySQL::test()
{
    return (1+1);
}
*/
