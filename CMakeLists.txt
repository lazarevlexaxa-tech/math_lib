cmake_minimum_required(VERSION 3.14)
project(math_lib VERSION 1.0.0 LANGUAGES CXX)

# Создаем интерфейсную библиотеку (так как она header-only)
add_library(math_lib INTERFACE)

# Создаем псевдоним, чтобы проект-калькулятор мог обращаться к ней как math_lib::math_lib
add_library(math_lib::math_lib ALIAS math_lib)

# Указываем, где лежат заголовочные файлы
target_include_directories(math_lib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
