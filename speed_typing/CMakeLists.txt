cmake_minimum_required(VERSION 3.10)


project(speed_typing)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)


set(SOURCES
    src/Button.cpp
    src/TextBox.cpp
    src/User.cpp
    src/UserManager.cpp
    src/ModeStrategy.cpp
    src/Menu.cpp
    src/main.cpp
)

add_executable(speed_typing ${SOURCES})

target_link_libraries(speed_typing sfml-graphics sfml-window sfml-system)
