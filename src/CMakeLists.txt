
cmake_minimum_required (VERSION 3.15)

add_library(k1ee
    "file.cpp"
)

add_library(k1ee::k1ee ALIAS k1ee)

target_include_directories(k1ee PUBLIC $<INSTALL_INTERFACE:include>)

set_target_properties(k1ee
     PROPERTIES
     VERSION ${${PROJECT_NAME}_VERSION}
     SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR}) 

set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets") 
     
install(TARGETS k1ee
  EXPORT ${TARGETS_EXPORT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib 
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
)

install(
  EXPORT ${TARGETS_EXPORT_NAME} 
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        DESTINATION lib/cmake/${PROJECT_NAME})

if (NOT DISABLE_INSTALL_HEADERS)
  install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../include/k1ee DESTINATION include)
endif()