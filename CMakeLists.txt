cmake_minimum_required(VERSION 3.12)
project(networking-game-raylib)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

# Include directories for ENet and INI
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/inih)

# Add ENet library
set(ENET_LIB_PATH ${CMAKE_SOURCE_DIR}/lib)
find_library(ENET_LIBRARY NAMES enet64 PATHS ${ENET_LIB_PATH} REQUIRED)

# Our Project - Client
add_executable(client)
file(GLOB_RECURSE CLIENT_SOURCE_FILES CONFIGURE_DEPENDS src/client/*.c)
target_sources(client PRIVATE ${CLIENT_SOURCE_FILES})
set_target_properties(client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/client)
target_link_libraries(client raylib ${ENET_LIBRARY} ws2_32 winmm)

# Define the source and destination directories for resources
set(RESOURCES_SOURCE_DIR ${CMAKE_SOURCE_DIR}/resources)
set(RESOURCES_DEST_DIR ${CMAKE_BINARY_DIR}/bin/client/resources)

# Add a post-build step to copy the resources
add_custom_command(TARGET client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCES_SOURCE_DIR} ${RESOURCES_DEST_DIR}
)

# Our Project - Server
add_executable(server)
file(GLOB_RECURSE SERVER_SOURCE_FILES CONFIGURE_DEPENDS src/server/*.c third_party/inih/*.c)
target_sources(server PRIVATE ${SERVER_SOURCE_FILES})
set_target_properties(server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/server)
target_link_libraries(server ${ENET_LIBRARY} ws2_32 winmm)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(client PROPERTIES SUFFIX ".html")
    target_link_options(client PUBLIC "-sUSE_GLFW=3")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(client "-framework IOKit")
    target_link_libraries(client "-framework Cocoa")
    target_link_libraries(client "-framework OpenGL")

    target_link_libraries(server "-framework IOKit")
    target_link_libraries(server "-framework Cocoa")
    target_link_libraries(server "-framework OpenGL")
endif()
