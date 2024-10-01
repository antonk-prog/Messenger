#include "Server.hpp"
#include <algorithm>
#include <iostream>

int main()
{
    Server server;

    server.start_acceptor();
    server.start_session_handler();

    server.join();

    return (0);
}