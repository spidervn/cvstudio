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

file(GLOB STATICLIBS "VisionFundamental/visionfund/impl/*.cpp"
                    "VisionFundamental/visionlab/impl/*.cpp")

file(GLOB SOURCES "VisionFundamental/main.cpp")
                    

add_executable( visionfund ${SOURCES} )
add_library(libvisionfund STATIC ${STATICLIBS})
target_link_libraries(visionfund libvisionfund ${OpenCV_LIBS})