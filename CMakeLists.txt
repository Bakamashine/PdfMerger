cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Set some basic project attributes
project (PdfMerger 
	VERSION 0.1
	DESCRIPTION "Project for automation merging pdf")

find_package(PoDofo 1.1.1 REQUIRED)
message(STATUS "Found PoDoFo: ${PoDoFo_VERSION}")

# This project will output an executable file
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} podofo::podofo)

# Install: executable + runtime dependencies (DLLs) into a clean directory.
include(InstallRequiredSystemLibraries)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
