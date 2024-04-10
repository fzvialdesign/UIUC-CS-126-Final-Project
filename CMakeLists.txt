cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
project(final-project)

# This tells the compiler to not aggressively optimize and
# to include debugging information so that the debugger
# can properly read what's going on.
set(CMAKE_BUILD_TYPE Debug)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

# Let's nicely support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Warning flags
if(MSVC)
    # warning level 3 and all warnings as errors
    add_compile_options(/W3 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wpedantic -Werror)
endif()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.11.1
)

# Adds Catch2 testing library
FetchContent_GetProperties(catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_library(catch2 INTERFACE)
    target_include_directories(catch2 INTERFACE ${catch2_SOURCE_DIR}/single_include)
endif()

get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE)
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE)

include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")

list(APPEND ENTITIES_SOURCE_FILES       src/entities/enemy.cc
                                        src/entities/player.cc)

list(APPEND ITEMS_SOURCE_FILES          src/items/weapon.cc)

list(APPEND MAP_SOURCE_FILES            src/map/door.cc
                                        src/map/room.cc
                                        src/map/dungeon.cc)

list(APPEND MECHANICS_SOURCE_FILES      src/mechanics/engine.cc)

list(APPEND SOURCE_FILES                ${ENTITIES_SOURCE_FILES}
                                        ${ITEMS_SOURCE_FILES}
                                        ${MAP_SOURCE_FILES}
                                        ${MECHANICS_SOURCE_FILES})

list(APPEND ENTITIES_TEST_FILES         tests/entities/test_enemy.cc
                                        tests/entities/test_player.cc)

list(APPEND ITEMS_TEST_FILES            tests/items/test_weapon.cc)

list(APPEND MAP_TEST_FILES              tests/map/test_door.cc
                                        tests/map/test_room.cc
                                        tests/map/test_dungeon.cc)

list(APPEND MECHANICS_TEST_FILES        tests/mechanics/test_engine.cc)

list(APPEND TEST_FILES                  ${ENTITIES_TEST_FILES}
                                        ${ITEMS_TEST_FILES}
                                        ${MAP_TEST_FILES}
                                        ${MECHANICS_TEST_FILES})

ci_make_app(
        APP_NAME        start-game
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         apps/cinder_app_main.cc ${SOURCE_FILES}
                        src/adventure_app.cc src/visualizer.cc
        INCLUDES        include
)

ci_make_app(
        APP_NAME        test-game
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         tests/test_main.cc ${SOURCE_FILES} ${TEST_FILES}
        INCLUDES        include
        LIBRARIES       catch2
)

if(MSVC)
    set_property(TARGET test-game APPEND_STRING PROPERTY LINK_FLAGS "
    /SUBSYSTEM:CONSOLE")
endif()