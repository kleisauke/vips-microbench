FetchContent_Declare(cgif
        GIT_REPOSITORY https://github.com/dloebl/cgif.git
        GIT_TAG e3ba2e62613f10c7cac0dc053b86069a668b5beb
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        )

FetchContent_GetProperties(cgif)
if(NOT cgif_POPULATED)
    FetchContent_Populate(cgif)
endif()

add_library(cgif STATIC ${cgif_SOURCE_DIR}/cgif.c ${cgif_SOURCE_DIR}/cgif.h)
target_include_directories(cgif PUBLIC ${cgif_SOURCE_DIR})
