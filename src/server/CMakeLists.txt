file(GLOB_RECURSE SERVER_SOURCE_FILES CONFIGURE_DEPENDS *.c)

add_executable(server ${SERVER_SOURCE_FILES})
set_target_properties(server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/server)

target_link_libraries(server ${ENET_LIBRARY} ws2_32 winmm)
