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
project( visonfund  )
find_package( OpenCV REQUIRED )

include_directories(VisionFundamental/)

file(GLOB SOURCES "VisionFundamental/*.cpp" 
                    "VisionFundamental/visionfund/impl/*.cpp")

add_executable( visonfund ${SOURCES} )
target_link_libraries( visonfund ${OpenCV_LIBS} )