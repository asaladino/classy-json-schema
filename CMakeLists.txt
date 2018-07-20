cmake_minimum_required(VERSION 3.10)

include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.22.19.tar.gz"
        SHA1 "54749ffc945f78362aa680a7abbafcaa40ff9069"
)

project(classy_json_schema)

set(CMAKE_CXX_STANDARD 17)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets CONFIG REQUIRED)

hunter_add_package(inja)
find_package(inja CONFIG REQUIRED)

# download boost
hunter_add_package(Boost COMPONENTS system filesystem)
# now boost can be used
find_package(Boost CONFIG REQUIRED system filesystem)

add_executable(classy_json_schema
        src/main.cpp
        src/Controller/Qt/mainwindow.cpp
        src/Controller/Qt/mainwindow.h
        src/Controller/Qt/mainwindow.ui
        src/Model/Setting.cpp
        src/Model/Setting.h
        src/Repository/JsonSchemaRepository.cpp
        src/Repository/JsonSchemaRepository.h
        src/Utility/ClassCreateUtility.cpp
        src/Utility/ClassCreateUtility.h
        src/Controller/CliController.cpp
        src/Controller/CliController.h
        src/Controller/GuiController.cpp
        src/Controller/GuiController.h src/Utility/FileValidator.cpp src/Utility/FileValidator.h)

target_link_libraries(classy_json_schema
        Qt5::Widgets
        inja::inja
        Boost::filesystem
        Boost::system)