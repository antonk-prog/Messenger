#pragma once

#include <sql.h>
#include <pqxx/pqxx>
#include <memory>
#include <queue>
#include <chrono>
#include <thread>
#include <mutex>

class thread;

using t_pDataBaseConnection = std::shared_ptr<pqxx::connection>;

/**
 * Class used for manipulating with Postgres database.
 * It collects pqxx:connection
 */
class PostgresAdapter {
public:
/**
 * Create PostgresAdapter.
 * @param string String that needs to make a connection with 
 * postgresql, like: user = <user> password = <password> hostaddr = ...
 */


PostgresAdapter(std::string db_connection_arguments);

t_pDataBaseConnection getPostgresConnection();

~PostgresAdapter() = default;


private:
    t_pDataBaseConnection database_connection;
};

using t_pPostgresAdapter = std::shared_ptr<PostgresAdapter>;


