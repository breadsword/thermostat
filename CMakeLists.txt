cmake_minimum_required(VERSION 3.0)

project(Thermostat)

SET(CMAKE_CXX_STANDARD 14)
INCLUDE_DIRECTORIES(${CURRENT_SOURCE_PATH})

LIST(APPEND LIB_SOURCES
    temperature_controller.hpp
    temperature_controller.cpp
    )

LIST(APPEND EXEC_SOURCES
    main.cpp
    )

SET (LIBRARY_NAME ${PROJECT_NAME})
add_library(${LIBRARY_NAME} ${LIB_SOURCES})
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

SET (EXECUTABLE_NAME ex_${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} ${EXEC_SOURCES})
TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} ${LIBRARY_NAME})

LIST( APPEND TESTSOURCES
    test_temperature_controller
    )

find_package(Qt5 COMPONENTS Test REQUIRED
    HINTS /usr/local/opt/qt5/lib/cmake/Qt5
    )

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

ENABLE_TESTING()

FIND_PACKAGE(Boost REQUIRED)

FOREACH (test ${TESTSOURCES})
    add_executable(${test} ${test})
    add_test(${test} ${test})
    TARGET_INCLUDE_DIRECTORIES(${test} PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(${test} PRIVATE
        Qt5::Test
        ${LIBRARY_NAME}
        )
ENDFOREACH(test)
