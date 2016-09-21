#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include "clientnetwork.h"
#include "add_get_window.h"
#include "check_balance.h"
#include "transactionhistory.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenu(ClientNetwork* n, QWidget *parent = 0);
    ~MainMenu();

private slots:
    void on_LogOut_btn_clicked();

    void on_add_btn_clicked();

    void on_get_btn_clicked();

    void on_chaeck_btn_clicked();

    void on_transaction_clicked();

private:
    ClientNetwork* net;
    Ui::MainMenu *ui;
    Add_Get_Window *obj;
    Check_balance *obj_c;
    TransactionHistory *obj_t;
};

#endif // MAINMENU_H
