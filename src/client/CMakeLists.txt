file(GLOB_RECURSE CLIENT_SOURCE_FILES CONFIGURE_DEPENDS *.c)

add_executable(client ${CLIENT_SOURCE_FILES})
set_target_properties(client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/client)

target_link_libraries(client raylib ${ENET_LIBRARY} ws2_32 winmm)
