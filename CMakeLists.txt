#CMakeLists.txt - корневой файл сборки проекта
#
#Дозоров Владимир Евгеньевич
#Группа МК - 101

cmake_minimum_required(VERSION 3.10)
project(task2_replacer C)

# Подключаем наши вспомогательные функции
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(MyFunctions)

# Задаем размер блока N. Если не указан, берем 1024 по умолчанию
if(NOT DEFINED BLOCK_SIZE)
    set(BLOCK_SIZE 1024)
endif()

# Передаем N в компилятор, как требуется в задании
add_definitions(-DN=${BLOCK_SIZE})

# Разделяем на библиотеку и главную программу
add_subdirectory(lib)
add_subdirectory(app)