add_executable(${PROJECT_NAME}-exif exif-bench.cpp)
target_include_directories(${PROJECT_NAME}-exif
        PRIVATE
            ${VIPS_INCLUDE_DIRS}
        )
target_link_libraries(${PROJECT_NAME}-exif
        PRIVATE
            benchmark
            ${VIPS_LDFLAGS}
        )

add_executable(${PROJECT_NAME}-thumbnail thumbnail-bench.cpp)
target_include_directories(${PROJECT_NAME}-thumbnail
        PRIVATE
            ${VIPS_INCLUDE_DIRS}
        )
target_link_libraries(${PROJECT_NAME}-thumbnail
        PRIVATE
            benchmark
            ${VIPS_LDFLAGS}
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
        )

add_executable(${PROJECT_NAME}-jpeg jpeg-bench.cpp)
target_include_directories(${PROJECT_NAME}-jpeg
        PRIVATE
            ${VIPS_INCLUDE_DIRS}
        )
target_link_libraries(${PROJECT_NAME}-jpeg
        PRIVATE
            benchmark
            ${VIPS_LDFLAGS}
        )

add_executable(${PROJECT_NAME}-gifsave gifsave-bench.cpp)
target_link_libraries(${PROJECT_NAME}-gifsave
        PRIVATE
            benchmark
            cgif
            gifenc
        )
