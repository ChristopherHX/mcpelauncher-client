set(CPACK_PACKAGE_NAME "mcpelauncher-client")
set(CPACK_PACKAGE_VENDOR "mcpelauncher")
set(CPACK_PACKAGE_VERSION "${MANIFEST_GIT_COMMIT_HASH}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A launcher for Minecraft: Pocket Edition")
set(CPACK_PACKAGE_CONTACT "https://github.com/minecraft-linux/mcpelauncher-manifest/issues")
set(CPACK_GENERATOR "TGZ;DEB")
if(NOT DEFINED CPACK_DEBIAN_PACKAGE_ARCHITECTURE)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm" OR CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
        set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE armhf)
    else()
        set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE i386)
    endif()
endif()
set(CPACK_DEBIAN_PACKAGE_VERSION "${BUILD_TIMESTAMP}-${MANIFEST_GIT_COMMIT_HASH}")

set(CPACK_INSTALL_CMAKE_PROJECTS
        "${CMAKE_BINARY_DIR};gamepad-mappings;gamepad-mappings;/"
        "${CMAKE_CURRENT_BINARY_DIR};mcpelauncher-client;mcpelauncher-client;/")
set(CPACK_OUTPUT_CONFIG_FILE CPackConfig.cmake)
if(DEFINED CPACK_DEBIAN_PACKAGE_DEPENDS)
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_DEBIAN_PACKAGE_DEPENDS}, ")
endif()
set(CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_DEBIAN_PACKAGE_DEPENDS}mcpelauncher-core")
if (DEB_OS_NAME MATCHES "ubuntu-xenial")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_DEBIAN_PACKAGE_DEPENDS}, libc6 (>=2.14), libstdc++6, libcurl3, libx11-6, zlib1g, libpng12-0, libevdev2, libudev1")
    set(CPACK_DEBIAN_PACKAGE_RECOMMENDS "libegl1-mesa, libegl1-mesa-drivers, libasound, pulseaudio")
    set(CPACK_DEBIAN_PACKAGE_VERSION "${CPACK_DEBIAN_PACKAGE_VERSION}~xenial")
elseif(DEB_OS_NAME MATCHES "ubuntu-bionic")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_DEBIAN_PACKAGE_DEPENDS}, libc6 (>=2.14), libstdc++6, libcurl4, libx11-6, zlib1g, libpng16-16, libevdev2, libudev1, libegl1")
    set(CPACK_DEBIAN_PACKAGE_RECOMMENDS "libegl1, libgl1-mesa-dri, libasound, pulseaudio")
elseif(DEB_OS_NAME MATCHES "ubuntu-disco")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_DEBIAN_PACKAGE_DEPENDS}, libc6 (>=2.14), libstdc++6, libcurl4, libx11-6, zlib1g, libpng16-16, libevdev2, libudev1, libegl1")
    set(CPACK_DEBIAN_PACKAGE_RECOMMENDS "libegl1, libgl1-mesa-dri, libasound, pulseaudio")
    set(CPACK_DEBIAN_PACKAGE_VERSION "${CPACK_DEBIAN_PACKAGE_VERSION}~disco")
endif()

include(CPack)
