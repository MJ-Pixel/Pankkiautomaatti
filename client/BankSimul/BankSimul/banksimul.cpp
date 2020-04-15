#include "banksimul.h"

BankSimul::BankSimul(QObject *parent) : QObject(parent)
{
    serialReader = new DLLSarjaPortti();
    serialReader->readCard();

    db = new DLLMySQL();
    db->connectToDb();

    // just passing the event from cardreader through
    QObject::connect(serialReader, &DLLSarjaPortti::readComplete, [this](QString cardId){
        emit this->readComplete(cardId);
    });

    // this is just for testing purposes
    QTimer *timer = new QTimer(this);
    QObject::connect(timer, QTimer::timeout, [this](){
        emit this->readComplete("0B0035CD90");
    });
    timer->setInterval(5000);
    timer->setSingleShot(true);
    timer->start();

}

BankSimul::~BankSimul()
{

}

void BankSimul::login(QString cardId, QString password)
{
    emit loginComplete(db->login(cardId, password));
}

QString BankSimul::loadBalance()
{
    return db->balance();
}

bool BankSimul::withdraw(double amount)
{
    return db->withdraw(amount);
}

bool BankSimul::payment(QString name, QString accnum, QString sum)
{
    DLLMySQL::PaymentInfo info;

    info.type = 1;
    info.bicc = "";
    info.message = "Maksu";
    info.name = name;
    info.amount = sum.toDouble();
    info.iban = accnum;

    return db->payment(info);
}

QVector<QString> BankSimul::transactions(){
    return db->events();
}
