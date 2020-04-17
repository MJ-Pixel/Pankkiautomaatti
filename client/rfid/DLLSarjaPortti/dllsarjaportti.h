#ifndef DLLSARJAPORTTI_H
#define DLLSARJAPORTTI_H
#include <QSerialPort>
#include <QDebug>
#include <QString>
#include <QObject>
#include "dllsarjaportti_global.h"

using namespace std;

class DLLSARJAPORTTISHARED_EXPORT DLLSarjaPortti : public QObject
{
    Q_OBJECT
public:
   // DLLSarjaPortti();
    void DLLSARJAPORTTISHARED_EXPORT readCard();
    static QString DLLSARJAPORTTISHARED_EXPORT simulateCard();
private:
    QString cardID;
   // QString returnCardID;
    QSerialPort *serial;
signals:
    void DLLSARJAPORTTISHARED_EXPORT readComplete(QString id);
public slots:
    void writeData();

};

#endif // DLLSARJAPORTTI_H
