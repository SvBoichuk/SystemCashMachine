#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(700,450);
    ui->groupBox_2->hide();

    db = new DataBase();
    try{
        db->Initialize("QMYSQL","ipz_database","localhost","root","pass1234");
    }catch(DataBaseException ex)
    {
        QMessageBox::critical(this,"Error",ex.what());
        ui->listWidget->addItem("Can't connect to data base!");
        ui->admin_btn->setEnabled(false);
    }
    tr_timer = new QTimer;
    connect(tr_timer,SIGNAL(timeout()),this,SLOT(check_connections()));
}

MainWindow::~MainWindow()
{
    delete ui;

    if(tr1){
        tr1->terminate();
    }
    if(tr2){
        tr2->terminate();
    }
    tr_timer->stop();
}

void MainWindow::on_admin_btn_clicked()
{
    ui->groupBox_2->show();
}

void MainWindow::check_connections()
{
    mt4.lock();
    if(!connected.isEmpty())
    {
        tr2 = new ServerThread(server,db);
        tr2->SetOp(2);
        tr2->start();
        ui->listWidget->addItem("Connected new client");
        connected.clear();
    }
    mt4.unlock();
}

void MainWindow::on_cancel_btn_clicked()
{
    ui->groupBox_2->hide();
    ui->login_line->clear();
    ui->pass_line->clear();
}

void MainWindow::on_accept_btn_clicked()
{
    if(ui->pass_line->text() != "admin" || ui->login_line->text() != "admin")
    {
        QMessageBox::information(this,"Info","Enter login or password!");
        return;
    }
    admin = new AdminDialog(*db,this);
    admin->show();
}

void MainWindow::on_start_btn_clicked()
{
    server = new ServerNetwork();
    server->StartServer();
    ui->listWidget->addItem("Server started!");

    tr1 = new ServerThread(server,db);
    connected = prev;
    tr1->UpDateConnected(connected);
    tr1->SetOp(1);
    tr1->start();
    tr_timer->start(100);
    ui->start_btn->setEnabled(false);
}
