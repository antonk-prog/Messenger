#if ! defined(AUTH_HPP)
#define AUTH_HPP

#include <map>
#include <memory>
#include <AuthSessionBase.hpp>
#include <TempDataBase.hpp>
using t_AuthSessionCollection = std::map<std::string, AuthSessionBase>;

class AuthCollectorBase
{
public:
    AuthCollectorBase(t_pAccountsCollector accounts_collector);
    ~AuthCollectorBase() = default;

    virtual std::string login(char* username, char* pass); // AuthSessionBase пытается создать объект, если получается добавляет его в активные сессии
    virtual bool registrate(char* username, char* pass);
    unsigned long getIdByHash(std::string& hash);

private:
// кто-то должен следить за временем жизни этих сессий
// Коллизии маловероятны, но лучше учесть, что они могут совпадать( ну или пофик )
    t_AuthSessionCollection m_ses;
    unsigned long getIdByUsername(char*);
    bool checkUserExists(char* usr, char* pass);
    t_pAccountsCollector accounts_collector;

};

using t_pAuthCollectorBase = std::shared_ptr<AuthCollectorBase>;

#endif