#include "client.h"
#include <memory>

int main() {

    const char* msg{"Hallo World!"};

    int len = 64;
    char buf[len] = {0};

    try {

        std::unique_ptr<Client> cli{new TCPClient("127.0.0.1", 18000)};

        cli->send(msg);

        cli->recv(buf, len);

        std::cout << "the msg is: " << buf << std::endl;

    } catch (const std::system_error& e) {

        std::cout << "System Error! " << e.what() << std::endl;

    } catch (...) {

        std::cout << "other Error!" << std::endl;

    }

    return 0;

}
