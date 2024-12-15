cmake_minimum_required(VERSION 3.20.0)

# vcpkg configs
set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
if(NOT DEFINED VCPKG_TARGET_TRIPLET)
	set(VCPKG_TARGET_TRIPLET x64-mingw-static)
endif()

# variables
set(TEST_PROJECT_NAME test)
set(SDL2_LIBS
	$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
	$<IF:$<TARGET_EXISTS:SDL2::SDL2>, SDL2::SDL2, SDL2::SDL2-static>
)

# files
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

# top project declare
project(${TEST_PROJECT_NAME} CXX)

# packages
find_package(SDL2 CONFIG REQUIRED)

# targets
add_executable(${TEST_PROJECT_NAME} ${SRC_FILES})
target_include_directories(${TEST_PROJECT_NAME} SYSTEM BEFORE
	PRIVATE ${SDL2_INCLUDE_DIRS}
)
target_link_libraries(${TEST_PROJECT_NAME} PRIVATE
	${SDL2_LIBS}
)