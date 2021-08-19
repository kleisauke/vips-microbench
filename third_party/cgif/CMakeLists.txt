FetchContent_Declare(cgif
        GIT_REPOSITORY https://github.com/dloebl/cgif.git
        GIT_TAG 8803d06b14dc5f85a5457898b41cd989722d52cc
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        )

FetchContent_GetProperties(cgif)
if(NOT cgif_POPULATED)
    FetchContent_Populate(cgif)
endif()

add_library(cgif STATIC ${cgif_SOURCE_DIR}/cgif.c ${cgif_SOURCE_DIR}/cgif.h)
target_include_directories(cgif PUBLIC ${cgif_SOURCE_DIR})
