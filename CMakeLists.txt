cmake_minimum_required(VERSION 3.0)

project(Thermostat)

SET(CMAKE_CXX_STANDARD 14)
INCLUDE_DIRECTORIES(${CURRENT_SOURCE_PATH})

LIST(APPEND LIB_SOURCES
    src/thermostat.hpp
    src/thermostat.cpp
    )

LIST(APPEND EXEC_SOURCES
    exec/main.cpp
    )

SET (LIBRARY_NAME ${PROJECT_NAME})
add_library(${LIBRARY_NAME} ${LIB_SOURCES})
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src)

SET (EXECUTABLE_NAME ex_${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} ${EXEC_SOURCES})
TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} ${LIBRARY_NAME})

LIST( APPEND TESTSOURCES
    test/test_thermostat
    )

find_package(Qt5 COMPONENTS Test REQUIRED
    HINTS /usr/local/opt/qt5/lib/cmake/Qt5
    )

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

ENABLE_TESTING()

FIND_PACKAGE(Boost REQUIRED)

FOREACH (test_src ${TESTSOURCES})
    get_filename_component(test_name ${test_src} NAME)
    add_executable(${test_name} ${test_src})
    add_test(${test_name} ${test_name})
    TARGET_INCLUDE_DIRECTORIES(${test_name} PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(${test_name} PRIVATE
        Qt5::Test
        ${LIBRARY_NAME}
        )
ENDFOREACH(test_src)
