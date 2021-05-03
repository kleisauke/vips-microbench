FetchContent_Declare(benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.5.3
        )

# Do not build the tests
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)

# CMake target: benchmark
FetchContent_MakeAvailable(benchmark)
