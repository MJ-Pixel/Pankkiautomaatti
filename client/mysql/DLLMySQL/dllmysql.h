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
    static bool DLLMYSQL_EXPORT connectToDb();
    int DLLMYSQL_EXPORT test();
};

#endif // DLLMYSQL_H
