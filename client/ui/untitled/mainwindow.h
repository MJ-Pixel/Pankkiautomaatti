#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCheckBox>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void MainScreenOn();
    void MainScreenOff();
    void PaymentScreenOn();
    void PaymentScreenOff();
    void BalanceScreenOn();
    void BalanceScreenOff();
    void WithdrawScreenOn();
    void WithdrawScreenOff();
    //Transactioniin voi luoda labeleita dynaamisesti seuraavanlailla
    //QLabel *label = new QLabel(<meijan info>, this);
    void LoginScreenOn();
    void LoginScreenOff();

    bool login = false;
private slots:
    void BalanceTimer();
    void SetBalance();
    void LoginCheck();

    void on_main_payment_button_clicked();

    void on_payment_back_button_clicked();

    void on_payment_confirm_button_clicked();

    void on_main_balance_button_clicked();

    void on_balance_back_button_clicked();

    void on_main_withdraw_button_clicked();

    void on_withdraw_back_button_clicked();

    void on_withdraw_confirm_button_clicked();

    void on_login_login_button_clicked();

private:
    Ui::MainWindow *ui;
    QMessageBox msg;
    QDialog qDia;

    int balanceTimer;
    QString balanceAmmount = "100";

};
#endif // MAINWINDOW_H
