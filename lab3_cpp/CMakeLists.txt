cmake_minimum_required(VERSION 3.27)
project(lab3_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_subdirectory(Inventory)
add_subdirectory(Character)
add_subdirectory(Level)

add_subdirectory(tests)

add_executable(Game main.cpp)
target_link_libraries(Game characters)
target_link_libraries(Game inventory)
target_link_libraries(Game level)

#add_executable(Game main.cpp Level/Matrix.cpp Level/Matrix.h)

#set(SOURCE_FILES ./)
#add_executable(Game ${SOURCE_FILES})

#add_executable(Game main.cpp Level/Level.cpp Level/Level.h Level/Point.h Level/Cell.h Level/Cell.cpp Level/Matrix.h Level/Matrix.cpp Inventory/Inventory.cpp Inventory/Inventory.h
#        Inventory/Items/Item.cpp Inventory/Items/Item.h Inventory/Items/ContainerForBullet.cpp
#        Inventory/Items/ContainerForBullet.h Inventory/Items/MedKit.cpp Inventory/Items/Weapon.cpp Inventory/Items/MedKit.h Inventory/Items/Weapon.h
#        Interfaces/Attack.h Interfaces/UserInventory.h Interfaces/UserWeapon.h
#        Character/Character.h Character/Character.cpp Character/Kinds/Enemy.cpp Character/Kinds/Forager.cpp Character/Kinds/Operative.cpp Character/Kinds/Reasonable.cpp Character/Kinds/Wild.cpp
#        Character/Kinds/Enemy.h Character/Kinds/Forager.h Character/Kinds/Operative.h Character/Kinds/Reasonable.h Character/Kinds/Wild.h)

#target_link_libraries(Game matrix)