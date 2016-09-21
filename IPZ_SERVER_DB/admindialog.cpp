#include "admindialog.h"
#include "ui_admindialog.h"
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QRegExp>
#include <QMessageBox>
#include <QTableView>
#include <QModelIndexList>

AdminDialog::AdminDialog(DataBase &db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Admin");
    database = db;
    users_model         = new QSqlTableModel(this,database.getDataBase());
    transactions_model  = new QSqlTableModel(this,database.getDataBase());

    users_model->setTable("Users");
    transactions_model->setTable("Transactions");
    users_model->select();
    transactions_model->select();

    ui->users_table->setModel(users_model);
    ui->transactions_table->setModel(transactions_model);
    ui->pushButton->setEnabled(false);
}

AdminDialog::~AdminDialog()
{
    delete ui;
}

void AdminDialog::on_add_user_clicked()
{
    users_model->insertRow(users_model->rowCount());
    ui->pushButton->setEnabled(true);
}

void AdminDialog::on_delete_btn_clicked()
{
    int selected_Row = ui->users_table->currentIndex().row();
    if(selected_Row >= 0)
    {
        QSqlQueryModel query_model;
        query_model.setQuery("SELECT * FROM Users");
        QString user_id = query_model.record(selected_Row).value("id").toString();
        QSqlQuery *query = new QSqlQuery(database.getDataBase());

        users_model->removeRow(selected_Row);

        if(query->exec("DELETE FROM Transactions WHERE id='" + user_id + "'"))
        {
            QMessageBox::information(this,"Info","Row is delete!");
            users_model->select();
        }
        else qDebug() << query->lastError().text();
    }
    else QMessageBox::information(this,"Info","No selected row!!");
}

void AdminDialog::on_pushButton_clicked()
{
    QSqlRecord rec = users_model->record(users_model->rowCount()-1);
    // 7 - count data in one record
    for(int i = 0; i < 7; i++)
    {
        if(rec.value(i).toString().isEmpty())
        {
            QMessageBox::warning(this,"Warning","Insert all data!");
            return;
        }
    }
    users_model->submitAll();
    ui->pushButton->setEnabled(false);
}

void AdminDialog::on_refresh_btn_clicked()
{
    users_model->select();
    transactions_model->select();
}
