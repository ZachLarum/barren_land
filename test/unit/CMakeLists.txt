include(GoogleTest)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

######################################
# FarmLand Tests
######################################
add_executable(farm-land-unit-tests "")

target_sources(farm-land-unit-tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/FarmLandTests.cpp
        ${PROJECT_SOURCE_DIR}/src/Point.cpp
        ${PROJECT_SOURCE_DIR}/src/Land.cpp
)

target_include_directories(farm-land-unit-tests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(farm-land-unit-tests
    PRIVATE
        gtest
        gtest_main
        Threads::Threads
)

set_target_properties(farm-land-unit-tests
    PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

add_test(farm-land-unit-tests farm-land-unit-tests)

######################################
# InputParser Tests
######################################
add_executable(input-parser-unit-tests "")

target_sources(input-parser-unit-tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/InputParserTests.cpp
        ${PROJECT_SOURCE_DIR}/src/Point.cpp
        ${PROJECT_SOURCE_DIR}/src/Land.cpp
        ${PROJECT_SOURCE_DIR}/src/FarmLand.cpp
)

target_include_directories(input-parser-unit-tests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(input-parser-unit-tests
    PRIVATE
        gtest
        gtest_main
        Threads::Threads
)

set_target_properties(input-parser-unit-tests
    PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

add_test(input-parser-unit-tests input-parser-unit-tests)

######################################
# Land Tests
######################################
add_executable(land-unit-tests "")

target_sources(land-unit-tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/LandTests.cpp
        ${PROJECT_SOURCE_DIR}/src/Point.cpp
)

target_include_directories(land-unit-tests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(land-unit-tests
    PRIVATE
        gtest
        gtest_main
        Threads::Threads
)

set_target_properties(land-unit-tests
    PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

add_test(land-unit-tests land-unit-tests)
