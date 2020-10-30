#include "client.h"

void ImpClient::setupTcp(std::string ip, int port) {

    _ip = ip;
    _port = port;

    struct sockaddr_in serverAddr;

    if((_sck = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cout<< "Error creating the socket!: " << strerror(errno) << std::endl;
        throw std::system_error(errno, std::generic_category());
    }

    try {
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(_port);
        if(inet_pton(AF_INET, _ip.c_str(), &serverAddr.sin_addr) == -1){
            std::cout << "error in inet_pton:" << strerror(errno) << std::endl;
            throw std::system_error(errno, std::generic_category());
        }

        if(connect(_sck, (sockaddr*) &serverAddr, sizeof(serverAddr)) == -1) {
            std::cout << "error in connect:" << strerror(errno) << std::endl;
            throw std::system_error(errno, std::generic_category());
        }
    } catch(const std::system_error& e) {

        if(close(_sck) == -1)
            std::cout<< "Error closing the socket!: " << strerror(errno) << std::endl;
        
        throw e;

    }

}

void ImpClient::sendTcp(const char* buf) {

    int len = strlen(buf);
    int numBytes = 0;

    numBytes = write(_sck, buf, len);
    if(numBytes != len) {
        std::cout << "problems writing to buffer!" << std::endl;
    }

}

void ImpClient::recvTcp(char* buf, int len) {

    int n = 0;
    while( (n = read(_sck, buf, len - 1)) > 0) {
        std::cout << buf << std::endl;
    }

    if(n == -1) {
        std::cout << "error in receive:" << strerror(errno) << std::endl;
    }

}

void ImpClient::closeTcp() {

    if(close(_sck) == -1)
        std::cout<< "Error closing the socket!: " << strerror(errno) << std::endl;

}

void ImpClient::setupUdp(std::string ip, int port) {

    _ip = ip;
    _port = port;

    if((_sck = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        std::cout<< "Error creating the socket!: " << strerror(errno) << std::endl;
        throw std::system_error(errno, std::generic_category());
    }

}

void ImpClient::sendUdp(const char* buf) {

    int len = strlen(buf);
    int numBytes = 0;
    struct sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(_port);
    if(inet_pton(AF_INET, _ip.c_str(), &serverAddr.sin_addr) == -1)
        throw std::system_error(errno, std::generic_category());

    numBytes = sendto(_sck, buf, len, 0, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if(numBytes != len) {
        std::cout << "problems writing to buffer!" << std::endl;
    }

}

void ImpClient::recvUdp(char* buf, int len) {

    if(recvfrom(_sck, buf, len, 0, NULL, 0) == -1)
        std::cout << "problems recieving!" << std::endl;

}

void ImpClient::closeUdp() {

    if(close(_sck) == -1)
        std::cout<< "Error closing the socket!: " << strerror(errno) << std::endl;

}

/**********************************************************************/

TCPClient::TCPClient(std::string ip, int port) {

    _imp.setupTcp(ip, port);

}

TCPClient::~TCPClient() {

    _imp.closeTcp();

}

void TCPClient::send(const char* buf) {

    _imp.sendTcp(buf);

}

void TCPClient::recv(char* buf, int len) {

    _imp.recvTcp(buf, len);

}

/**********************************************************************/

UDPClient::UDPClient(std::string ip, int port) {

    _imp.setupUdp(ip, port);

}

UDPClient::~UDPClient() {

    _imp.closeUdp();

}

void UDPClient::send(const char* buf) {

    _imp.sendUdp(buf);

}

void UDPClient::recv(char* buf, int len) {

    _imp.recvUdp(buf, len);

}
