cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Monopoly_Il_Cavo_Coassiale)

include_directories(include) 

add_library(Giocatori
    include/Giocatore.h
    src/Giocatore.cpp
    include/Computer.h
    src/Computer.cpp
    include/Human.h
    src/Human.cpp
)

add_library(Tabellone
    include/Tabellone.h
    src/Tabellone.cpp
    include/Casella.h
    src/Casella.cpp
    include/Casella_Laterale.h
    src/Casella_Laterale.cpp
)

add_executable(TestTabellone src/TestTabellone.cpp)
add_executable(Game src/Game.cpp)

target_link_libraries(TestTabellone Tabellone)
target_link_libraries(Game Tabellone Giocatori)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
install(TARGETS TestTabellone DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
install(TARGETS Game DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)

