#pragma once
#include "Log.hpp"

#include "nlohmann/json.hpp"

#include <exception>
#include <sstream>
#include <string>

namespace LogAndConfig {

template <typename T>
void getJSONValue(const nlohmann::json& json, T& data, std::stringstream& ss, const std::string& key)
{
    ss << '.' << key;
    if (json.find(key) == json.cend())
        throw std::runtime_error("can't parse " + ss.str());

    data = json[key];
    return;
}

template <typename T, typename... Types>
void getJSONValue(const nlohmann::json& json, T& data, std::stringstream& ss, const std::string& key, const Types&... keys)
{
    ss << '.' << key;
    if (json.find(key) == json.cend())
        throw std::runtime_error("can't parse " + ss.str());

    nlohmann::json value = json[key];
    getJSONValue(value, data, ss, keys...);

    return;
}

template <typename T, typename... Types>
void getJSONValue(const nlohmann::json& json, T& data, const std::string& key, const Types&... keys)
{
    std::stringstream ss;
    ss << key;

    if (json.find(key) == json.cend())
        throw std::runtime_error("can't parse " + ss.str());

    nlohmann::json value = json[key];
    getJSONValue(value, data, ss, keys...);

    return;
}

class ConfigLoader {
public:
    bool loadFile(const std::string& filePath);

    Config::Log log() const;

private:
    Config::Log m_log;
};

}
