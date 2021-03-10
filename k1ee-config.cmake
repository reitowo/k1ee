find_path(K1EE_INCLUDE_DIR
          NAMES file.h)

find_library(K1EE_LIBRARY
             NAMES k1ee
             HINTS ${K1EE_LIBRARY_ROOT})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(K1EE REQUIRED_VARS K1EE_LIBRARY K1EE_INCLUDE_DIR)

if(K1EE_FOUND)
    set(K1EE_LIBRARIES ${K1EE_LIBRARY})
    set(K1EE_INCLUDE_DIRS ${K1EE_INCLUDE_DIR})
endif()
