# Create a static library target called "jsonpp".
add_library(jsonpp STATIC
        json.cpp
        json.h
)

# Specify include directories for users of the library.
target_include_directories(jsonpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

