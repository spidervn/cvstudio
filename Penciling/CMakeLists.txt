cmake_minimum_required(VERSION 2.8)

project( penciling  )
find_package( OpenCV REQUIRED )

include_directories(src/)
file(GLOB SOURCES "src/*.cpp" 
            "src/pencil/*.cpp")

add_executable( penciling ${SOURCES} )
target_link_libraries( penciling ${OpenCV_LIBS} )
