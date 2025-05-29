include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://codeload.github.com/google/googletest/zip/refs/heads/main
  DOWNLOAD_EXTRACT_TIMESTAMP False
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(ut Test.cpp)

target_link_libraries(ut
    PRIVATE
    guess-number
    gmock_main
)

enable_testing()
include(GoogleTest)
gtest_discover_tests(ut)
