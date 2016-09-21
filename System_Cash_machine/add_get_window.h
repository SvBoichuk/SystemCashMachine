#ifndef ADD_GET_WINDOW_H
#define ADD_GET_WINDOW_H

#include <QDialog>
#include <QDebug>
#include "clientnetwork.h"

namespace Ui {
class Add_Get_Window;
}

class Add_Get_Window : public QDialog
{
    Q_OBJECT

public:
    explicit Add_Get_Window(ClientNetwork *n,int type,QWidget *parent = 0);
    ~Add_Get_Window();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_btn_100_clicked();

    void on_btn_200_clicked();

    void on_btn_500_clicked();

    void on_btn_1000_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::Add_Get_Window *ui;
    ClientNetwork* net;
};

#endif // ADD_GET_WINDOW_H
