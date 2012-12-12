#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_btnAdd_clicked();
    void out();

private:
    Ui::MainWindow *ui;
     QProcess* roommateProcess ;
};

#endif // MAINWINDOW_H
