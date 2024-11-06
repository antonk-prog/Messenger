#include <PostgresAdapter.hpp>
#include <iostream>
PostgresAdapter::PostgresAdapter(std::string db_connection_arguments){
    try{
        database_connection = std::make_shared<pqxx::connection>(db_connection_arguments);
    }
    catch (std::exception const &e) {
        std::cerr << "error in PostgresAdapter constructor" << std::endl;
        std::cerr << e.what() << std::endl;
    }
}

t_pDataBaseConnection PostgresAdapter::getPostgresConnection()
{
    return database_connection;
}
