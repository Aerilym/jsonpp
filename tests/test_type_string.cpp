// tests/test_type_string.cpp
#include "json.h"
#include <cassert>
#include <iostream>
#include <string>


int main() {
    using json::String;

    // Test 1: Basic
    {
        String s("Hello");
        std::string serialized = s.serialize();
        std::string expected = "\"Hello\"";
        std::cout << "json::String: " << serialized << std::endl;
        assert(serialized == expected);
    }

    std::cout << "All tests passed." << std::endl;
    return 0;
}
