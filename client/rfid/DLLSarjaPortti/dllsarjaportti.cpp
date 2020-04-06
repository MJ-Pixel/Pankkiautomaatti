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

QString DLLSarjaPortti::writeData()
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
                cardID.remove(0,3);
               // cardID = cardID.trimmed();
                qDebug () << "CardID:" << cardID << endl;
            }
            else
                qDebug () << "Reading card error" << endl;


            return cardID;
}

void DLLSarjaPortti::bSignal()
{
    emit aSignal();
}
