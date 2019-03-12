cmake_minimum_required(VERSION 2.8)

project( extract_text  )
find_package( OpenCV REQUIRED )

include_directories(src/)
file(GLOB SOURCES "src/*.cpp" 
                    "src/extract/*.cpp"
                    "src/app/impl/application/*.cpp"
                    "src/app/impl/background/*.cpp"
                    "src/app/impl/cv/*.cpp"
                    "src/examples/background/*.cpp")

add_executable( extract_text ${SOURCES} )
target_link_libraries( extract_text ${OpenCV_LIBS} )