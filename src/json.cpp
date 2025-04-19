#include "json.h"

#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

std::string json::String::serialize() {
    return "\"" + data + "\"";
}

std::string json::Number::serialize() {
    return data;
}

std::string json::Boolean::serialize() {
    return data ? "true" : "false";
}

std::string json::Array::serialize() {
    std::string result = "[";
    for (auto it = data.begin(); it != data.end(); ++it) {
        result += std::visit([](auto&& value) -> std::string {
            return value.serialize();
        }, *it);
        if (std::next(it) != data.end()) {
            result += ", ";
        }
    }
    result += "]";
    return result;
}

std::string json::Object::serialize() {
    std::string result = "{";
    for (auto it = data.begin(); it != data.end(); ++it) {
        result += "\"" + it->first + "\": " + std::visit([](auto&& value) -> std::string {
            return value.serialize();
        }, it->second);
        if (std::next(it) != data.end()) {
            result += ", ";
        }
    }
    result += "}";
    return result;
}

// --- JSON Parsing implementation ---
// This function parses a JSON string and returns a JSONObject.
// It uses a recursive descent approach.
json::Object json::parse(const std::string& json) {
    size_t pos = 0;

    // Helper: Skip over whitespace.
    auto skipWhitespace = [&]() {
        while (pos < json.size() && std::isspace(json[pos])) {
            pos++;
        }
    };

    // A recursive lambda to parse any JSON value.
    std::function<Value()> parseValue = [&]() -> Value {
        skipWhitespace();
        if (pos >= json.size()) {
            throw std::runtime_error("Unexpected end of input");
        }
        char ch = json[pos];
        if (ch == '"') {
            // Parse a JSON string.
            pos++; // Skip the opening quote.
            std::string result;
            while (pos < json.size() && json[pos] != '"') {
                if (json[pos] == '\\') {
                    pos++;
                    if (pos >= json.size()) {
                        throw std::runtime_error("Unexpected end in escape sequence");
                    }
                    char esc = json[pos];
                    switch (esc) {
                    case '"': result.push_back('"');
                        break;
                    case '\\': result.push_back('\\');
                        break;
                    case '/': result.push_back('/');
                        break;
                    case 'b': result.push_back('\b');
                        break;
                    case 'f': result.push_back('\f');
                        break;
                    case 'n': result.push_back('\n');
                        break;
                    case 'r': result.push_back('\r');
                        break;
                    case 't': result.push_back('\t');
                        break;
                    default: result.push_back(esc);
                        break;
                    }
                } else {
                    result.push_back(json[pos]);
                }
                pos++;
            }
            if (pos >= json.size() || json[pos] != '"') {
                throw std::runtime_error("Unterminated string literal");
            }
            pos++; // Skip the closing quote.
            return String(result);
        } else if (ch == '{') {
            // Parse a JSON object.
            pos++; // Skip '{'
            std::map<std::string, Value> obj;
            skipWhitespace();
            if (pos < json.size() && json[pos] == '}') {
                pos++; // Empty object.
                return Object(obj);
            }
            while (true) {
                skipWhitespace();
                if (pos >= json.size() || json[pos] != '"') {
                    throw std::runtime_error("Expected key string in object");
                }
                // Parse key string.
                pos++; // Skip opening quote.
                std::string key;
                while (pos < json.size() && json[pos] != '"') {
                    if (json[pos] == '\\') {
                        pos++;
                        if (pos >= json.size()) {
                            throw std::runtime_error("Unexpected end in key escape sequence");
                        }
                        char esc = json[pos];
                        switch (esc) {
                        case '"': key.push_back('"');
                            break;
                        case '\\': key.push_back('\\');
                            break;
                        case '/': key.push_back('/');
                            break;
                        case 'b': key.push_back('\b');
                            break;
                        case 'f': key.push_back('\f');
                            break;
                        case 'n': key.push_back('\n');
                            break;
                        case 'r': key.push_back('\r');
                            break;
                        case 't': key.push_back('\t');
                            break;
                        default: key.push_back(esc);
                            break;
                        }
                    } else {
                        key.push_back(json[pos]);
                    }
                    pos++;
                }
                if (pos >= json.size() || json[pos] != '"') {
                    throw std::runtime_error("Unterminated key string");
                }
                pos++; // Skip closing quote.
                skipWhitespace();
                if (pos >= json.size() || json[pos] != ':') {
                    throw std::runtime_error("Expected ':' after key");
                }
                pos++; // Skip ':'.
                // Parse the value for this key.
                Value val = parseValue();
                obj[key] = val;
                skipWhitespace();
                if (pos < json.size() && json[pos] == '}') {
                    pos++; // End of object.
                    break;
                }
                if (pos >= json.size() || json[pos] != ',') {
                    throw std::runtime_error("Expected ',' between object key/value pairs");
                }
                pos++; // Skip comma.
            }
            return Object(obj);
        } else if (ch == '[') {
            // Parse a JSON array.
            pos++; // Skip '['.
            std::vector<Value> arr;
            skipWhitespace();
            if (pos < json.size() && json[pos] == ']') {
                pos++; // Empty array.
                return Array(arr);
            }
            while (true) {
                Value element = parseValue();
                arr.push_back(element);
                skipWhitespace();
                if (pos < json.size() && json[pos] == ']') {
                    pos++; // End of array.
                    break;
                }
                if (pos >= json.size() || json[pos] != ',') {
                    throw std::runtime_error("Expected ',' between array elements");
                }
                pos++; // Skip comma.
                skipWhitespace();
            }
            return Array(arr);
        } else if (std::isdigit(ch) || ch == '-' || ch == '+') {
            // Parse a number.
            size_t start = pos;
            while (pos < json.size() && (std::isdigit(json[pos]) || json[pos] == '.' ||
                json[pos] == 'e' || json[pos] == 'E' ||
                json[pos] == '+' || json[pos] == '-')) {
                pos++;
            }
            std::string numStr = json.substr(start, pos - start);
            return Number(numStr);
        } else if (json.compare(pos, 4, "true") == 0) {
            pos += 4;
            return Boolean(true);
        } else if (json.compare(pos, 5, "false") == 0) {
            pos += 5;
            return Boolean(false);
        } else {
            throw std::runtime_error("Unexpected token in JSON input");
        }
    };

    skipWhitespace();
    if (pos >= json.size() || json[pos] != '{') {
        throw std::runtime_error("JSON input must start with an object '{'");
    }
    // Parse the root value.
    Value root = parseValue();
    // Ensure that the root value is a JSON object.
    try {
        return std::get<Object>(root);
    } catch (const std::bad_variant_access&) {
        throw std::runtime_error("Parsed JSON root is not an object");
    }
}

