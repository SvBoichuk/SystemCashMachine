#include "serverthread.h"

ServerThread::ServerThread(ServerNetwork *ntw, DataBase *db)
{
    server = ntw;
    database = db;
}

void ServerThread::UpDateConnected(QString &name)
{
    con_name = &name;
}

void ServerThread::run()
{
    switch(op)
    {
    case 1:
        newConnection(); break;
    case 2:
        WorkWithClient(); break;
    }
}

void ServerThread::SetOp(int operation)
{
    op = operation;
}

char* ServerThread::requestType(char *s)
{
    qDebug() << s ;
    //req = strtok(s," ");
    char* tmp = strtok(s," ");
    if(s != NULL)
        password = strtok(NULL," ");
    return tmp;

}

void ServerThread::Disconnect()
{
    server->Disconnect();
}

void ServerThread::newConnection()
{
    //static int i = 0;
    while(true){
       QString tmp = QString::fromStdString(server->StartAcception());
       mt4.lock();
      *con_name = tmp;
       mt4.unlock();
       msleep(100);
      {
        go = true;
        copy_net = *server;
        var1.notify_one();
      }
    }
}

void ServerThread::WorkWithClient()
{
    std::unique_lock<std::mutex> lock1(mt3);
    var1.wait(lock1);
    lock1.unlock();

    bool stop = false;
    char request[100];
    memset(request,0,100);

    while(!stop)
    {
        memset(request,0,100);
        try{
            server->recv_from_client(request);
        }catch(NetWorkExceptions ex)
        {
            return;
        }
        req = requestType(request);

        if(strcmp(req,"login") == 0)
        {
            LogIn(password);
        }
        else if(strcmp(req,"GET") == 0)
        {
            GetMoney(password);
        }
        else if(strcmp(req,"ADD") == 0)
        {
            AddMoney(password);
        }
        else if(strcmp(req,"BALANCE") == 0)
        {
            GetBalance();
        }
        else if(strcmp(req,"Transact") == 0)
        {
            History();
        }
        else if(strcmp(req,"Disconnect") == 0)
        {
            Disconnect();
        }
        else {
            server->sendToClient("BadRequest");
        }
    }
    memset(request,0,100);
}

void ServerThread::LogIn(char* pass)
{
    if( database->isUser(QString::fromStdString(pass)) )
    {
      server->sendToClient("LoginSuccess");
      database->GetUserData();
    }
    else server->sendToClient("LoginFaild");
}

void ServerThread::GetMoney(char *number)
{
    int num = atoi(number);
    if( database->GetMoney(num) )
    {
        server->sendToClient("GetMoneyOK");
    }
    else server->sendToClient("GetMoneyFail");
}

void ServerThread::GetBalance()
{
    QString b = database->CheckBalance();
    server->sendToClient(b.toStdString().c_str());
}

void ServerThread::AddMoney(char *number)
{
    int num = atoi(number);
    if( database->AddMoney(num) )
    {
        server->sendToClient("AddMoneyOK");
    }
    else server->sendToClient("AddMoneyFail");
}

void ServerThread::History()
{
    database->GetTransactionHistory(&trs);
    /*Send to client*/
    QString str_d;
    for(unsigned int i = 0; i < trs.size(); i++)
    {
        str_d += QString::number(trs[i].ID) + " ";
        str_d += QString::number(trs[i].numb) + " ";
        str_d += trs[i].DataTime + " ";
        str_d += trs[i].Balance + "|";
    }
    if(str_d.isEmpty())
    {
        str_d = "Empty";
    }
    server->sendToClient(str_d.toStdString().c_str());
    str_d.clear();
    memset(&trs,0,sizeof(trs));
}
