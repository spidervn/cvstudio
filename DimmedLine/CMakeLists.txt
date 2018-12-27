cmake_minimum_required(VERSION 2.8)

project( dimmed_line  )
find_package( OpenCV REQUIRED )

include_directories(src/)
file(GLOB SOURCES "src/*.cpp" 
                    "src/dimmed/*.cpp")

add_executable( dimmed_line ${SOURCES} )
target_link_libraries( dimmed_line ${OpenCV_LIBS} )
