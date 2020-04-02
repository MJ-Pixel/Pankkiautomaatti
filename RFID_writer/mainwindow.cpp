#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_writeCardBtn_clicked()
{
    if(ui->cardId->text() == ""){
        ui->writerLog->appendPlainText("ERROR: Cannot write empty id");
    }else{
        ui->writerLog->appendPlainText("Attempting to write card with id: "+ui->cardId->text());
        if(false){
            ui->writerLog->appendPlainText("ERROR: RFID device not present");
        }else{
            ui->writerLog->appendPlainText("Writer waiting, insert card");
            ui->writeCardBtn->setDisabled(1);
        }

    }
}

void MainWindow::on_searchBtn_clicked()
{
    if(ui->search->text().length() < 3){
        ui->writerLog->appendPlainText("FETCH ERROR: Input at least 3 characters");
    }else{
        ui->searchBtn->setText("...");
        ui->searchBtn->setDisabled(1);
        ui->writerLog->appendPlainText("Searching from database");

        // sql connection and search
        QSqlDatabase db;
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("mysli.oamk.fi");
        db.setDatabaseName("opisk_t9haju03");
        db.setPort(3306);
        db.setUserName("t9haju03");
        db.setPassword("a6n6QLe8pEC7nJ4j");

        if(!db.open()){
            ui->writerLog->appendPlainText("FETCH ERROR: Connection to database failed");
            ui->searchBtn->setText("Search");
            ui->searchBtn->setDisabled(0);
            return;
        }

        QSqlQuery query;
        query.prepare("SELECT user_id FROM tilitiedot WHERE user_first LIKE ':param'% OR user_last LIKE ':param'%");
        query.bindValue(":param", ui->search->text());
        query.exec();

        if(query.size() == 0){
            ui->writerLog->appendPlainText("FETCH ERROR: No matches found");
            ui->searchBtn->setText("Search");
            ui->searchBtn->setDisabled(0);
            return;
        }

        while(query.next()){
            ui->writerLog->appendPlainText("FOUND");
        }

        ui->searchResults->addItem("Etu Suku: 12591383192");
        ui->searchResults->addItem("Etu2 Suku2: 125935353192");

        ui->searchBtn->setText("Search");
        ui->searchBtn->setDisabled(0);
    }
}

void MainWindow::on_insertSelectedBtn_clicked()
{
    if(ui->searchResults->selectedItems().size() != 0){
        QString s_id = ui->searchResults->currentItem()->text();
        int pos = s_id.indexOf(":");
        s_id = s_id.right(s_id.length()-pos-2);
        ui->cardId->setText(s_id);
    }
}
