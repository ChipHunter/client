#include "client.h"

void ImpClient::sendTcp(int sck, const char* buf) {
    
    int len = strlen(buf);
    int numBytes = 0;

    numBytes = write(sck, buf, len);
    if(numBytes != len) {
        std::cout << "problems writing to buffer!" << std::endl;
    }

}

void ImpClient::recvTcp(int sck, char* buf, int len) {

    int n = 0;
    while( (n = read(sck, buf, len - 1)) > 0) {
        std::cout << buf << std::endl;
    }

    if(n == -1) {
        std::cout << "error in receive:" << strerror(errno) << std::endl;
    }

}

void ImpClient::sendUdp(int sck, const char* buf, std::string ip, int port) {

    int len = strlen(buf);
    int numBytes = 0;
    struct sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    if(inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr) == -1)
        throw std::system_error(errno, std::generic_category());

    numBytes = sendto(sck, buf, len, 0, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if(numBytes != len) {
        std::cout << "problems writing to buffer!" << std::endl;
    }

}

void ImpClient::recvUdp(int sck, char* buf, int len) {

    if(recvfrom(sck, buf, len, 0, NULL, 0) == -1)
        std::cout << "problems recieving!" << std::endl;

}

/**********************************************************************/

TCPClient::TCPClient(std::string ip, int port) : Client(ip, port) {

    struct sockaddr_in serverAddr;

    if((_sck = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cout<< "Error creating the socket!: " << strerror(errno) << std::endl;
        throw std::system_error(errno, std::generic_category());
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(_port);
    if(inet_pton(AF_INET, _ip.c_str(), &serverAddr.sin_addr) == -1){
        std::cout << "error in inet_pton:" << strerror(errno) << std::endl;
        throw std::system_error(errno, std::generic_category());
    }

    if(::connect(_sck, (sockaddr*) &serverAddr, sizeof(serverAddr)) == -1) {
        std::cout << "error in connect:" << strerror(errno) << std::endl;
        throw std::system_error(errno, std::generic_category());
    }

}

void TCPClient::send(const char* buf) {

    _imp->sendTcp(_sck, buf);

}

void TCPClient::recv(char* buf, int len) {

    _imp->recvTcp(_sck, buf, len);

}

TCPClient::~TCPClient() {

    if(close(_sck) == -1)
        std::cout<< "Error closing the socket!: " << strerror(errno) << std::endl;

}

/**********************************************************************/

UDPClient::UDPClient(std::string ip, int port) : Client(ip, port) {

    if((_sck = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        std::cout<< "Error creating the socket!: " << strerror(errno) << std::endl;
        throw std::system_error(errno, std::generic_category());
    }

}

UDPClient::~UDPClient() {

    if(close(_sck) == -1)
        std::cout<< "Error closing the socket!: " << strerror(errno) << std::endl;

}

void UDPClient::send(const char* buf) {

    _imp->sendUdp(_sck, buf, _ip, _port);

}

void UDPClient::recv(char* buf, int len) {

    _imp->recvUdp(_sck, buf, len);

}