#include <Server.hpp>
#include <algorithm>
#include <iostream>
#include <memory>

#define DB_CONNECTION_ARGUMENTS "user = anton password = 105605 hostaddr = 127.0.0.1 port = 5432 dbname = test"

void add_all_endpoints(Server & server);
int main() {
    try{
        t_pServerData serverData = std::make_shared<ServerData>();
        t_pAccountsCollector accounts_collector = std::make_shared<DataBaseAccounts>();
        serverData->authCollector = std::make_shared<AuthCollectorBase>(accounts_collector);
        serverData->my_db = std::make_shared<pqxx::connection>(DB_CONNECTION_ARGUMENTS);
        Server server(serverData);
 
        add_all_endpoints(server);

        server.start_acceptor();
        server.start_session_handler();

        server.join();






    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }


    


    return 0;
}

