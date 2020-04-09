#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
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
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::PaymentScreen()
{
    ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWindow::LoginScreen()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::BalanceScreen()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::WithdrawScreen()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}
void MainWindow::on_main_payment_button_clicked()
{
    ClearPayment();
    ClearWithdraw();
    EnableBalance();
    EnableWithdraw();
    DisablePayment();
    PaymentScreen();
}

void MainWindow::on_main_balance_button_clicked()
{
    ClearPayment();
    ClearWithdraw();
    BalanceScreen();
    EnablePayment();
    EnableWithdraw();
    DisableBalance();
    SetBalance();
}

void MainWindow::on_main_withdraw_button_clicked()
{
    ClearPayment();
    ClearWithdraw();
    EnablePayment();
    EnableBalance();
    DisableWithdraw();
    WithdrawScreen();
    SetBalance();
}

void MainWindow::on_main_transaction_button_clicked()
{
    ClearPayment();
    ClearWithdraw();
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

void MainWindow::ClearPayment()
{
    ui->payment_sum_line->setText("");
    ui->payment_name_line->setText("");
    ui->payment_accnum_line->setText("");
}

void MainWindow::ClearWithdraw()
{
    ui->withdraw_ammount_line->setText("");
}

void MainWindow::ErrorMessage()
{
    msg.critical(this,tr("Wrong Password!"), tr("Wrong Password!"));
    ui->login_password_line->setText("");
}
void MainWindow::on_login_login_button_clicked()
{
    if(ui->login_password_line->text() == "1234")
    {
        login=true;
    }
    LoginCheck();
}

void MainWindow::LoginCheck()
{
    if(login == true){
        MainScreen();
    }else
    {
        ErrorMessage();
    }
}

int MainWindow::randInt(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}

void MainWindow::ResetNumpad()
{
    ui->gridLayout->addWidget(ui->login_numpad_button1, 0, 0);
    ui->gridLayout->addWidget(ui->login_numpad_button2, 0, 1);
    ui->gridLayout->addWidget(ui->login_numpad_button3, 0, 2);
    ui->gridLayout->addWidget(ui->login_numpad_button4, 1, 0);
    ui->gridLayout->addWidget(ui->login_numpad_button5, 1, 1);
    ui->gridLayout->addWidget(ui->login_numpad_button6, 1, 2);
    ui->gridLayout->addWidget(ui->login_numpad_button7, 2, 0);
    ui->gridLayout->addWidget(ui->login_numpad_button8, 2, 1);
    ui->gridLayout->addWidget(ui->login_numpad_button9, 2, 2);
}

void MainWindow::NumpadRandom()
{
    int maxValue = 8;
    int randValue;

    vec.push_back(ui->login_numpad_button1);
    vec.push_back(ui->login_numpad_button2);
    vec.push_back(ui->login_numpad_button3);
    vec.push_back(ui->login_numpad_button4);
    vec.push_back(ui->login_numpad_button5);
    vec.push_back(ui->login_numpad_button6);
    vec.push_back(ui->login_numpad_button7);
    vec.push_back(ui->login_numpad_button8);
    vec.push_back(ui->login_numpad_button9);


    for(int y = 0; y <= 2; y++)
    {
        for (int x = 0; x <= 2; x++)
        {
            randValue = randInt(0,maxValue);
            ui->gridLayout->addWidget(vec[randValue],x,y);
            vec.erase(vec.begin() + randValue);
            maxValue--;
        }
    }
}

void MainWindow::on_login_mix_button_clicked()
{
    NumpadRandom();
    ui->login_mix_button->setEnabled(false);
    ui->login_reset_button->setEnabled(true);
    randomiser = true;
}

void MainWindow::on_login_reset_button_clicked()
{
    ResetNumpad();
    ui->login_mix_button->setEnabled(true);
    ui->login_reset_button->setEnabled(false);
    randomiser = false;
}

void MainWindow::on_login_numpad_button1_clicked()
{
    ui->login_password_line->setText(ui->login_password_line->text() + "1");
    ButtonMadness();
    if(randomiser)
    {
        NumpadRandom();
    }
}

void MainWindow::on_login_numpad_button2_clicked()
{
    ui->login_password_line->setText(ui->login_password_line->text() + "2");
    ButtonMadness();
    if(randomiser)
    {
        NumpadRandom();
    }
}

void MainWindow::on_login_numpad_button3_clicked()
{
    ui->login_password_line->setText(ui->login_password_line->text() + "3");
    ButtonMadness();
    if(randomiser)
    {
        NumpadRandom();
    }
}

void MainWindow::on_login_numpad_button4_clicked()
{
    ui->login_password_line->setText(ui->login_password_line->text() + "4");
    ButtonMadness();
    if(randomiser)
    {
        NumpadRandom();
    }
}

void MainWindow::on_login_numpad_button5_clicked()
{
    ui->login_password_line->setText(ui->login_password_line->text() + "5");
    ButtonMadness();
    if(randomiser)
    {
        NumpadRandom();
    }
}

void MainWindow::on_login_numpad_button6_clicked()
{
    ui->login_password_line->setText(ui->login_password_line->text() + "6");
    ButtonMadness();
    if(randomiser)
    {
        NumpadRandom();
    }
}

void MainWindow::on_login_numpad_button7_clicked()
{
    ui->login_password_line->setText(ui->login_password_line->text() + "7");
    ButtonMadness();
    if(randomiser)
    {
        NumpadRandom();
    }
}

void MainWindow::on_login_numpad_button8_clicked()
{
    ui->login_password_line->setText(ui->login_password_line->text() + "8");
    ButtonMadness();
    if(randomiser)
    {
        NumpadRandom();
    }
}

void MainWindow::on_login_numpad_button9_clicked()
{
    ui->login_password_line->setText(ui->login_password_line->text() + "9");
    ButtonMadness();
    if(randomiser)
    {
        NumpadRandom();
    }
}

void MainWindow::on_login_empty_button_clicked()
{
    ui->login_password_line->setText("");
    /*firstNumber = false;
    secondNumber = false;
    thirdNumber = false;
    fourthNumber = false;*/
}

void MainWindow::EnableBalance()
{
    ui->main_balance_button->setEnabled(true);
}

void MainWindow::DisableBalance()
{
    ui->main_balance_button->setEnabled(false);
}

void MainWindow::EnablePayment()
{
    ui->main_payment_button->setEnabled(true);
}

void MainWindow::DisablePayment()
{
    ui->main_payment_button->setEnabled(false);
}

void MainWindow::EnableWithdraw()
{
    ui->main_withdraw_button->setEnabled(true);
}

void MainWindow::DisableWithdraw()
{
    ui->main_withdraw_button->setEnabled(false);
}

void MainWindow::ButtonMadness()
{
    QString str = "";
    str.append(ui->login_password_line->text());

    if(str.size() == 4)
    {
        on_login_login_button_clicked();
    }else
    {
        str = "";
    }
    /*if(firstNumber && secondNumber && thirdNumber && !fourthNumber)
    {
        on_login_login_button_clicked();
        firstNumber = false;
        secondNumber = false;
        thirdNumber = false;
        fourthNumber = false;
    }else if(firstNumber && secondNumber && !thirdNumber && !fourthNumber)
    {
        thirdNumber = true;
    }else if(firstNumber && !secondNumber && !thirdNumber && !fourthNumber)
    {
        secondNumber = true;
    }else if(!firstNumber && !secondNumber && !thirdNumber && !fourthNumber)
    {
        firstNumber = true;
    }*/
}
