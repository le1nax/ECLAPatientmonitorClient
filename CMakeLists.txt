# If someone uses a lower version of CMake building this fails.
cmake_minimum_required (VERSION 3.5)

include(FindPkgConfig)

set(CMAKE_TOOLCHAIN_FILE "C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_LIBRARY_PATH "C:/Program Files/MATLAB/R2023b/extern/lib/win64/mingw64")

set(Matlab_ROOT_DIR "C:/Program Files/MATLAB/R2023b" CACHE PATH "Path to MATLAB installation")

set(VCPKG_TARGET_TRIPLET "x64-mingw-static")
set(VCPKG_HOST_TRIPLET "x64-mingw-static")

# C++ standard to use.
set(CXX_STANDARD 17)

#set module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# Name of your project.
project(BasicGui CXX)
message("Generating project ${CMAKE_PROJECT_NAME} ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
message("modulepath: ${CMAKE_MODULE_PATH}")
# find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)
find_package(Threads REQUIRED)
find_package(pcanbasic REQUIRED) 
find_package(OpenGL)
find_package(Matlab REQUIRED)
include_directories(${Matlab_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCE_FILES "source/*.cpp" "PCANModule/*.cpp")
add_executable(ECLA_PM "main.cpp" ${SOURCE_FILES})
# pkg_check_modules(DEPS REQUIRED sigc++-3.0) 
# include_directories(${DEPS_INCLUDE_DIRS})
# target_link_libraries(yourprogram ${DEPS_LIBRARIES})
target_include_directories(ECLA_PM PRIVATE ${pcanbasic_INCLUDE_DIR})
# target_include_directories(ECLA_PM PRIVATE "C:/Program Files/MATLAB/R2020b/extern/include")
# link_directories("C:/Program Files/MATLAB/R2020b/extern/lib/win64/mingw64")

if (imgui_FOUND)
  target_link_libraries(ECLA_PM ${OPENGL_gl_LIBRARY}
                                ${Matlab_MX_LIBRARY} ${Matlab_MAT_LIBRARY}
                                # "C:/Program Files/MATLAB/R2023b/extern/lib/win64/microsoft/libmat.lib"
                               pcanbasic::pcanbasic
                               imgui::imgui
                               implot::implot
                               glfw 
                               Threads::Threads
                               ws2_32 
                              -pthread)
else()
  message(FATAL_ERROR "imgui library not found.")
endif()

set(CMAKE_INSTALL_RPATH "$ORIGIN") # Sets the RPATH to search for DLLs in the same directory as the executable.
