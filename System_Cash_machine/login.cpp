#include "login.h"
#include "ui_login.h"
#include "mainmenu.h"
#include <QMessageBox>
#include <QRegExp>
#include <QDebug>

LogIn::LogIn(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
    this->setFixedSize(300,200); //fixed size this form (300px,200px)

    //SetUp validator
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]{4}"),this));
    //SetUp echo-mode to line_edit
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    //button "Enter" is not enabled
    ui->enter_btn->setEnabled(false);
    client = new ClientNetwork;
    client->StartClient();
}

LogIn::~LogIn()
{
    delete ui;
}

//until the user enters the password,
//button "Enter" is not enabled
void LogIn::on_lineEdit_textChanged(const QString &arg1)
{
    if(ui->lineEdit->text().length() != 4)
        ui->enter_btn->setEnabled(false);
    else ui->enter_btn->setEnabled(true);
}

//close window
void LogIn::on_exit_btn_clicked()
{
    this->close();
}

void LogIn::on_enter_btn_clicked()
{
    QString password = ui->lineEdit->text();
    char buff[14];
    memset(buff,0,14);
    client->Connect();
    if(password.isEmpty())
    {
        QMessageBox::warning(this,"Warning!","Pleas, enter you password!");
        return;
    }
    else {
        QString query_ToServer = "login " + password;
        client->Send(query_ToServer.toStdString().c_str());
        client->Recv(buff);
        qDebug() << buff;
    }

    if(strcmp(buff,"LoginSuccess") == 0)
    {
        MainMenu menu(client,this);
        //menu.setModal(true);
        this->hide();
        menu.exec();
        ui->lineEdit->clear();
        this->show();
    }

}
