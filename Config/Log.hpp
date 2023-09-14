#pragma once
#include <string>

namespace LogAndConfig {
namespace Config {

    struct Log {
        std::string level = "trace";
        std::string path;
        size_t fileNum = 3;
        size_t maxSizeMB = 5;
    };

}
}
