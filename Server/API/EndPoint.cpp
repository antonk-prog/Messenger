#include <EndPoint.hpp>
#include <Server.hpp>
#include <URI.hpp>
#define API_VERSION_V1 "/api/v1"

// void EP_api_get_inventory(t_pEndPointArgs argv)
// {
// 	/*
// 	Добавить проверку сессии
// 	*/

// 	// URI _uri;
// 	std::stringstream ss;
// 	// t_InventoryId id = -1;

// 	// if (argv->request->method != "POST")
// 	// 	return;
//     std::string str_to_send = "hello";
//     ss << "HTTP/1.0 200 OK \r\nContent-Length: ";
//     ss << str_to_send.size() << "\r\n\r\n";
//     ss << str_to_send;


// 	// _uri.Parse(argv->request->uri);
// 	// if (_uri.params.find("id") != _uri.params.end())
// 	// {
// 	// 	try
// 	// 	{
// 	// 		id = std::stoul(_uri.params["id"]);
// 	// 		ss << argv->serverData->converter->getJson(
// 	// 			argv->serverData->inventoryCollector->getInventoryById(id)
// 	// 		);
// 	// 	}
// 	// 	catch(const std::exception& e)
// 	// 	{
// 	// 		ss << _uri.params["id"];
// 	// 		return;
// 	// 	}
// 	// }

// 	*(argv->response) = ss.str();
// }

void api_login(t_pEndPointArgs argv)
{
	/*
	TODO
	пределать авторизацию на OAuth2.0
	*/
	std::string username, password, hash;
	URI _uri;

	if (argv->request->method != "POST")
		return;
	argv->response->append(OK_HTTP_STRING);
	std::string data(argv->request->content.begin(), argv->request->content.end());
	data = "?" + data;
	_uri.Parse(data);
	for (auto& item: _uri.params)
	{
		if (item.first == "username")
			username = item.second;
		if (item.first == "password")
			password = item.second;
	}

	if (username.empty() || password.empty())
		return ;

	// TODO переделать на строки
	hash = argv->serverData->authCollector->login(
		(char *)username.c_str(), (char *)password.c_str()
	);
	if (!hash.empty())
	{
		argv->response->append("Authentication: ");
		argv->response->append(hash);
		argv->response->append("\r\n");
	}

	argv->response->append("\r\n");
	argv->response->append("chlen");
}

// static inline t_InventoryId inventory_id_by_auth(t_pEndPointArgs argv)
// {
// 	std::string hash;

// 	for (auto& item: argv->request->headers)
// 	{
// 		if (item.name == "Authentication")
// 		{
// 			hash = item.value;
// 		}
// 	}

// 	if (hash.empty())
// 		throw -1;

// 	return argv->serverData->authCollector->getIdByHash(
// 		hash
// 	); 
// }

// void EP_api_plug(t_pEndPointArgs argv)
// {
// 	std::stringstream ss;

// 	ss << OK_HTTP_STRING;
// 	ss << "\r\nEnd point not realized.";

// 	*(argv->response) = ss.str();
// }

void add_all_endpoints(Server& server)
{
	// server.add_end_point(API_VERSION_V1"/test", EP_api_get_inventory);
	// server.add_end_point(API_VERSION_V1"/create_sell_order", EP_api_plug);
	// server.add_end_point(API_VERSION_V1"/cancel_buy_order", EP_api_plug);
	// server.add_end_point(API_VERSION_V1"/cancel_sell_order", EP_api_plug);

	// server.add_end_point(API_VERSION_V1"/create_trade", EP_api_plug);
	// server.add_end_point(API_VERSION_V1"/accept_trade", EP_api_plug);
	// server.add_end_point(API_VERSION_V1"/denie_trade", EP_api_plug);
	
	// server.add_end_point(API_VERSION_V1"/get_buy_orders", EP_api_get_buy_orders);
	// server.add_end_point(API_VERSION_V1"/get_my_inventory", EP_api_get_my_inventory);
	// server.add_end_point(API_VERSION_V1"/get_inventory", EP_api_get_inventory);
	
	// server.add_end_point(API_VERSION_V1"/login", api_login);
}