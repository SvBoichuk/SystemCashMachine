#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <vector>
#include <QString>
#include <QDateTime>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "databaseexception.h"

struct TransactionInfo{
    int ID;
    int numb;
    QString DataTime;
    QString Balance;
};

class DataBase
{
private:
    QSqlDatabase db;
    QSqlQuery* query;
    QString request;

    struct UserData
    {
        int ID;
        int password;
        QString user_name;
        int ballance;
        QString e_mail;
        QString phone;
        QString card_number;
    };

    TransactionInfo info;
    UserData data;
    QString balance;
public:
    explicit DataBase();
    bool isUser(const QString& req);
    void GetUserData();
    bool AddMoney(int sum);
    bool GetMoney(int sum);
    bool GetTransactionHistory(std::vector<TransactionInfo> *t);
    bool Initialize(const QString& driver, const QString& db_name, const QString &l_host, const QString &userName, const QString &pass);
    QString CheckBalance();
    QSqlDatabase& getDataBase();
};

#endif // DATABASE_H
