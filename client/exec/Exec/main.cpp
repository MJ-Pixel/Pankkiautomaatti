#include <QCoreApplication>
#include "C:/BankSimul/Pankkiautomaatti/client/rfid/DLLSarjaPortti/DLLSarjaPortti.h"
#include "C:/BankSimul/Pankkiautomaatti/client/mysql/DLLMySQL/DLLMySQL.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(DLLMySQL::connectToDb()){
        if(DLLMySQL::login("0B0035CD90", "1234")){
            if(DLLMySQL::withdraw(15)){
                qDebug() << "Success";
            } else {
                qDebug() << "Failed";
            }
        }
    }
    return a.exec();
}
