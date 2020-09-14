cmake_minimum_required(VERSION 3.8)
project(mpi-examples CXX)

find_package(MPI REQUIRED)

function(add_example name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name}
    PRIVATE
        MPI::MPI_CXX
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
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
    )
endfunction()

add_example(hello_world)
add_example(trapezoid)
add_example(send_recieve)