include(GoogleTest)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(barren-land-test "")

target_sources(barren-land-test
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/BarrenLandTests.cpp
)

#target_include_directories(barren-land-test
#    PRIVATE
#)

target_link_libraries(barren-land-test
    PRIVATE
        gtest
        gtest_main
        Threads::Threads
)

set_target_properties(barren-land-test
    PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

add_test(barren-land-test barren-land-test)
