cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(LogAndConfig LANGUAGES CXX)

include_directories(ThirdParty)
include_directories(Config)

set(HEADER_FILES
        ConfigLoader/ConfigLoader.hpp

        Config/Log.hpp
        )

add_executable(LogAndConfig main.cpp ${HEADER_FILES})
target_sources(LogAndConfig
    PRIVATE
        ConfigLoader/ConfigLoader.cpp
        )
