// tests/test_type_array.cpp
#include "json.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>


int main() {
    using json::String;
    using json::Number;
    using json::Boolean;
    using json::Array;
    using json::Value;

    // Test 1: Basic
    {
        std::vector<Value> arr;
        arr.push_back(String("A"));
        arr.push_back(Number("456"));
        arr.push_back(Boolean(true));

        std::vector<Value> inner;
        inner.push_back(String("Inner"));
        Array innerArray(inner);
        arr.push_back(innerArray);

        Array jsonArr(arr);
        std::string serialized = jsonArr.serialize();
        std::string expected = "[\"A\", 456, true, [\"Inner\"]]";
        std::cout << "JSONArray: " << serialized << std::endl;
        assert(serialized == expected);
    }

    std::cout << "All tests passed." << std::endl;
    return 0;
}
