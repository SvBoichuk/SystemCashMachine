
#include "database.h"
#include <QVariant>


DataBase::DataBase()
{
}

bool DataBase::isUser(const QString& req)
{
    if(query->exec("select * from Users where Password='" + req + "'"))
    {
        int cnt = 0;
        while(query->next())
        {
         cnt++;
        }
        if(cnt == 1)
        {
            request = req;
            GetUserData();
            return true;
        }
        else
        {
            request.clear();
            return false;
        }
    }
}

void DataBase::GetUserData()
{
    if(query->exec("select * from Users where Password='" + request + "'"))
    {
        while(query->next())
        {
         data.ID = query->value(0).toInt();
         data.user_name = query->value(1).toString();
         data.password = query->value(2).toInt();
         data.ballance = query->value(3).toInt();
         data.e_mail = query->value(4).toString();
         data.phone = query->value(5).toString();
         data.card_number = query->value(6).toString();
        }
    }
    std::cout << "User ID: " << data.ID << std::endl;
    std::cout << "User name: " << data.user_name.toStdString() << std::endl;
    std::cout << "Balance: " << data.ballance << std::endl;
}

bool DataBase::AddMoney(int sum)
{
    data.ballance += sum;
    std::cout << "sum: " << data.ballance << std::endl;
    if(query->exec("UPDATE Users SET Balance='" + QString::number(data.ballance) + "' WHERE id='" + QString::number(data.ID) + "'"))
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        info.ID = data.ID;
        info.DataTime = QDateTime::currentDateTime().toString();
        info.numb = qrand()%1000;
        info.Balance = '+';
        info.Balance += QString::number(sum);

        query->prepare("INSERT INTO Transactions (ID, numb, DataTime, balance)"
                     "VALUES (?, ?, ?, ?)");
        query->addBindValue(info.ID);
        query->addBindValue(info.numb);
        query->addBindValue(info.DataTime);
        query->addBindValue(info.Balance);
        if(query->exec())
            std::cout << "Data Insert!" << std::endl;
        else std:: cout << query->lastError().text().toStdString() << std::endl;

        std::cout << "Update! AddMoney() is success!" << std::endl;
        return true;
    }
    else {
        std::cout << query->lastError().text().toStdString() << std::endl;
        return false;
    }
}

bool DataBase::GetMoney(int sum)
{
    if(sum > data.ballance)
    {
        std::cout << "Not enough momey!" << std::endl;
        return false;
    }

    data.ballance -= sum;
    if(query->exec("UPDATE Users SET Balance='" + QString::number(data.ballance) + "' WHERE id='" + QString::number(data.ID) + "'"))
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        info.ID = data.ID;
        info.DataTime = QDateTime::currentDateTime().toString();
        info.numb = qrand()%1000;
        info.Balance = '-';
        info.Balance += QString::number(sum);

        query->prepare("INSERT INTO Transactions (ID, numb, DataTime, balance)"
                     "VALUES (?, ?, ?, ?)");
        query->addBindValue(info.ID);
        query->addBindValue(info.numb);
        query->addBindValue(info.DataTime);
        query->addBindValue(info.Balance);
        if(query->exec())
            std::cout << "Data Insert!" << std::endl;
        else std:: cout << query->lastError().text().toStdString() << std::endl;

        std::cout << "Update! GetMoney() is success!" << std::endl;
        return true;
    }
    else {
        std::cout << query->lastError().text().toStdString() << std::endl;
        return false;
    }
}

bool DataBase::GetTransactionHistory(std::vector<TransactionInfo> *t)
{
    TransactionInfo tmp;
    if(query->exec("SELECT * FROM Transactions where ID='" + QString::number(data.ID) +"'"))
    {
        while(query->next())
        {
            tmp.ID = query->value(0).toInt();
            tmp.numb = query->value(1).toInt();
            tmp.DataTime = query->value(2).toString();
            tmp.Balance = query->value(3).toString();
            t->push_back(tmp);
        }
        return true;
    }
    else return false;
}

bool DataBase::Initialize(const QString &driver, const QString &db_name, const QString &l_host, const QString &userName, const QString &pass)
{
    db = QSqlDatabase::addDatabase(driver);
    db.setDatabaseName(db_name);
    db.setHostName(l_host);
    db.setUserName(userName);
    db.setPassword(pass);

    if(!db.open())
    {
        throw DataBaseException(db.lastError().text());
    }
    else std::cout << "DataBase is opened!" << std::endl;

    query = new QSqlQuery(db);
    return true;
}

QString DataBase::CheckBalance()
{
    QString str_data;
    str_data += data.user_name + " ";
    str_data += QString::number(data.ballance) + " ";
    str_data += QString::number(data.password) + " ";
    str_data += data.e_mail + " ";
    str_data += data.phone + " ";
    str_data += data.card_number;

    return str_data;
}

QSqlDatabase &DataBase::getDataBase()
{
    return db;
}
