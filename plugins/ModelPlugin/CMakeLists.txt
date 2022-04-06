cmake_minimum_required(VERSION 3.14)

project(ModelPlugin VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(modelPlugin
	SHARED

	plugin.h
	myModel.h

	plugin.cpp
	myModel.cpp

	)

find_package(Qt5 REQUIRED COMPONENTS Core Quick Qml)

target_link_libraries(
	modelPlugin
	PRIVATE
	Qt5::Core
	Qt5::Quick
	Qt5::Qml
	)
