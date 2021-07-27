FetchContent_Declare(gifenc
        GIT_REPOSITORY https://github.com/lecram/gifenc.git
        GIT_TAG 7d53ea9820af3388a1df1a5b16ed4bcc6f6ef7c7
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        )

FetchContent_GetProperties(gifenc)
if(NOT gifenc_POPULATED)
    FetchContent_Populate(gifenc)
endif()

add_library(gifenc STATIC ${gifenc_SOURCE_DIR}/gifenc.c ${gifenc_SOURCE_DIR}/gifenc.h)
target_include_directories(gifenc PUBLIC ${gifenc_SOURCE_DIR})
