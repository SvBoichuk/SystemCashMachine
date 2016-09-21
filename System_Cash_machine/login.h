#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "clientnetwork.h"
#include "mainmenu.h"
#include "clientnetwork.h"

namespace Ui {
class LogIn;
}

class LogIn : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = 0);
    ~LogIn();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_exit_btn_clicked();

    void on_enter_btn_clicked();

private:
    Ui::LogIn *ui;
    //MainMenu *menu;
    ClientNetwork *client;
};

#endif // LOGIN_H
