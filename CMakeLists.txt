cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 14)

project(SuperAlfaBros)

add_executable(SuperAlfaBros main.cpp Map/Map.hpp Map/Map.cpp Objects/Object.hpp Objects/Object.cpp Objects/Teleporter.hpp Objects/Teleporter.cpp Lists/DynamicObjectList.cpp Lists/DynamicObjectList.hpp Lists/DynamicLevelList.cpp Lists/DynamicLevelList.hpp Objects/Player.cpp Objects/Player.hpp Map/MapFiles.cpp Map/MapFiles.hpp Objects/Spikes.cpp Objects/Spikes.hpp Objects/Bomb.cpp Objects/Bomb.hpp Objects/Patrol.cpp Objects/Patrol.hpp Objects/knife.cpp Objects/knife.hpp Objects/gun.cpp Objects/gun.hpp Objects/weapon.cpp Objects/weapon.hpp)
target_link_libraries(SuperAlfaBros -lncursesw -lstdc++fs -pthread)