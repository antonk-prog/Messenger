#include <Session.hpp>
#include <Server.hpp>

Session::Session(int serverSocket)
{
    m_fd = accept(serverSocket, nullptr, nullptr);
    m_bad_session = false;
    if (m_fd < 0)
        m_bad_session = true;
    response = std::make_shared<std::string>();
}

Session::~Session()
{
    if (!m_bad_session)
        close(m_fd);
}

void Session::handle(t_pServerData data)
{
    m_read();

    if (m_request_parse())
    {
        m_create_response(data);
    }
    else
    {
        //TODO fix parse error
        std::cout << "UI";
    }
    m_send();
}

void Session::m_read()
{

    size_t readed;
    char buffer[2048] = {0};

    std::memset(buffer, 0, 2048);
    recv(m_fd, buffer, sizeof(buffer), 0);
    request.append(buffer);
}

void Session::m_create_response(t_pServerData data)
{
    std::stringstream ss;
    std::string context;
    t_pEndPointArgs argsEndPoint;
    
    argsEndPoint = std::make_shared<EndPointArgs>();
    argsEndPoint->serverData = data;
    argsEndPoint->request = m_req;
    response = argsEndPoint->response;
    // TODO
    // Заглушка статуса ответа, отсутсвие заголовков в ответе
    ss << "HTTP/1.0 200 OK\r\nContent-Length: ";
    ss << m_req->uri.size() << "\r\n\r\n";
    ss << m_req->uri;
    *response = ss.str();


    for (auto endPoint: data->endPoints)
    {
        if (endPoint == m_req->uri)
        {
            *response = std::string();
            endPoint(argsEndPoint);
            break;
        }
    }
}

void Session::m_send()
{
    send(m_fd, response->c_str(), response->size(), 0);
}

bool Session::m_request_parse()
{
    char* c_requests = (char *)request.c_str();

    m_req = std::make_shared<httpparser::Request>();
    httpparser::HttpRequestParser::ParseResult res = parser.parse(
        *m_req,
        c_requests,
        c_requests + request.size()
    );

    if (res != httpparser::HttpRequestParser::ParsingCompleted)
        return false;
    return true;
}