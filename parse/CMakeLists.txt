cmake_minimum_required(VERSION 2.6)

project (parse)

add_executable (parse main.cpp ../public/Configure.cpp)

target_link_libraries (parse 
	${Boost_LIBRARIES}
  	${Jsoncpp}
)
