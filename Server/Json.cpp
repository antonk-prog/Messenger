#include <Json.hpp>

JsonConverter::JsonConverter()
{}

JsonConverter::~JsonConverter()
{}

std::string JsonConverter::getJson()
{

    nlohmann::json j_item;

    return j_item.dump();
}
