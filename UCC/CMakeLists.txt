set(TARGET_NAME UCC)
file(GLOB SOURCE_FILES CONFIGURE_DEPENDS Src/*.cpp)
add_executable(${TARGET_NAME} ${SOURCE_FILES} ../Core/Src/UnMisc.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE BugHandler ComCtl32 dnCommon Engine)
