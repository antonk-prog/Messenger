#if !defined(SERVER_HPP)
#define SERVER_HPP

#include <chrono>
#include <queue>
#include <thread>
#include <mutex>
#include <memory>
#include <iostream> 
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_PORT 8484
#define THREAD_HANDLE_COUNT 4

// Server -> Session -> Endpoint

class EndPoint;

class Session;
using t_pSession = std::shared_ptr<Session>;

class Server
{
public:
    Server();
    ~Server();

    void join();
    void start_session_handler();
    void start_acceptor();

private:
    bool m_acceptor_working;
    bool m_session_handle;
    int m_serverSocket;
    bool m_logger_inited;
    std::thread m_threads[1 + THREAD_HANDLE_COUNT];
    std::mutex m_mut_sessions;
    std::queue<t_pSession> m_sessions;

    void m_acceptor();
    void m_session_handler();
    void m_on_accept(t_pSession session);

};

#endif