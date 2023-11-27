set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(C:/SFML/include)

add_library(game Game.h Game.cpp map.h)
target_link_libraries(game sfml-system sfml-graphics sfml-window sfml-audio)