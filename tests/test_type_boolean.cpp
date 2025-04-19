// tests/test_type_boolean.cpp
#include "json.h"
#include <cassert>
#include <iostream>
#include <string>


int main() {
    using json::Boolean;

    // Test 1: Basic
    {
        Boolean t(true);
        Boolean f(false);
        std::string serializedTrue = t.serialize();
        std::string serializedFalse = f.serialize();
        std::cout << "json::Boolean (true): " << serializedTrue << std::endl;
        std::cout << "json::Boolean (false): " << serializedFalse << std::endl;
        assert(serializedTrue == "true");
        assert(serializedFalse == "false");
    }

    std::cout << "All tests passed." << std::endl;
    return 0;
}
