cmake_minimum_required(VERSION 3.24)
project(faceit)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(faceit
  src/main.cpp
  src/Helper.h
  src/Helper.cpp
)

# Third party package linking. Used for packages installed by homebrew(macOS)
# Should be modified for your own os or any other package management system.
# curlpp and nlohmann_json parser are used for the project.

target_include_directories(faceit PUBLIC /opt/homebrew/include)
target_link_directories(faceit PUBLIC /opt/homebrew/lib)

find_package(nlohmann_json 3.2.0 REQUIRED)

target_link_libraries(faceit PUBLIC
  curlpp
  curl
  nlohmann_json::nlohmann_json
)

# Compiler flags and sanitizers
target_compile_options(faceit PRIVATE
  -Wall
  -Wextra
  -Wpedantic
  -Wconversion
  -fno-omit-frame-pointer
  -fsanitize=address)

target_link_options(faceit PRIVATE
  -fno-omit-frame-pointer
  -fsanitize=address)

