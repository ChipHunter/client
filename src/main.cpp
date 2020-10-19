#include "client.h"
#include <memory>

int main() { 

    const char* msg{"Hallo World!"};

    try {
    
        std::unique_ptr<Client> cli{new UDPClient("127.0.0.1", 18000)};

        cli->send(msg);
    
    } catch (const std::system_error& e) {

        std::cout << "System Error! " << e.what() << std::endl;

    } catch (...) {
        
        std::cout << "other Error!" << std::endl;
    
    } 

    return 0; 
    
}