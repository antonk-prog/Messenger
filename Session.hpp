#if !defined(SESSION_HPP)
#define SESSION_HPP

#include <string>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <memory>


class Session
{
public:
	Session(int);
	~Session();
	
	void handle();

private:
	int m_fd;
	std::string request;
    std::string response;

	bool m_bad_session;

	void m_read();
	// void m_parse();
	void m_create_response();
	void m_send();
	bool m_request_parse();
};

using t_pSession = std::shared_ptr<Session>;

#endif