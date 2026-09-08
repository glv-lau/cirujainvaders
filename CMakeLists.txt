cmake_minimum_required(VERSION 3.16)
project(CirujaInvaders CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(CirujaInvaders
    Main.cpp
    Game.cpp
    Match.cpp
    AssetManager.cpp
    Scenes/Scene.cpp
    Scenes/SceneMenu.cpp
    Scenes/SceneStageIntro.cpp
    Scenes/Button.cpp
    Entities/Entity.cpp
    Entities/Player.cpp
    Entities/Enemy.cpp
    Entities/Bullet.cpp
    Entities/PowerUp.cpp
)

target_include_directories(CirujaInvaders PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Scenes
    ${CMAKE_SOURCE_DIR}/Entities
)

target_link_libraries(CirujaInvaders PRIVATE sfml-graphics sfml-window sfml-system)

configure_file(${CMAKE_SOURCE_DIR}/Nave.png ${CMAKE_BINARY_DIR}/Nave.png COPYONLY)

if(EXISTS ${CMAKE_SOURCE_DIR}/arial.ttf)
    configure_file(${CMAKE_SOURCE_DIR}/arial.ttf ${CMAKE_BINARY_DIR}/arial.ttf COPYONLY)
endif()
