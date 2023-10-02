cmake_minimum_required(VERSION 3.26)
project(PP_task3)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        caesar_cipher.cpp
        main.cpp
)

add_library(CaesarCipher SHARED ${SOURCE_FILES})
