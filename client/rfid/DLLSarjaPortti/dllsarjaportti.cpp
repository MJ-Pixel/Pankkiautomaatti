#include "dllsarjaportti.h"



/*DLLSarjaPortti::DLLSarjaPortti()
{
}*/

void DLLSarjaPortti::readCard()
{
    serial = new QSerialPort(this);
    serial->setPortName("com1");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if(!serial->open(QIODevice::ReadWrite)){
        qDebug () << serial->error() << endl;
    }else{
        qDebug () << "Portname:" << serial->portName() << endl;
    }
     connect(serial,SIGNAL(readyRead()),this,SLOT(writeData()));


}

QString DLLSarjaPortti::simulateCard()
{
    return "0B0035CD90";
}

void DLLSarjaPortti::writeData()
{
    char data[20];
    int bytesRead;
    bytesRead = serial->read(data,20);
    data[bytesRead] = '\0';

    if (bytesRead>10)
    {
        for (int i=0;i<=9;i++)
        {
            cardID = data;
        }
        cardID = cardID.simplified().remove(0,1).remove(11,1);

        qDebug () << "CardID:" << cardID << endl;
        emit readComplete(QString(cardID));
    }else{
        qDebug () << "Reading card error" << endl;
    }
}
