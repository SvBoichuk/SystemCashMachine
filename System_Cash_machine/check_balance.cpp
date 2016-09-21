#include "check_balance.h"
#include "ui_check_balance.h"

Check_balance::Check_balance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Check_balance)
{
    ui->setupUi(this);

    //SetUp all line edits in ReadOnly mode
    ui->card_line->setReadOnly(true);
    ui->line_balane->setReadOnly(true);
    ui->line_mail->setReadOnly(true);
    ui->line_name->setReadOnly(true);
    ui->pass_line->setReadOnly(true);
    ui->phone_line->setReadOnly(true);
}

Check_balance::~Check_balance()
{
    delete ui;
}
