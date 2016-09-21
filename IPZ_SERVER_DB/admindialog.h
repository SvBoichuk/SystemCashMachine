#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include "database.h"

namespace Ui {
class AdminDialog;
}

class AdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog(DataBase &db,QWidget *parent = 0);
    ~AdminDialog();

private slots:
    void on_add_user_clicked();

    void on_delete_btn_clicked();

    void on_pushButton_clicked();

    void on_refresh_btn_clicked();

private:
    Ui::AdminDialog *ui;
    DataBase database;
    QSqlTableModel *users_model;
    QSqlTableModel *transactions_model;
};

#endif // ADMINDIALOG_H
