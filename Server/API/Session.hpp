#pragma once

/*
TODO
Session

Поменять сокеты на библиотеку
start -> read -> create_answer -> write -> close
*/

#include <string>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <Json.hpp>
#include <EndPoint.hpp>
#include <httpparser/request.h>
#include <httpparser/httprequestparser.h>

struct ServerData;
using t_pServerData = std::shared_ptr<ServerData>;

using t_pRequest = std::shared_ptr<httpparser::Request>;
using t_pResponse = std::shared_ptr<std::string>;


// Где=то течет память после
class Session
{
public:
	Session(int);
	~Session();
	
	void handle(t_pServerData);

private:
	int m_fd;
	std::string request;
	t_pResponse response;
	httpparser::HttpRequestParser parser;
	t_pRequest m_req;

	bool m_bad_session;

	void m_read();
	// void m_parse();
	void m_create_response(t_pServerData);
	void m_send();
	bool m_request_parse();
};

using t_pSession = std::shared_ptr<Session>;

