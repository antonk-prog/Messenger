#include <Server.hpp>
#include <algorithm>
#include <iostream>
#include <memory>

#define DB_CONNECTION_ARGUMENTS "user = anton password = 105605 hostaddr = 127.0.0.1 port = 5432 dbname = messenger_db"

void add_all_endpoints(Server & server);
int main() {
    try{
        t_pServerData serverData = std::make_shared<ServerData>();
        serverData->authCollector = std::make_shared<AuthCollectorBase>();
        serverData->postgres_adapter = std::make_shared<PostgresAdapter>(DB_CONNECTION_ARGUMENTS);

        
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

