#ifndef CHECK_BALANCE_H
#define CHECK_BALANCE_H

#include <QDialog>

namespace Ui {
class Check_balance;
}

class Check_balance : public QDialog
{
    Q_OBJECT

public:
    explicit Check_balance(QWidget *parent = 0);
    ~Check_balance();

private:
    Ui::Check_balance *ui;
};

#endif // CHECK_BALANCE_H
