#include "clientnetwork.h"

bool ClientNetwork::InitLib()
{
    if (WSAStartup(MAKEWORD(2,2), &wsa) < 0)
    {
        //throw NETException{"Failed to load WSA library"};
        return false;
    }
    return true;
}

bool ClientNetwork::CreateSock()
{
    data.sin_family = AF_INET;
    data.sin_port = htons(6881);
    //data.sin_addr.s_addr = inet_addr("127.0.0.1");
    data.sin_addr.s_addr = inet_addr("188.163.75.14");

    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        //throw NETException{"Failed to create socket"};
        return false;
    }
    return true;
}

bool ClientNetwork::Connect_to_server()
{
    if (connect(sock, (struct sockaddr*)&data, sizeof(data)) < 0)
    {
        //throw NETException{"Failed to connect to server"};
        return false;
    }
    return true;
}

ClientNetwork::ClientNetwork()
{
    sock = 0;
    memset(&data, 0, sizeof(data));
    memset(&wsa, 0, sizeof(wsa));
}

bool ClientNetwork::Send(const char *msg)
{
    if (msg == NULL)
    {
        //throw  NETException{"Bad data"};
        return false;
    }
    int data_length = strlen(msg);
    if (send(sock, msg, data_length, NULL) < 0)
    {
         //throw NETException{"Failed to send data to server"};
        return false;
    }
    return true;
}

bool ClientNetwork::Recv(char *buff)
{
    while (true)
    {
         if (recv(sock, buff, 14, NULL) < 0)
         {
            //throw NETException{"Failed to receive data from the server"};
            return false;
         }
         return true;
    }
}

void ClientNetwork::StartClient()
{
    if (!InitLib())
    {
            return;
    }
    if (!CreateSock())
    {
            return;
    }
}

void ClientNetwork::Connect()
{
    if (!Connect_to_server())
    {
            return;
    }
}

ClientNetwork::~ClientNetwork()
{
    closesocket(sock);
    memset(&data, 0, sizeof(data));
    memset(&wsa, 0, sizeof(wsa));
    WSACleanup();
}
