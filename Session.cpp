#include "Session.hpp"

Session::Session(int serverSocket)
{
    m_fd = accept(serverSocket, nullptr, nullptr);
    m_bad_session = false;
    if (m_fd < 0)
        m_bad_session = true;
}

Session::~Session()
{
    if (!m_bad_session)
        close(m_fd);
}

void Session::handle()
{
    m_read();
    m_create_response();
    m_send();
}

void Session::m_read()
{
    /*
    TODO
    Добавить ограничения для чтения
    Максимальное время
    Максимальный размер
    */
    size_t readed;
    char buffer[2048] = {0};

    std::memset(buffer, 0, 2048);
    recv(m_fd, buffer, sizeof(buffer), 0);
    request.append(buffer);
}

void Session::m_create_response()
{

    response = std::string(request);
}

void Session::m_send()
{
    send(m_fd, response.c_str(), response.size(), 0);
}