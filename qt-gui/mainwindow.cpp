#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QListWidgetItem>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    roommateProcess = new QProcess();
    connect( roommateProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(out()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAdd_clicked()
{
    QStringList args;
    args << "python/roommate.py" << "-a" << ui->leAdd->text();
    roommateProcess->start("python", args);

    QStandardItemModel *model = new QStandardItemModel();
    QStandardItem *Item = new QStandardItem();
    Item->setCheckable( true );
    Item->setCheckState( Qt::Checked );
    model->setItem( 0, Item );
    ui->listView->setModel( model );
}

void MainWindow::out(){
       ui->lineEdit->setText("In Out Function");
       QByteArray newData = roommateProcess->readAllStandardOutput();

       qDebug() <<newData.data();
}
