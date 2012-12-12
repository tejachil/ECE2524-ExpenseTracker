#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    roommateProcess = new QProcess();
    expenseProcess = new QProcess();
    connect(roommateProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(roommateOut()));
    connect(expenseProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(expenseOut()));
    refreshUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAdd_clicked()
{
    roommateComm = ADD;
    QStringList args;
    args << "python/roommate.py" << "-a" << ui->leAdd->text();
    roommateProcess->start("python", args);
    roommateProcess->waitForFinished();
    expenseCommView = false;
    refreshUI();
}

void MainWindow::roommateOut(){
    QString newData = roommateProcess->readAllStandardOutput();
    //qDebug() << roommateComm;
    switch(roommateComm){
    case ALL:
        ui->listRoommates->clear();
        ui->comboPaidRoommate->clear();
        ui->comboViewExpense->clear();
        roommates = newData.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
        //qDebug() << roommates.size();
        removeList = new QListWidgetItem*[roommates.size()];
        expenseList = new QListWidgetItem*[roommates.size()];
        for(int i = 0; i < roommates.size(); ++i){
            removeList[i] = new QListWidgetItem(roommates.at(i), ui->listRoommates);
            removeList[i]->setCheckState(Qt::Unchecked);
            expenseList[i] = new QListWidgetItem(roommates.at(i), ui->listExpense);
            expenseList[i]->setCheckState(Qt::Unchecked);
            ui->comboPaidRoommate->addItem(roommates.at(i));
            ui->comboViewExpense->addItem(roommates.at(i));
        }
        break;
    case ADD:
        break;
    case REMOVE:
        break;
    }
}

void MainWindow::refreshUI(){
    roommateComm = ALL;
    QStringList args;
    args << "python/roommate.py" << "-al";
    roommateProcess->start("python", args);

    //QListWidgetItem *item0 = new QListWidgetItem(tr("First"), ui->listRoommates);
    //item0->setCheckState(Qt::Unchecked);
    //ui->listRoommates->item(0)->setFlags(ui->listWidget->item(0)->flags() |Qt::ItemIsUserCheckable);
    //ui->listRoommates->item(0)->setCheckState(Qt::Unchecked);
}

void MainWindow::on_btnRemove_clicked(){
    roommateComm = REMOVE;
    for (int i = 0; i < roommates.size(); ++i){
        if (removeList[i]->checkState()){
            QStringList args;
            args << "python/roommate.py" << "-r" << removeList[i]->text();
            roommateProcess->start("python", args);
            roommateProcess->waitForFinished();
        }
    }
    refreshUI();
}

void MainWindow::on_btnAddExpense_clicked(){
    QStringList args;
    //QString name = ui->comboPaidRoommate->itemData(ui->comboPaidRoommate->currentIndex()).toString();
    //qDebug() << ui->comboPaidRoommate->currentText();
    args << "python/expense.py" << "add" << ui->comboPaidRoommate->currentText() << ui->leAmount->text();
    for (int i = 0; i < roommates.size(); ++i){
        if (expenseList[i]->checkState()){
            args << expenseList[i]->text();
        }
    }
    //qDebug() << args;
    expenseProcess->start("python", args);
    expenseProcess->waitForFinished();
}

void MainWindow::expenseOut(){
    QString newData = expenseProcess->readAllStandardOutput();
    //qDebug() << newData;
    if(expenseCommView){
        ui->teView->setText(newData);
        expenseCommView = false;
    }
}

void MainWindow::on_btnView_clicked(){
    QStringList args;
    args << "python/expense.py" << "view" << ui->comboViewExpense->currentText();
    expenseCommView = true;
    expenseProcess->start("python", args);
    expenseProcess->waitForFinished();
}
