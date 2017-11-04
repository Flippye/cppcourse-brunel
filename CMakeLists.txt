cmake_minimum_required(VERSION 2.6)
project(neuron)

set(CMAKE_CXX_FLAGS "-O3 -W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(neuron
			neuron.cpp
			main.cpp
			cortex.cpp)

add_executable(neuron_unittest
			neuron.cpp
			neuronUnittest.cpp
			cortex.cpp)

target_link_libraries(neuron_unittest 
						gtest
						gtest_main)
						
add_test(neuron_unittest neuron_unittest)

find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxyconfig ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	add_custom_target(doc
	${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
endif(DOXYGEN_FOUND)
