#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H
#include <winsock2.h>
#include <string.h>

#pragma comment (lib, "ws2_32.lib")


class ClientNetwork
{
private:
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in data;
    bool InitLib();
    bool CreateSock();
    bool Connect_to_server();
public:
    ClientNetwork();
    bool Send(const char* msg);
    bool Recv(char* buff);
    void StartClient();
    void Connect();
    ~ClientNetwork();
};

#endif // CLIENTNETWORK_H
