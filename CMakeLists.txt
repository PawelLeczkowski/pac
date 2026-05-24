add_library(pac
        pac.c
        queue.c
        caesarCipher.c
)

target_include_directories(pac
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(pac::pac ALIAS pac)
