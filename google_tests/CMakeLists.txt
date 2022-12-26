project(google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(lab2_tests lab2_tests.cpp)
target_link_libraries(lab2_tests src)
target_link_libraries(lab2_tests gtest gtest_main)

add_executable(lab3_tests lab3_tests.cpp)
target_link_libraries(lab3_tests src)
target_link_libraries(lab3_tests gtest gtest_main)