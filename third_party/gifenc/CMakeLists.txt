FetchContent_Declare(gifenc
        GIT_REPOSITORY https://github.com/lecram/gifenc.git
        GIT_TAG 87acd487dfa2f2a638eec751a1d6c2fff60822da
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        )

FetchContent_GetProperties(gifenc)
if(NOT gifenc_POPULATED)
    FetchContent_Populate(gifenc)
endif()

add_library(gifenc STATIC ${gifenc_SOURCE_DIR}/gifenc.c ${gifenc_SOURCE_DIR}/gifenc.h)
target_include_directories(gifenc PUBLIC ${gifenc_SOURCE_DIR})
