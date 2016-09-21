#ifndef SERVERNETWORK_H
#define SERVERNETWORK_H
#include <iostream>
#include <QString>
#include <winsock2.h>
#include <exception>

class NetWorkExceptions : public std::exception{
  QString error;
public:
    NetWorkExceptions(const QString &err);
    QString what();
    ~NetWorkExceptions();
};

class ServerNetwork
{
private:
    WSADATA wsa;
    SOCKET client_sock, server_sock;
    struct sockaddr_in client_data, server_data;
    int client_data_size;
    bool InitLib();
    bool CreateSock();
    bool Bind();
    //bool AcceptConnection();
public:
    void Disconnect();
    void Copy(ServerNetwork &);
    ServerNetwork();
    std::string StartAcception();
    void StartServer();
    bool sendToClient(const char* msg);
    bool recv_from_client(char* msg);
    QString CurrentIP();
    ~ServerNetwork();
    bool AcceptConnection();
};

#endif // SERVERNETWORK_H
