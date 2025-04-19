// tests/test_type_number.cpp
#include "json.h"
#include <cassert>
#include <iostream>
#include <string>


int main() {
    using json::Number;

    // Test 1: Basic
    {
        Number num("123.45");
        std::string serialized = num.serialize();
        std::string expected = "123.45";
        std::cout << "json::Number: " << serialized << std::endl;
        assert(serialized == expected);
    }

    std::cout << "All tests passed." << std::endl;
    return 0;
}
