cmake_minimum_required(VERSION 2.8.6)
project(WizardIDE)

include_directories(
	"include"
	)

file(GLOB sources src/*.cpp)

add_definitions("-std=gnu++0x")
add_definitions("-g")
add_definitions("-Wall -Wextra")

# when we start work on the ide, swap these lines around
add_executable(wizard ${sources} parser.cpp)
# add_executable(wide ${sources} ide.cpp)
