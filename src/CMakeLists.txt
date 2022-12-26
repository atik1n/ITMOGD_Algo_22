project(lab_src)
set(CMAKE_CXX_STANDARD 20)

set(HEADER_FILES dyn-array.hpp quicksort.hpp)

add_library(src STATIC ${HEADER_FILES})
set_target_properties(src PROPERTIES LINKER_LANGUAGE CXX)