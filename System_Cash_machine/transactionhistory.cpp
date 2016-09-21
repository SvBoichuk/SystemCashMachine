#include "transactionhistory.h"
#include "ui_transactionhistory.h"

TransactionHistory::TransactionHistory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransactionHistory)
{
    ui->setupUi(this);
    this->setWindowTitle("Transactions history");
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "№" << "Date" << "Type transaction" << "Sum" << "Current balance" );
}

TransactionHistory::~TransactionHistory()
{
    delete ui;
}
