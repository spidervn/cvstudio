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
find_package(Boost COMPONENTS filesystem regex)

include_directories(src/)
include_directories(src/libs)
include_directories($ENV{BOOST_171_DIR})
link_directories($ENV{BOOST_171_DIR}/libs)

find_package(VTK COMPONENTS 
              vtkChartsCore
              vtkCommonCore
              vtkCommonDataModel
              vtkInteractionStyle
              vtkRenderingContext2D
              vtkRenderingContextOpenGL2
              vtkRenderingCore
              vtkRenderingFreeType
              vtkRenderingGL2PSOpenGL2
              vtkRenderingOpenGL2
              vtkViewsContext2D QUIET)
if (NOT VTK_FOUND)
  message("Skipping LinePlot: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")

if (VTK_VERSION VERSION_LESS "8.90.0")
  # Old system
  include(${VTK_USE_FILE})

  file(GLOB SOURCES "src/*.cpp" 
                      "src/extract/*.cpp"
                      "src/app/impl/application/*.cpp"
                      "src/app/impl/application/background/*.cpp"
                      "src/app/impl/application/poultry/*.cpp"
                      "src/app/impl/application/calculus/*.cpp"
                      "src/app/impl/background/*.cpp"
                      "src/app/impl/background/probability/*.cpp"
                      "src/app/impl/cv/*.cpp"
                      "src/app/impl/general/*.cpp"
                      "src/app/examples/background/*.cpp")
  add_executable( extract_text MACOSX_BUNDLE ${SOURCES} )
  target_link_libraries( extract_text ${OpenCV_LIBS} ${Boost_LIBRARIES} ${VTK_LIBRARIES})

else ()
  # 
  file(GLOB SOURCES "src/*.cpp" 
                      "src/extract/*.cpp"
                      "src/app/impl/application/*.cpp"
                      "src/app/impl/application/background/*.cpp"
                      "src/app/impl/application/poultry/*.cpp"
                      "src/app/impl/application/calculus/*.cpp"
                      "src/app/impl/background/*.cpp"
                      "src/app/impl/background/probability/*.cpp"
                      "src/app/impl/cv/*.cpp"
                      "src/app/impl/general/*.cpp"
                      "src/app/examples/background/*.cpp")

  add_executable( extract_text MACOSX_BUNDLE ${SOURCES} )
  target_link_libraries( extract_text ${OpenCV_LIBS} ${Boost_LIBRARIES} ${VTK_LIBRARIES})
  vtk_module_autoinit(
                      TARGETS extract_text
                      MODULES ${VTK_LIBRARIES})
endif ()


