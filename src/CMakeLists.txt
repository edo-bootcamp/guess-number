add_library(guess-number
    guess_number.cpp
)

target_include_directories(guess-number
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)