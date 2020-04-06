#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoginScreen();
    SetBalance();
    login = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MainScreen()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::PaymentScreen()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::LoginScreen()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::BalanceScreen()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::WithdrawScreen()
{
    ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::on_main_payment_button_clicked()
{
    PaymentScreen();
}

void MainWindow::on_payment_back_button_clicked()
{
    MainScreen();
}

void MainWindow::on_payment_confirm_button_clicked()
{
    QString nameValue = ui->payment_name_line->text();
    QString accnumValue = ui->payment_accnum_line->text();
    QString sumValue = ui->payment_sum_line->text();

    QAbstractButton *noButton = msg.addButton(tr("no"), QMessageBox::ActionRole);
    QAbstractButton *confirmButton = msg.addButton(tr("confirm"), QMessageBox::ActionRole);
    QString str = QString("Are you sure?\nName: %1\nAccount number: %2\nSum: %3").arg(nameValue).arg(accnumValue).arg(sumValue);
    msg.setText(str);
    msg.exec();

    if(msg.clickedButton() == confirmButton){
        msg.removeButton(noButton);
        msg.removeButton(confirmButton);
        MainScreen();
    }else if(msg.clickedButton() == noButton){
        msg.removeButton(noButton);
        msg.removeButton(confirmButton);
    }
}

void MainWindow::on_main_balance_button_clicked()
{
    BalanceScreen();
    balanceTimer = 100;
    SetBalance();
    //BalanceTimer(); //ei toimi vielä, ei varmaan voi looppeja käyttää tai jotain...

}

void MainWindow::on_balance_back_button_clicked()
{
    MainScreen();
    balanceTimer = 0;
}

void MainWindow::BalanceTimer()
{

    for(int i = balanceTimer; i > 0; i--)
    {
        MainScreen();
    }

    //MainScreenOn();
    //BalanceScreenOff();
    //balanceScreen = false;
}

void MainWindow::on_main_withdraw_button_clicked()
{
    WithdrawScreen();
}

void MainWindow::on_withdraw_back_button_clicked()
{
    MainScreen();
}

void MainWindow::on_withdraw_confirm_button_clicked()
{

    QString newBalance;
    QAbstractButton *noButton = msg.addButton(tr("no"), QMessageBox::ActionRole);
    QAbstractButton *confirmButton = msg.addButton(tr("confirm"), QMessageBox::ActionRole);
    QString str = QString("Are you sure?\nNew balance: %1").arg(newBalance);
    msg.setText(str);
    msg.exec();

    if(msg.clickedButton() == confirmButton){
        msg.removeButton(noButton);
        msg.removeButton(confirmButton);
        MainScreen();
    }else if(msg.clickedButton() == noButton){
        msg.removeButton(noButton);
        msg.removeButton(confirmButton);
    }
}

void MainWindow::SetBalance()
{
    ui->balance_ammount_label->setText(balanceAmmount);
    ui->balance_ammount_label_2->setText(balanceAmmount);
    ui->withdraw_ammount_label_2->setText(balanceAmmount);
}

void MainWindow::on_login_login_button_clicked()
{
    login = true;
    LoginCheck();
}

void MainWindow::LoginCheck()
{
    if(login == true){
        MainScreen();
    }
}

void MainWindow::on_main_transaction_button_clicked()
{

}
