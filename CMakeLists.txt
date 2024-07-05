cmake_minimum_required(VERSION 3.15)
project(Buckeye)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/System)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_compile_definitions(
    $<$<COMPILE_LANGUAGE:C,CXX>:UNICODE>
    $<$<COMPILE_LANGUAGE:C,CXX>:_UNICODE>
    $<$<COMPILE_LANGUAGE:C,CXX>:_CRT_NO_VA_START_VALIDATION>
    $<$<COMPILE_LANGUAGE:C,CXX>:_CRT_SECURE_NO_WARNINGS>
    $<$<COMPILE_LANGUAGE:C,CXX>:WINDOWS_IGNORE_PACKING_MISMATCH>)

add_compile_options(
    $<$<COMPILE_LANGUAGE:C,CXX>:/vmg>
    $<$<COMPILE_LANGUAGE:C,CXX>:/vmv>
    $<$<COMPILE_LANGUAGE:C,CXX>:/Zp4>)

add_subdirectory(3DRDebugLib)
add_subdirectory(BugHandler)
add_subdirectory(D3DDrv9)
add_subdirectory(dnAI)
add_subdirectory(dnAnimation)
add_subdirectory(dnCommon)
add_subdirectory(dnGame)
add_subdirectory(dnVehicles)
add_subdirectory(Editor)
add_subdirectory(Engine)
add_subdirectory(Fire)
add_subdirectory(MilesAudio)
add_subdirectory(NullRenDev)
add_subdirectory(UCC)
add_subdirectory(UWindow)
