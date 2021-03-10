cmake_minimum_required (VERSION 3.15)

target_include_directories(k1ee PUBLIC  
    $<INSTALL_INTERFACE:include>    
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_sources(k1ee PRIVATE
     # Header files (useful in IDEs)
    "k1ee/file.h"
    "k1ee/exception.h"
)

install(DIRECTORY k1ee DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})