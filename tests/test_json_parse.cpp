// tests/test_json_parse.cpp
#include "json.h"
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>


int main() {
    using namespace json;
    // Test 1: Simple JSON object.
    {
        std::string input = "{\"name\": \"John\", \"age\": 30, \"isStudent\": false}";
        Object obj = parse(input);
        std::string serialized = obj.serialize();
        // Lexicographically sorted keys: "age", "isStudent", "name"
        std::string expected = "{\"age\": 30, \"isStudent\": false, \"name\": \"John\"}";
        std::cout << "Parse Test 1: " << serialized << std::endl;
        assert(serialized == expected);
    }

    // Test 2: Nested JSON object.
    {
        std::string input = "{\"person\": {\"name\": \"Alice\", \"age\": 25}}";
        Object obj = parse(input);
        std::string serialized = obj.serialize();
        // The inner object sorts keys: "age", "name"
        std::string expected = "{\"person\": {\"age\": 25, \"name\": \"Alice\"}}";
        std::cout << "Parse Test 2: " << serialized << std::endl;
        assert(serialized == expected);
    }

    // Test 3: JSON object with an array.
    {
        std::string input = "{\"fruits\": [\"apple\", \"banana\", \"cherry\"]}";
        Object obj = parse(input);
        std::string serialized = obj.serialize();
        std::string expected = "{\"fruits\": [\"apple\", \"banana\", \"cherry\"]}";
        std::cout << "Parse Test 3: " << serialized << std::endl;
        assert(serialized == expected);
    }

    // Test 4: Complex nested structure (array with mixed types).
    {
        std::string input = "{\"data\": [1, {\"nested\": true}, [\"a\", \"b\"]]}";
        Object obj = parse(input);
        std::string serialized = obj.serialize();
        // Expected string with the same structure. (Keys are sorted in the nested object.)
        std::string expected = "{\"data\": [1, {\"nested\": true}, [\"a\", \"b\"]]}";
        std::cout << "Parse Test 4: " << serialized << std::endl;
        assert(serialized == expected);
    }

    // Test 5: JSON with string escapes.
    {
        std::string input = "{\"message\": \"Hello\\nWorld\\t!\"}";
        Object obj = parse(input);
        std::string serialized = obj.serialize();
        // The parser produces a JSONString containing actual newline and tab characters.
        std::string expected = "{\"message\": \"Hello\nWorld\t!\"}";
        std::cout << "Parse Test 5: " << serialized << std::endl;
        assert(serialized == expected);
    }

    // Test 6: Error case - missing closing brace.
    {
        bool exceptionThrown = false;
        try {
            std::string input = "{\"key\": \"value\"";
            Object obj = parse(input);
        } catch (const std::runtime_error &e) {
            std::cout << "Parse Test 6: Caught expected exception: " << e.what() << std::endl;
            exceptionThrown = true;
        }
        assert(exceptionThrown);
    }

    // Test 7: Error case - invalid token.
    {
        bool exceptionThrown = false;
        try {
            std::string input = "{\"key\": invalid}";
            Object obj = parse(input);
        } catch (const std::runtime_error &e) {
            std::cout << "Parse Test 7: Caught expected exception: " << e.what() << std::endl;
            exceptionThrown = true;
        }
        assert(exceptionThrown);
    }

    std::cout << "All JSON parsing tests passed." << std::endl;
    return 0;
}
