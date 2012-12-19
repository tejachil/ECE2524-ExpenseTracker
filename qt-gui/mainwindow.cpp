#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QDebug>

//Constructor for the main window that initializes the variables
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	//Allocates memory for the two process objects and connects slots to the signals
    ui->setupUi(this);
    roommateProcess = new QProcess();
    expenseProcess = new QProcess();
    connect(roommateProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(roommateOut()));
    connect(expenseProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(expenseOut()));
    refreshUI();
    
    setWindowTitle("Roommate Expense Tracker");
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Triggered when a new roommate is added
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

//The slot for the roommate process slot that reads the stdout from the roommate python
void MainWindow::roommateOut(){
    QString newData = roommateProcess->readAllStandardOutput();
    //qDebug() << roommateComm;
    switch(roommateComm){
    case ALL:
        ui->listRoommates->clear();
        ui->listExpense->clear();
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
        msgBox.setText(newData);
        if(newData.contains("Successfully")){
            msgBox.setWindowTitle("Succesfully Added!");
            msgBox.setIcon(QMessageBox::Information);
        }
        else{
            msgBox.setWindowTitle("Unable to Add!");
            msgBox.setIcon(QMessageBox::Critical);
        }
        msgBox.show();
        break;
    case REMOVE:
        msgBox.setText(newData);
        if(newData.contains("Successfully")){
            msgBox.setWindowTitle("Succesfully Removed!");
            msgBox.setIcon(QMessageBox::Information);
        }
        else{
            msgBox.setWindowTitle("Unable to Remove!");
            msgBox.setIcon(QMessageBox::Critical);
        }
        msgBox.show();
        break;
    }
}

//Refreshes the UI once a specific task is done or action is taken
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

//Triggered for removing a roommate
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

//Triggered for adding a new expense
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
    msgBox.setText("The selected expense was succesfully added to the data file.");
    msgBox.setWindowTitle("Expense Added!");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.show();
}

//Manages the stdout from the expense python script
void MainWindow::expenseOut(){
    QString newData = expenseProcess->readAllStandardOutput();
    //qDebug() << newData;
    if(expenseCommView){
        ui->teView->setText(newData);
        expenseCommView = false;
    }
}

//Triggered to view all the expenses for a person
void MainWindow::on_btnView_clicked(){
    QStringList args;
    args << "python/expense.py" << "view" << ui->comboViewExpense->currentText();
    expenseCommView = true;
    expenseProcess->start("python", args);
    expenseProcess->waitForFinished();
}
