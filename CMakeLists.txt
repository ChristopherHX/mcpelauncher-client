cmake_minimum_required (VERSION 2.6)

project(mcpelauncher-client LANGUAGES CXX ASM)

find_package(PNG)

git_commit_hash(${CMAKE_CURRENT_SOURCE_DIR} CLIENT_GIT_COMMIT_HASH)
configure_file(src/build_info.h.in ${CMAKE_CURRENT_BINARY_DIR}/build_info/build_info.h)

add_executable(mcpelauncher-client src/main.cpp src/JNIBinding.cpp src/window_callbacks.cpp src/window_callbacks.h src/utf8_util.h)
target_link_libraries(mcpelauncher-client jnivm logger mcpelauncher-core gamewindow argparser)
target_include_directories(mcpelauncher-client PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/build_info/)

if (APPLE)
    set_target_properties(mcpelauncher-client PROPERTIES MACOSX_RPATH TRUE INSTALL_RPATH @executable_path/../Frameworks)
endif()

if (IS_ARMHF_BUILD)
    target_sources(mcpelauncher-client PRIVATE src/armhf_support.cpp src/armhf_support.h)
    target_compile_definitions(mcpelauncher-client PRIVATE USE_ARMHF_SUPPORT)
else()
    target_sources(mcpelauncher-client PRIVATE src/cpuid.cpp src/cpuid.h)
endif()

if (PNG_FOUND)
    target_compile_definitions(mcpelauncher-client PRIVATE HAS_LIBPNG)
    target_include_directories(mcpelauncher-client PRIVATE ${PNG_INCLUDE_DIRS})
    target_link_libraries(mcpelauncher-client ${PNG_LIBRARIES})
endif()

install(TARGETS mcpelauncher-client RUNTIME COMPONENT mcpelauncher-client DESTINATION bin)
include(CPackSettings.cmake)