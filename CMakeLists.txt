cmake_minimum_required(VERSION 3.10)
project(GTKTutorial)

set(CMAKE_C_STANDARD 11)

# Set MSYS2 paths
set(MSYS2_PATH "C:/msys64")
set(ENV{PKG_CONFIG_PATH} "${MSYS2_PATH}/mingw64/lib/pkgconfig")

# Find PkgConfig
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED IMPORTED_TARGET gtk+-3.0)

# Add source files dynamically
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c # Include main.c here
)

# Add executable
add_executable(app ${SRC_FILES})

# Link against GTK3
target_link_libraries(app PRIVATE PkgConfig::GTK3)

# Add include directories
target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/modules
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

# Ensure the application is linked as a console app
set_target_properties(app PROPERTIES
    LINK_FLAGS "-mwindows"  # This flag is necessary to link a GUI app on Windows
)
