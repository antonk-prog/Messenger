#if !defined(ENDPOINT_HPP)
#define ENDPOINT_HPP

#include <string>
#include <Json.hpp>
#include <Server.hpp>
#include <iostream>
#include <httpparser/request.h>
#include <httpparser/httprequestparser.h>
using t_pRequest = std::shared_ptr<httpparser::Request>;
using t_pResponse = std::shared_ptr<std::string>;

struct ServerData;
using t_pServerData = std::shared_ptr<ServerData>;

struct EndPointArgs
{
    t_pServerData serverData;
    t_pRequest request;
    t_pResponse response = std::make_shared<std::string>();
};

using t_pEndPointArgs = std::shared_ptr<EndPointArgs>;

class EndPoint
{
public:
    EndPoint(std::string uri, void (*f)(t_pEndPointArgs))
        : m_f(f)
    {
        m_uri = uri;
        m_size = m_uri.size();
    };

    inline bool operator==(std::string &str) const
    {
        return str.compare(0, m_size, m_uri) == 0;
    };

    void operator()(t_pEndPointArgs argv)
    {
        m_f(argv);
    };

private:
    std::string m_uri;
    size_t m_size;
    
    void (*m_f)(t_pEndPointArgs);

};

#endif