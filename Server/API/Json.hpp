#if !defined(JSON_HPP_)
#define JSON_HPP_


#include <json.hpp>
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

class JsonConverter
{
public:
    JsonConverter();
    ~JsonConverter();

    std::string getJson();
    // nlohmann::json getObj(std::string) = nlohmann::json::parse;

private:
    // std::map<>

};

using t_pJsonConverter = std::shared_ptr<JsonConverter>;

#endif