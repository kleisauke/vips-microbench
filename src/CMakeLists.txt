add_executable(${PROJECT_NAME}-thumbnail thumbnail-bench.cpp)
target_include_directories(${PROJECT_NAME}-thumbnail
        PRIVATE
            ${VIPS_INCLUDE_DIRS}
        )
target_link_libraries(${PROJECT_NAME}-thumbnail
        PRIVATE
            benchmark
            ${VIPS_LDFLAGS}
            ${CMAKE_THREAD_LIBS_INIT}
        )

add_executable(${PROJECT_NAME}-reduce reduce-bench.cpp)
target_include_directories(${PROJECT_NAME}-reduce
        PRIVATE
            ${VIPS_INCLUDE_DIRS}
        )
target_link_libraries(${PROJECT_NAME}-reduce
        PRIVATE
            benchmark
            ${VIPS_LDFLAGS}
            ${CMAKE_THREAD_LIBS_INIT}
        )
