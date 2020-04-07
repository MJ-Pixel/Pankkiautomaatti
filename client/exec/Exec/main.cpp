#include <QCoreApplication>
#include "C:/BankSimul/Pankkiautomaatti/client/rfid/DLLSarjaPortti/DLLSarjaPortti.h"
#include "C:/BankSimul/Pankkiautomaatti/client/mysql/DLLMySQL/DLLMySQL.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(DLLMySQL::connectToDb()){
        if(DLLMySQL::login(DLLSarjaPortti::simulateCard(), "0000")){
            DLLMySQL::balance();
        }
    }
    return a.exec();
}
