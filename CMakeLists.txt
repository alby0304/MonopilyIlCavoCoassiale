cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Monopoly_Il_Cavo_Coassiale)

include_directories(include) 


add_library(Monopoly
    include/Casella.h
    src/Casella.cpp
    include/Casella_Laterale.h
    src/Casella_Laterale.cpp
    include/Tabellone.h
    src/Tabellone.cpp
    include/Giocatore.h
    src/Giocatore.cpp
    include/Human.h
    src/Human.cpp
    include/Computer.h
    src/Computer.cpp
    include/Human.h
    src/Human.cpp
    include/Computer.h
    src/Computer.cpp
)

add_executable(TestTabellone src/TestTabellone.cpp)
add_executable(Game src/Game.cpp)

target_link_libraries(TestTabellone Monopoly)
target_link_libraries(Game Monopoly)



install(TARGETS TestTabellone DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
install(TARGETS Game DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)