// ARRAYS
// Read-only access via operator[] (throws if index out of range).
json::Value& json::Array::operator[](size_t index) {
    if (index >= data.size()) {
        throw std::out_of_range("JSONArray index out of range");
    }
    return data[index];
}

const json::Value& json::Array::operator[](size_t index) const {
    if (index >= data.size()) {
        throw std::out_of_range("JSONArray index out of range");
    }
    return data[index];
}

// A setter method that extends the vector if needed.
void json::Array::set(size_t index, const json::Value& value) {
    if (index >= data.size()) {
        // Resize vector to index+1, default-constructing new elements.
        data.resize(index + 1);
    }
    data[index] = value;
}

// Optional: A push_back method to add elements at the end.
void json::Array::push_back(const Value& value) {
    data.push_back(value);
}

// Optional: Get the size of the array.
size_t json::Array::size() const {
    return data.size();
}

// OBJECTS

json::Value json::Object::get(const std::string& key) {
    return data.at(key);
}

// Setter with x.set(key, value) syntax.
json::Value json::Object::set(const std::string& key, const Value& value) {
    return data[key] = value;
}

json::Value json::Object::set(const std::string& key, const std::string& value) {
    return data[key] = String(value);
}

// Getter/Setter with x[i] syntax.
json::Value& json::Object::operator[](const std::string& key) {
    return data[key];
}

// Const version for read-only access.
const json::Value& json::Object::operator[](const std::string& key) const {
    return data.at(key);
}
