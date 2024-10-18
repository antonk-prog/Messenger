#include <AuthSessionBase.hpp>

static const char ALFAVITE[] = 
    "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789"; // len 63

AuthSessionBase::AuthSessionBase(char* name, char* pass, u_long inv)
    : id(inv)
{
    unsigned char _temp[MD5_DIGEST_LENGTH];
    char c_hash[MD5_DIGEST_LENGTH * 2];
    std::string hash;
    std::time_t t1 = std::time(nullptr);

    hash.append(name);
    hash.append(pass);
    hash.append(std::to_string(t1));

    MD5((unsigned char *)hash.c_str(), hash.size(), _temp);
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)             //?????
    {
        c_hash[i * 2] = ALFAVITE[_temp[i] % 62];             //?????
        c_hash[i * 2 + 1] = ALFAVITE[_temp[i] / 62];             //?????
    }
    m_hash = std::string(c_hash, MD5_DIGEST_LENGTH * 2);             //?????
}