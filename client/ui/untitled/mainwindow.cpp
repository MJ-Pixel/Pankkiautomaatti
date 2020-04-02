#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    PaymentScreenOff();
    BalanceScreenOff();
    WithdrawScreenOff();
    MainScreenOff();
    LoginScreenOn();
    login = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MainScreenOn()
{
    ui->main_welcome_label->setText("Welcome!");
    ui->main_balance_button->setVisible(true);
    ui->main_payment_button->setVisible(true);
    ui->main_withdraw_button->setVisible(true);
    ui->main_transaction_button->setVisible(true);
    balanceTimer = 3;
}

void MainWindow::MainScreenOff()
{
    ui->main_balance_button->setVisible(false);
    ui->main_payment_button->setVisible(false);
    ui->main_withdraw_button->setVisible(false);
    ui->main_transaction_button->setVisible(false);
}
void MainWindow::PaymentScreenOn()
{
    ui->main_welcome_label->setText("Payment");
    ui->payment_back_button->setVisible(true);
    ui->payment_sum_line->setVisible(true);
    ui->payment_name_line->setVisible(true);
    ui->payment_accnum_line->setVisible(true);
    ui->payment_sum_label->setVisible(true);
    ui->payment_name_label->setVisible(true);
    ui->payment_accnum_label->setVisible(true);
    ui->payment_confirm_button->setVisible(true);
}

void MainWindow::PaymentScreenOff()
{
    ui->payment_back_button->setVisible(false);
    ui->payment_sum_line->setVisible(false);
    ui->payment_name_line->setVisible(false);
    ui->payment_accnum_line->setVisible(false);
    ui->payment_sum_label->setVisible(false);
    ui->payment_name_label->setVisible(false);
    ui->payment_accnum_label->setVisible(false);
    ui->payment_confirm_button->setVisible(false);
}

void MainWindow::BalanceScreenOn()
{
    ui->main_welcome_label->setText("Balance");
    ui->balance_usable_label->setVisible(true);
    ui->balance_ammount_label->setVisible(true);
    ui->balance_balance_label->setVisible(true);
    ui->balance_ammount_label_2->setVisible(true);
    ui->balance_back_button->setVisible(true);
}

void MainWindow::BalanceScreenOff()
{
    ui->balance_usable_label->setVisible(false);
    ui->balance_ammount_label->setVisible(false);
    ui->balance_balance_label->setVisible(false);
    ui->balance_ammount_label_2->setVisible(false);
    ui->balance_back_button->setVisible(false);
}

void MainWindow::on_main_payment_button_clicked()
{
    MainScreenOff();
    PaymentScreenOn();

}

void MainWindow::on_payment_back_button_clicked()
{
    MainScreenOn();
    PaymentScreenOff();
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
        MainScreenOn();
        PaymentScreenOff();
    }else if(msg.clickedButton() == noButton){
        msg.removeButton(noButton);
        msg.removeButton(confirmButton);
    }
}

void MainWindow::on_main_balance_button_clicked()
{
    MainScreenOff();
    BalanceScreenOn();
    balanceTimer = 100;
    SetBalance();
    //BalanceTimer(); //ei toimi vielä, ei varmaan voi looppeja käyttää tai jotain...

}

void MainWindow::on_balance_back_button_clicked()
{
    BalanceScreenOff();
    MainScreenOn();
    balanceTimer = 0;
}

void MainWindow::BalanceTimer()
{

    for(int i = balanceTimer; i > 0; i--)
    {
        MainScreenOn();
        BalanceScreenOff();
    }

    //MainScreenOn();
    //BalanceScreenOff();
    //balanceScreen = false;
}

void MainWindow::WithdrawScreenOn()
{
    ui->main_welcome_label->setText("Withdraw");
    ui->withdraw_back_button->setVisible(true);
    ui->withdraw_ammount_line->setVisible(true);
    ui->withdraw_ammount_label->setVisible(true);
    ui->withdraw_confirm_button->setVisible(true);
    ui->balance_usable_label->setVisible(true);
    ui->balance_balance_label->setVisible(true);
    ui->balance_ammount_label->setVisible(true);
    ui->balance_ammount_label_2->setVisible(true);
}

void MainWindow::WithdrawScreenOff()
{
    ui->withdraw_back_button->setVisible(false);
    ui->withdraw_ammount_line->setVisible(false);
    ui->withdraw_ammount_label->setVisible(false);
    ui->withdraw_confirm_button->setVisible(false);
    ui->balance_usable_label->setVisible(false);
    ui->balance_balance_label->setVisible(false);
    ui->balance_ammount_label->setVisible(false);
    ui->balance_ammount_label_2->setVisible(false);
}

void MainWindow::on_main_withdraw_button_clicked()
{
    WithdrawScreenOn();
    MainScreenOff();
}

void MainWindow::on_withdraw_back_button_clicked()
{
    WithdrawScreenOff();
    MainScreenOn();
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
        MainScreenOn();
        WithdrawScreenOff();
    }else if(msg.clickedButton() == noButton){
        msg.removeButton(noButton);
        msg.removeButton(confirmButton);
    }
}

void MainWindow::SetBalance()
{
    ui->balance_ammount_label->setText(balanceAmmount);
    ui->balance_ammount_label_2->setText(balanceAmmount);
}

void MainWindow::on_login_login_button_clicked()
{
    //login = true;
    LoginCheck();
}

void MainWindow::LoginCheck()
{
    if(login == true){
        MainScreenOn();
        LoginScreenOff();
    }
}

void MainWindow::LoginScreenOn()
{
    ui->main_welcome_label->setText("Login");
    ui->login_username_line->setVisible(true);
    ui->login_password_label->setVisible(true);
    ui->login_username_label->setVisible(true);
    ui->login_password_line->setVisible(true);
    ui->login_login_button->setVisible(true);
}

void MainWindow::LoginScreenOff()
{
    ui->login_username_line->setVisible(false);
    ui->login_password_label->setVisible(false);
    ui->login_username_label->setVisible(false);
    ui->login_password_line->setVisible(false);
    ui->login_login_button->setVisible(false);
}


