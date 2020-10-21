#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory>

class ImpClient {
public:
    /* TCP related implementation*/
    void setupTcp(std::string ip, int port);
    void sendTcp(const char* buf);
    void recvTcp(char* buf, int len);
    void closeTcp();

    /* UDP related implementation*/
    void sendUdp(const char* buf);
    void recvUdp(char* buf, int len);
    void setupUdp(std::string ip, int port);
    void closeUdp();

private:
    std::string _ip;
    int _sck;
    int _port; 
};

/**********************************************************************/

class Client{
public:
    virtual ~Client() {};

    virtual void send(const char* buf)    = 0;
    virtual void recv(char* buf, int len) = 0;

};

/**********************************************************************/

class TCPClient : public Client {
public:
    TCPClient(std::string ip, int port);
    ~TCPClient();

    void send(const char* buf)    override final;
    void recv(char* buf, int len) override final;

private:
    ImpClient _imp;
};

/**********************************************************************/

class UDPClient : public Client {
public:
    UDPClient(std::string ip, int port );
    ~UDPClient();

    void send(const char* buf)    override final;
    void recv(char* buf, int len) override final;

private:
    ImpClient _imp;
};