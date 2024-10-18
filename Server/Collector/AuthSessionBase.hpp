#if ! defined(AUTH_SESSION_BASE_HPP)
#define AUTH_SESSION_BASE_HPP

#include <string>
#include <ctime>
#include <openssl/md5.h>

class AuthSessionBase
{
public:
    AuthSessionBase() = default;
    AuthSessionBase(char* name, char* pass, u_long inv);

    std::string getHash(){return m_hash;};
    unsigned long getId(){return id;};

private:
    std::string m_hash;
    
    unsigned long id;

};

#endif