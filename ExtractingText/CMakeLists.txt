cmake_minimum_required(VERSION 2.8)

macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)

use_cxx11()
set (CMAKE_CXX_STANDARD 11)
project( extract_text  )
find_package( OpenCV REQUIRED )

include_directories(src/)
include_directories(src/libs)
include_directories($ENV{BOOST_171_DIR})
link_directories($ENV{BOOST_171_DIR}/libs)

file(GLOB SOURCES "src/*.cpp" 
                    "src/extract/*.cpp"
                    "src/app/impl/application/*.cpp"
                    "src/app/impl/application/poultry/*.cpp"
                    "src/app/impl/background/*.cpp"
                    "src/app/impl/cv/*.cpp"
                    "src/app/impl/general/*.cpp"
                    "src/app/examples/background/*.cpp")

add_executable( extract_text ${SOURCES} )
target_link_libraries( extract_text ${OpenCV_LIBS} )