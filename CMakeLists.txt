cmake_minimum_required(VERSION 3.10)

include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.22.19.tar.gz"
        SHA1 "54749ffc945f78362aa680a7abbafcaa40ff9069"
)

project(classy_json_schema)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH /usr/local/opt/qt5/)

find_package(Qt5Widgets)

hunter_add_package(inja)
find_package(inja CONFIG REQUIRED)


add_executable(classy_json_schema
        src/main.cpp
        src/Repository/JsonSchemaRepository.cpp
        src/Repository/JsonSchemaRepository.h
        src/Utility/ClassCreateUtility.cpp
        src/Utility/ClassCreateUtility.h src/Model/Setting.cpp src/Model/Setting.h)

target_link_libraries(classy_json_schema Qt5::Widgets inja::inja)