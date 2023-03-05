cmake_minimum_required(VERSION 3.13)

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
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name}
    PRIVATE
        MPI::MPI_CXX
        fmt::fmt
    )
    target_compile_features(${name}
    PRIVATE
        cxx_std_17
    )
    target_compile_options(${name}
    PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
        $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic>
        $<$<CXX_COMPILER_ID:Intel>:$<IF:$<PLATFORM_ID:Windows>,/warn:all,-warn all>>
        $<$<CXX_COMPILER_ID:MSVC>:/W3>
    )
endfunction()

add_example(hello_world)
add_example(trapezoid)
add_example(send_recieve)