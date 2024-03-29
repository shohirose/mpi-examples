cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(
    fmt
    URL https://github.com/fmtlib/fmt/releases/download/9.1.0/fmt-9.1.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP false
)
FetchContent_MakeAvailable(fmt)

project(mpi-examples CXX)

find_package(MPI REQUIRED)

function(add_example name)
    add_executable(${name} ${ARGN})
    target_link_libraries(${name}
    PUBLIC
        MPI::MPI_CXX
        fmt::fmt-header-only
    )
    target_compile_features(${name}
    PUBLIC
        cxx_std_17
    )
    target_compile_options(${name}
    PUBLIC
        $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
        $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic>
        $<$<CXX_COMPILER_ID:Intel>:$<IF:$<PLATFORM_ID:Windows>,/warn:all,-warn all>>
        $<$<CXX_COMPILER_ID:MSVC>:/W3>
    )
endfunction()

add_example(hello_world hello_world.cpp)
add_example(trapezoid trapezoid.cpp)
add_example(send_recieve send_recieve.cpp)