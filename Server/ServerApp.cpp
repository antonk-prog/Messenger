#include <Server.hpp>
#include <algorithm>
#include <iostream>
#include <memory>

void add_all_endpoints(Server & server);

int main() {
    t_pServerData serverData = std::make_shared<ServerData>();
    serverData->authCollector = std::make_shared<AuthCollectorBase>();
    

    Server server(serverData);

    

    add_all_endpoints(server);

    server.start_acceptor();
    server.start_session_handler();

    server.join();


    return 0;
}