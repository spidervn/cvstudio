cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)

project( textdetect )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( textdetect textdetect.cpp )
target_link_libraries( textdetect ${OpenCV_LIBS})
