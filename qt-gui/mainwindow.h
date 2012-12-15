#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QListWidget>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum RoommateCommand{ADD, REMOVE, ALL};
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_btnAdd_clicked();
    void roommateOut();
    void expenseOut();
    void on_btnRemove_clicked();

    void on_btnAddExpense_clicked();

    void on_btnView_clicked();

private:
    Ui::MainWindow *ui;
    QProcess* roommateProcess;
    QProcess* expenseProcess;
    RoommateCommand roommateComm;
    bool expenseCommView;
    void refreshUI();
    QStringList roommates;
    QListWidgetItem** removeList;
    QListWidgetItem** expenseList;
    QMessageBox msgBox;
};

#endif // MAINWINDOW_H
