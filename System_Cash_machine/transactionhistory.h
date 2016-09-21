#ifndef TRANSACTIONHISTORY_H
#define TRANSACTIONHISTORY_H

#include <QDialog>

namespace Ui {
class TransactionHistory;
}

class TransactionHistory : public QDialog
{
    Q_OBJECT

public:
    explicit TransactionHistory(QWidget *parent = 0);
    ~TransactionHistory();

private:
    Ui::TransactionHistory *ui;
    static int count;
};

#endif // TRANSACTIONHISTORY_H
