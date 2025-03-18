cmake_minimum_required(VERSION 3.10)
project(GTKTutorial)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Set MSYS2 paths
set(MSYS2_PATH "C:/msys64")
set(ENV{PKG_CONFIG_PATH} "${MSYS2_PATH}/mingw64/lib/pkgconfig")

# Find PkgConfig
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED IMPORTED_TARGET gtk+-3.0)

# Add executable
add_executable(app main.c)
set_target_properties(app PROPERTIES WIN32_EXECUTABLE true)

# Link against GTK3
target_link_libraries(app PRIVATE PkgConfig::GTK3)