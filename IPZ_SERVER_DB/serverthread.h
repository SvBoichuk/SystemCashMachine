#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H
#include "database.h"
#include "servernetwork.h"
#include "samelib.h"
#include <string.h>

static bool go = false;
static QString RecvD;
static ServerNetwork copy_net;

class ServerThread : public QThread
{
public:
    ServerThread(ServerNetwork *ntw, DataBase *db);
    void UpDateConnected(QString &);
    void run();
    void SetOp(int);
private:
    ServerNetwork *server;
    DataBase *database;
    int op;
    int value_num;
    char* req;
    char* password;
    QString* con_name;

    std::vector<TransactionInfo> trs;

    char* requestType(char* s);
    // QThread interface
protected:
    void Disconnect();
    void newConnection();
    void WorkWithClient();
    void LogIn(char *pass);
    void GetMoney(char *number);
    void GetBalance();
    void AddMoney(char *number);
    void History();
};

#endif // SERVERTHREAD_H
