cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Monopoly_Il_Cavo_Coassiale)

include_directories(include) 

add_library(Casella
include/Casella.h
src/Casella.cpp
)

add_library(Casella_laterale
include/Casella_laterale.h
src/Casella_laterale.cpp
)

add_library(Tabellone
include/Tabellone.h
src/Tabellone.cpp
)

add_library(Giocatore
include/Giocatore.h
src/Giocatore.cpp
)

add_executable(TestTabellone src/TestTabellone.cpp)

target_link_libraries(TestTabellone Tabellone Casella_laterale Casella)


install(TARGETS TestTabellone DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)