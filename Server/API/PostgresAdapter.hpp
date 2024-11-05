#pragma once

#include <sql.h>
#include <pqxx/pqxx>
#include <memory>
#include <queue>
#include <chrono>
#include <mutex>
#include <thread>

class Session;
class thread;
using t_pSession = std::shared_ptr<Session>;

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

bool create_user(std::string username, std::string password_hash);
//TODO: bool delete_user
std::string get_hash_by_username(std::string username);

void start_session_handler();
void m_session_handler();
void handle(t_pSession);

PostgresAdapter(std::string db_connection_arguments);

~PostgresAdapter() = default;



private:
    std::queue<t_pSession> m_sessions;
    bool m_session_handle = false;
    t_pDataBaseConnection database_connection;
    std::thread my_threads[1];
    std::mutex m_mutex;
};

using t_pPostgresAdapter = std::shared_ptr<PostgresAdapter>;


