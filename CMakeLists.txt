cmake_minimum_required(VERSION 3.23)
project(tdd_app)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_executable(tdd_app main.cpp soundex/soundex_test.cpp soundex/soundex.cpp soundex/soundex.h collection.cpp roman_converter.cpp roman_converter.h http.cpp portfolio.cpp)


target_link_libraries(
        tdd_app
        gtest_main
        gmock
)

include(GoogleTest GoogleMock
        )


gtest_discover_tests(tdd_app PROPERTIES DISCOVERY_TIMEOUT  30)

