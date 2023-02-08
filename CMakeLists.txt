cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 14)

project(SuperAlfaBros)


add_executable(SuperAlfaBros main.cpp Map/Map.hpp Map/Map.cpp Objects/Object.hpp Objects/Object.cpp Objects/Teleporter.hpp Objects/Teleporter.cpp Lists/DynamicObjectList.cpp Lists/DynamicObjectList.hpp Lists/DynamicLevelList.cpp Lists/DynamicLevelList.hpp Objects/Player.cpp Objects/Player.hpp Map/MapFiles.cpp Map/MapFiles.hpp Objects/Spikes.cpp Objects/Spikes.hpp Objects/Bomb.cpp Objects/Bomb.hpp Objects/Patrol.cpp Objects/Patrol.hpp Objects/Weapons/Weapon.cpp Objects/Weapons/Weapon.hpp Objects/Weapons/Shotgun.cpp Objects/Weapons/Shotgun.hpp Objects/Weapons/Gun.cpp Objects/Weapons/Gun.hpp Objects/Bullet.cpp Objects/Bullet.hpp Objects/Weapons/AllWeapons.hpp Progress/CodeList.hpp Progress/CodeList.hpp Progress/CodeList.cpp Progress/ProgressManager.hpp Progress/ProgressManager.hpp Progress/ProgressManager.cpp Market/SkinList.hpp Market/SkinList.cpp Market/MarketManager.hpp Market/MarketManager.cpp Market/RefillList.hpp Market/RefillList.cpp Market/WeaponItemList.hpp Market/WeaponItemList.cpp Market/MenuDisplayer.hpp Market/MenuDisplayer.cpp Market/MarketDisplayer.hpp Market/MarketDisplayer.cpp Utilities/StringUtilities.h Utilities/StringUtilities.cpp Utilities/Movement.hpp Utilities/Movement.cpp Objects/Weapons/Shotgun.cpp)

target_link_libraries(SuperAlfaBros -lncursesw -lstdc++fs)