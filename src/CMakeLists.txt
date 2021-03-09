
cmake_minimum_required (VERSION 3.15)

add_library(k1ee
    "file.cpp"
)

add_library(k1ee::k1ee ALIAS k1ee)

set_target_properties(k1ee
     PROPERTIES
     VERSION ${${PROJECT_NAME}_VERSION}
     SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR})
      
install(TARGETS k1ee)