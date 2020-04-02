#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:


private slots:
    void on_writeCardBtn_clicked();

    void on_searchBtn_clicked();

    void on_insertSelectedBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
