cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)

project( distrans )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( distrans distrans.cpp )
target_link_libraries( distrans ${OpenCV_LIBS})

