#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCheckBox>
#include <QDialog>
#include <vector>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void MainScreen();
    void PaymentScreen();
    void LoginScreen();
    void BalanceScreen();
    void WithdrawScreen();
    //Transactioniin voi luoda labeleita dynaamisesti seuraavanlailla
    //QLabel *label = new QLabel(<info>, this);
    int randInt(int low, int high);

    bool login = false;

private slots:

    void on_main_payment_button_clicked();

    void on_payment_confirm_button_clicked();

    void on_main_balance_button_clicked();

    void on_main_withdraw_button_clicked();

    void on_withdraw_confirm_button_clicked();

    void on_login_login_button_clicked();

    void on_main_transaction_button_clicked();

    void on_login_mix_button_clicked();

    void on_login_reset_button_clicked();

    void on_login_numpad_button1_clicked();

    void on_login_numpad_button2_clicked();

    void on_login_numpad_button3_clicked();

    void on_login_numpad_button4_clicked();

    void on_login_numpad_button5_clicked();

    void on_login_numpad_button6_clicked();

    void on_login_numpad_button7_clicked();

    void on_login_numpad_button8_clicked();

    void on_login_numpad_button9_clicked();

    void on_login_empty_button_clicked();

private:
    Ui::MainWindow *ui;
    QMessageBox msg;
    QDialog qDia;

    void SetBalance();
    void LoginCheck();
    void ResetNumpad();
    void NumpadRandom();
    void ClearPayment();
    void ClearWithdraw();
    void ErrorMessage();

    QString balanceAmmount = "100";
    QVector<QWidget *> vec;

};
#endif // MAINWINDOW_H
