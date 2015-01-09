cmake_minimum_required(VERSION 2.6)

project (list)

aux_source_directory (. SOURCE_FILES)
set (SOURCE_FILES ${SOURCE_FILES} ../public/Configure.cpp)
add_executable (list ${SOURCE_FILES})

if (WIN32)
	target_link_libraries (list ws2_32)
endif (WIN32)

target_link_libraries (list 
  	${Boost_LIBRARIES}
  	${Jsoncpp}
)
