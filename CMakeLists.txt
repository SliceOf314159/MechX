cmake_minimum_required(VERSION 3.16)
project(Kosztorys LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(kosztorys
    src/main.cpp
    src/Pojazd.cpp
    src/Czesc.cpp
    src/StanowiskoNaprawcze.cpp
    src/UslugaProsta.cpp
    src/UslugaZlozna.cpp
    src/BazaUslug.cpp
    src/Kosztorys.cpp
)
