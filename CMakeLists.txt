cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Allow headers in root directory
include_directories(${CMAKE_SOURCE_DIR})

# Put executables into build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Find all .cpp files two levels deep
file(GLOB_RECURSE EXAMPLE_SRCS
    CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/*/*/*.cpp")

# For each src file, generate an executable
foreach(src IN LISTS EXAMPLE_SRCS)
    # Path relative to project root
    file(RELATIVE_PATH rel "${CMAKE_SOURCE_DIR}" "${src}")

    # Strip .cpp extension
    string(REPLACE ".cpp" "" noext "${rel}")

    # Replace "/" with "_"
    string(REPLACE "/" "_" target "${noext}")

    # Declare executable
    add_executable(${target} "${src}")

    # Headers in the same folder
    get_filename_component(srcdir "${src}" PATH)
    get_filename_component(parentdir "${srcdir}" DIRECTORY)
    target_include_directories(${target}
        PRIVATE
            "${srcdir}"
            "${parentdir}"
    )
endforeach()