#include "servernetwork.h"
#include <string.h>

bool ServerNetwork::InitLib()
{
    if (WSAStartup(MAKEWORD(2,2), &wsa) < 0){
            return false;
        }
    return true;
}

bool ServerNetwork::CreateSock()
{
    server_data.sin_addr.s_addr = INADDR_ANY;//inet_addr("");//inet_addr(IP_ADDRESS);
    server_data.sin_family = AF_INET;
    server_data.sin_port = htons(6881);

    if ((server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        return false;
    }
    return true;
}

bool ServerNetwork::Bind()
{
    if (bind(server_sock, (struct sockaddr*)&server_data, sizeof(server_data)) < 0){
            return false;
        }
        if (listen(server_sock, SOMAXCONN) < 0){
            return false;
        }
        return true;
}

void ServerNetwork::Disconnect()
{
    //closesocket(client_sock);
    //memset(&client_data,0,sizeof(client_data));
    shutdown(client_sock,SD_BOTH);
}

void ServerNetwork::Copy(ServerNetwork &c)
{
    *this = c;
}

bool ServerNetwork::AcceptConnection()
{
    if ((client_sock = accept(server_sock, (struct sockaddr*)&client_data, &client_data_size)) < 0)
    {
        throw NetWorkExceptions{"Failed to accept incomming connection...."};
        return false;
    }
    return true;
}

ServerNetwork::ServerNetwork()
{
    server_sock = 0;
    client_sock = 0;
    client_data_size = sizeof(client_data);
    memset(&server_data, 0, sizeof(server_data));
    memset(&client_data, 0, sizeof(client_data));
    memset(&wsa, 0, sizeof(wsa));
}

std::string ServerNetwork::StartAcception()
{
    if(!AcceptConnection()){
       closesocket(server_sock);
       throw NetWorkExceptions{"Failed to Accept a server, try again later..."};
   }
    return CurrentIP().toStdString();
}

void ServerNetwork::StartServer()
{
    if (!InitLib())
    {
           throw NetWorkExceptions{"Failed to load winsock library, closing program..."};
        return;
        }
        if (!CreateSock()){
            throw NetWorkExceptions{"Failed to create socket, closing program..."};
            return;
        }
        if (!Bind()){
            closesocket(server_sock);
           throw NetWorkExceptions{"Failed to Create a server, try again later..." };
    }
}

bool ServerNetwork::sendToClient(const char *msg)
{
    if (msg == NULL)
    {
        throw NetWorkExceptions{"Bad data passed to send...."};
        return false;
    }
    if (send(client_sock, msg, strlen(msg), NULL) < 0)
    {
        throw NetWorkExceptions{"Failed to send data to client...."};
        return false;
    }
    return true;
}

bool ServerNetwork::recv_from_client(char *msg)
{
    memset(msg,0,strlen(msg));
    while (true)
    {
        if (recv(client_sock, msg, 100, NULL) < 0){
            throw NetWorkExceptions{"Failed to receive data from client...."};
        }
        return true;
    }
}

QString ServerNetwork::CurrentIP()
{
    return QString::fromStdString(std::string{inet_ntoa(client_data.sin_addr)});
}

ServerNetwork::~ServerNetwork()
{
    closesocket(server_sock);
    memset(&server_data, 0, sizeof(server_data));
    memset(&wsa, 0, sizeof(wsa));
    WSACleanup();
}

NetWorkExceptions::NetWorkExceptions(const QString &err)
{
    error = err;
}

QString NetWorkExceptions::what()
{
    return error;
}

NetWorkExceptions::~NetWorkExceptions()
{

}
