cmake_minimum_required(VERSION 2.8)

project( extract_text  )
find_package( OpenCV REQUIRED )

include_directories(src/)
file(GLOB SOURCES "src/*.cpp" 
                    "src/extract/*.cpp")

add_executable( extract_text ${SOURCES} )
target_link_libraries( extract_text ${OpenCV_LIBS} )
