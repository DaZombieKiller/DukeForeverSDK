set(TARGET_NAME mss32)
add_library(${TARGET_NAME} INTERFACE)
target_link_libraries(${TARGET_NAME} INTERFACE win32/lib/mss32.lib)
