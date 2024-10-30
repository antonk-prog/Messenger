#if !defined(POSTGRES_ADAPTER_HPP)
#define POSTGRES_ADAPTER_HPP

#include <sql.h>
#include <pqxx/pqxx>
#include <memory>

using t_pDataBaseConnection = std::shared_ptr<pqxx::connection>;
using sql::InsertModel; 
using sql::DeleteModel;
using sql::SelectModel;
using sql::UpdateModel;

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


PostgresAdapter(std::string db_connection_arguments);

~PostgresAdapter() = default;



private:
    t_pDataBaseConnection database_connection;
    InsertModel insert_model;
    DeleteModel delete_model;
    SelectModel select_model;
    UpdateModel update_model;
};




#endif
