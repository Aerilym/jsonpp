enable_testing()

set(TEST_SOURCES
        test_json.cpp
        test_type_boolean.cpp
        test_type_number.cpp
        test_type_string.cpp
        test_type_array.cpp
        test_type_object.cpp
        test_json_parse.cpp
        test_json_readme.cpp
)

# Loop over each test source file.
foreach(test_src IN LISTS TEST_SOURCES)
    # Extract the test name (without extension).
    get_filename_component(test_name ${test_src} NAME_WE)

    # Create an executable for the test.
    add_executable(${test_name} ${test_src})
    target_link_libraries(${test_name} PRIVATE jsonpp)

    # Register the test with CTest.
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
