#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "database.h"
#include "databaseexception.h"
#include "admindialog.h"
#include "servernetwork.h"
#include "serverthread.h"
//static std::mutex mt4;
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
    void on_admin_btn_clicked();

    void check_connections();

    void on_cancel_btn_clicked();

    void on_accept_btn_clicked();

    void on_start_btn_clicked();

private:
    Ui::MainWindow *ui;
    DataBase* db;
    AdminDialog *admin;
    ServerNetwork* server;
    QString connected;
    QString prev;
    QTimer *tr_timer;
    ServerThread* tr1;
    ServerThread* tr2;
};

#endif // MAINWINDOW_H
