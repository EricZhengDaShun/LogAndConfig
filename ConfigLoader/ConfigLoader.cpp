#include "ConfigLoader.hpp"

#include "spdlog/spdlog.h"

#include <fstream>
#include <sstream>

using namespace LogAndConfig;

bool ConfigLoader::loadFile(const std::string& filePath)
{
    spdlog::debug("ConfigLoader::loadFile filePath: {}", filePath);

    std::ifstream is;
    is.open(filePath);
    if (!is.is_open()) {
        spdlog::warn("ConfigLoader can't open file {}", filePath);
        return false;
    }

    std::stringstream ss;
    ss << is.rdbuf();
    const std::string rawData = ss.str();
    spdlog::trace("config file rawData: {}", rawData);
    nlohmann::json json = nlohmann::json::parse(rawData);

    getJSONValue(json, m_log.level, "log", "level");
    getJSONValue(json, m_log.path, "log", "path");
    getJSONValue(json, m_log.fileNum, "log", "fileNum");
    getJSONValue(json, m_log.maxSizeMB, "log", "maxSizeMB");

    return true;
}

Config::Log ConfigLoader::log() const
{
    return m_log;
}
