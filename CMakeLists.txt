cmake_minimum_required(VERSION 3.10)

project(pr4)

set(CMAKE_C_STANDART 11)

include_directories(common)

add_executable(pr4
	server.c
	client.c
)
