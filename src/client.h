#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory>

class ImpClient {
public:
    ImpClient();
    ~ImpClient();

    void sendTcp(int sck, const char* buf);
    void sendUdp(int sck, const char* buf, std::string ip, int port);
    void recvTcp(int sck, char* buf, int len);
    void recvUdp(int sck, char* buf, int len);
};

/**********************************************************************/

class Client{
public:
    Client(std::string ip, int port) : _ip{ip}, _port{port} {};
    virtual ~Client() {};

    virtual void send(const char* buf) = 0;
    virtual void recv(char* buf, int len) = 0;

protected:
    ImpClient* _imp = nullptr;
    int _sck = -1;
    std::string _ip;
    int _port; 
};

/**********************************************************************/

class TCPClient : public Client {
public:
    TCPClient(std::string ip, int port);
    ~TCPClient();

    void send(const char* buf) override final;
    void recv(char* buf, int len) override final;
};

/**********************************************************************/

class UDPClient : public Client {
public:
    UDPClient(std::string ip, int port );
    ~UDPClient();

    void send(const char* buf) override final;
    void recv(char* buf, int len) override final;
};