cmake_minimum_required(VERSION 3.10)

project(pr4)

set(CMAKE_C_STANDART 11)

include_directories(common)

add_executable(server
	server.c
)

add_executable(client
	client.c
)
