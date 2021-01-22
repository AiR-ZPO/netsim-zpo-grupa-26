cmake_minimum_required(VERSION 3.13)
project(net_simulation)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Werror=switch)

include_directories(include)

# FIXME: Uzupełnij.
set(SOURCE_FILES
        src/factory.cpp
        src/helpers.cpp
        src/nodes.cpp
        src/package.cpp
        src/reports.cpp
        src/simulation.cpp
        src/storage_types.cpp
        src/types.cpp
        )
add_executable(net_sim ${SOURCE_FILES} main.cpp)


set(SOURCES_FILES_TESTS
        test/net_test.cpp
        test/test_package.cpp
        test/test_nodes.cpp
        #test/test_Factory.cpp
        )

# Dodaj konfigurację typu `Test`.
add_executable(net_test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)

# Dodaj katalogi z plikami nagłówkowymi wyłącznie do konkretnej konfiguracji (tu: `Test`).
target_include_directories(net_test PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        mocks
        )

# Dodaj podkatalog `googletest-master`.
add_subdirectory(googletest-master)

# Podlinkuj bibliotekę o identyfikatorze `gmock` (w pliku CMake) wyłącznie do konkretnej
# konfiguracji (tu: `Test`).
target_link_libraries(net_test gmock)