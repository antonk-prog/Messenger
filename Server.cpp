#include "Server.hpp"

Server::Server(){
    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress; 
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_port = htons(SERVER_PORT); 
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(
        m_serverSocket,
        (struct sockaddr*)&serverAddress,
        sizeof(serverAddress)
    );
    if (listen(m_serverSocket, 5) < 0) // максимальная длина очереди ожидающих соединений
    {

    }

    m_acceptor_working = false;
    m_session_handle = false;
}

Server::~Server()
{
    close(m_serverSocket); 
}

void Server::start_acceptor()
{
    m_acceptor_working = true;
    std::thread accept_thread(&Server::m_acceptor, this);
    std::swap(accept_thread, m_threads[0]);

}

void Server::start_session_handler()
{
    m_session_handle = true;
    m_threads[1] = std::thread(&Server::m_session_handler, this);

}

void Server::m_on_accept(pSession session)
{
    std::lock_guard _lock(m_mut_sessions);

    m_sessions.push(session);
}

void Server::m_acceptor()
{
    pSession cur_session;
    
    while (m_acceptor_working)
        m_on_accept( std::make_shared<Session>(m_serverSocket) );
}

void Server::m_session_handler()
{
    pSession cur_session;

    while (m_session_handle)
    {
        if (m_sessions.empty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

        while (!m_sessions.empty())
        {
            {
                std::lock_guard _lock(m_mut_sessions);
                cur_session = std::move(m_sessions.front());
            }
            if (cur_session.get() == nullptr)
                break;
            cur_session->handle();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }   
}

void Server::join()
{
    m_threads[0].join();
    m_threads[1].join();
}