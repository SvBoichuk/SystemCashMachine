#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "add_get_window.h"
#include "check_balance.h"

#define ADD 1
#define GET 2

MainMenu::MainMenu(ClientNetwork *n, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    this->setWindowTitle("Main menu");
    this->setFixedSize(410,330);
    net = n;
}

MainMenu::~MainMenu()
{
    delete ui;
}

//close this window
void MainMenu::on_LogOut_btn_clicked()
{
    this->close();
}

void MainMenu::on_add_btn_clicked()
{
    obj = new Add_Get_Window(net,ADD,this);
    this->hide();
    if(obj->exec())
    this->show();
}

void MainMenu::on_get_btn_clicked()
{
    obj = new Add_Get_Window(net,GET,this);
    this->hide();
    obj->exec();
    this->show();
}

void MainMenu::on_chaeck_btn_clicked()
{
    this->hide();
    obj_c = new Check_balance(this);
    obj_c->exec();
    this->show();
}

void MainMenu::on_transaction_clicked()
{
    obj_t = new TransactionHistory(this);
    this->hide();
    obj_t->exec();
    this->show();
}
