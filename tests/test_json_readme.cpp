// tests/test_json_readme.cpp
#include "json.h"
#include <iostream>
#include <string>

int main() {
    // Test 1: First readme example. (Parsing)
    {
        // Parse a json string.
        std::string jsonString = "{\"key1\": \"value1\", \"key2\": [1, 2, 3]}";
        json::Object jsonObject = json::parse(jsonString);

        // Access the value of a key.
        auto value1 = jsonObject.get("key1");
        auto value2 = jsonObject["key2"];
    }

    // Test 2: Second readme example. (Set JSON)
    {
        // Set JSON values in a json object.
        json::Object jsonObject;

        // Set a key to a string
        jsonObject.set("key1", json::String("potato"));
        jsonObject.set("key1", "potato");
        jsonObject["key1"] = json::String("potato");
        auto potato = jsonObject["key1"];

        // Set a key to a bool
        jsonObject.set("key2", json::Boolean(true));
        jsonObject.set("key2", true);
    }

    // Test 3: Arrays
    {
        // Arrays
        json::Array jsonArray1;
        jsonArray1.set(0, json::String("potato"));
        jsonArray1.set(0, json::String("potato"));
        jsonArray1.set(0, json::Boolean(true));
        jsonArray1[0] = json::String("potato");
        jsonArray1[0] = json::String("potato");
        auto item1 = jsonArray1[0];

        json::Array jsonArray2(std::vector<json::Value> {json::String("potato"), json::Boolean(true)});
        auto item2 = jsonArray2[1];
        jsonArray2.set(1, json::String("potato"));
        jsonArray2.set(1, json::Boolean(true));
        auto item3 = jsonArray2[1];
    }

    std::cout << "All JSON parsing tests passed." << std::endl;
    return 0;
}
