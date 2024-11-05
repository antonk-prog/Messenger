#pragma once

#include <chrono>
#include <queue>
#include <thread>
#include <mutex>
#include <memory>
#include <iostream> 
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <Session.hpp>
#include <AuthCollectorBase.hpp>
#include <PostgresAdapter.hpp>
#define SERVER_PORT 8484
#define THREAD_HANDLE_COUNT 4

class EndPoint; 
struct ServerData;

// Server -> Session -> Endpoint
using t_pServerData = std::shared_ptr<ServerData>;
struct EndPointArgs;
using t_pEndPointArgs = std::shared_ptr<EndPointArgs>;
class Session;
using t_pPostgresAdapter = std::shared_ptr<PostgresAdapter>;
using t_pSession = std::shared_ptr<Session>;


struct ServerData
{
    t_pAuthCollectorBase authCollector;
    t_pJsonConverter converter;
    std::vector<EndPoint> endPoints;
    t_pPostgresAdapter postgres_adapter;
    
};
class Server
{
public:
    Server(t_pServerData);
    ~Server();

    void join();
    void start_session_handler();
    void start_acceptor();
    void add_end_point(std::string uri, void (*f)(t_pEndPointArgs));
private:
    bool m_acceptor_working;
    bool m_session_handle;
    int m_serverSocket;
    bool m_logger_inited;
    std::thread m_threads[1 + THREAD_HANDLE_COUNT];
    std::mutex m_mut_sessions;
    std::queue<t_pSession> m_sessions;
    t_pServerData m_data;
    void m_acceptor();
    void m_session_handler();
    void m_on_accept(t_pSession session);

};

