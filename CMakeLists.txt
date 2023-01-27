cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 14)

project(SuperAlfaBros)

add_executable(SuperAlfaBros main.cpp Map/Map.hpp Map/Map.cpp Objects/Object.hpp Objects/Object.cpp Objects/Teleporter.hpp Objects/Teleporter.cpp Lists/DynamicObjectList.cpp Lists/DynamicObjectList.hpp Lists/DynamicLevelList.cpp Lists/DynamicLevelList.hpp Objects/Player.cpp Objects/Player.hpp Map/MapFiles.cpp Map/MapFiles.hpp Objects/Spikes.cpp Objects/Spikes.hpp Objects/Bomb.cpp Objects/Bomb.hpp Progress/CodeData.hpp Progress/CodeData.hpp Progress/CodeData.cpp Progress/ProgressManager.hpp Progress/ProgressManager.hpp Progress/ProgressManager.cpp Market/SkinList.hpp Market/SkinList.cpp Market/MarketManager.hpp Market/MarketManager.cpp Market/RefillList.hpp Market/RefillList.cpp Market/WeaponList.hpp Market/WeaponList.cpp Market/MenuDisplayer.hpp Market/MenuDisplayer.cpp Market/MarketDisplayer.hpp Market/MarketDisplayer.cpp Utilities/StringUtilities.h Utilities/StringUtilities.cpp)
target_link_libraries(SuperAlfaBros -lncursesw -lstdc++fs)