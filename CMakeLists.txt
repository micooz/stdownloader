cmake_minimum_required(VERSION 2.6)

project (Songtaste)

list (APPEND CMAKE_CXX_FLAGS "-std=c++11 -O2 -pthread")

set (BOOST_ROOT "D:/libs/boost_1_56_0")

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set (BOOST_LIBS
		system-mgw49-mt-1_56 
		regex-mgw49-mt-1_56 
		filesystem-mgw49-mt-1_56 
		program_options-mgw49-mt-1_56)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set (BOOST_LIBS
		system
		regex
		filesystem
		program_options)
endif ()

find_package (Boost COMPONENTS ${BOOST_LIBS} REQUIRED)
find_library (Jsoncpp NAMES jsoncpp HINTS libs/jsoncpp-0.7.0/lib)

include_directories ("public")
include_directories ("libs/avhttp-2.9.9/include")
include_directories ("libs/jsoncpp-0.7.0/include")
include_directories (${BOOST_ROOT})

add_subdirectory (songtaste)
add_subdirectory (down)
add_subdirectory (parse)
add_subdirectory (list)
