// tests/test_type_object.cpp
#include "json.h"
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>


int main() {
    using json::String;
    using json::Number;
    using json::Boolean;
    using json::Array;
    using json::Object;
    using json::Value;

    // Test 1: Basic
    {
        std::map<std::string, Value> objMap;
        objMap["key1"] = String("Value1");
        objMap["key2"] = Number("789");
        objMap["flag"] = Boolean(false);

        std::vector<Value> arr;
        arr.push_back(String("Item1"));
        arr.push_back(Number("10"));
        Array jsonArr(arr);
        objMap["list"] = jsonArr;

        Object obj(objMap);
        std::string serialized = obj.serialize();
        // Keys in a std::map are sorted lexicographically.
        std::string expected = "{\"flag\": false, \"key1\": \"Value1\", \"key2\": 789, \"list\": [\"Item1\", 10]}";
        std::cout << "JSONObject: " << serialized << std::endl;
        assert(serialized == expected);
    }

    std::cout << "All tests passed." << std::endl;
    return 0;
}
