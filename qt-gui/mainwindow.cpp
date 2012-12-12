#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAdd_clicked()
{
    pid_t roommatePID;
    int roommateFD[2];
    if(pipe(roommateFD)){
        qDebug() << "problem";
    }
    char* buff = {NULL};
    roommatePID = fork();
    qDebug() << "hello";
    if(!roommatePID){
        dup2(roommateFD[1], STDOUT_FILENO);
        execl("/python/roommates.py", buff, NULL);

    }
    qDebug() << "fag";
    char line[100];
    read(roommateFD[0], line, 100);
    //qDebug() << line;
}
