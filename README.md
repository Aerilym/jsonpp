# JSONPP

JSONPP (JSON++ or JSON Parser Parser) is a C++ library for parsing and generating JSON. All json data types are supported,
including nested objects arrays.

This library is **not (yet)** fully compliant
with [ECMA-404](https://ecma-international.org/publications-and-standards/standards/ecma-404/) (The JSON data
interchange syntax standard). The goal of this project is to create a fully compliant JSON parser in c++.
See [contributing](#contributing) for the "why".

## Features

- Supports all (maybe not null) json data types.
- Supports nested objects and arrays.

## Usage

All usage examples are in the [tests/test_json_readme.cpp](tests/test_json_readme.cpp) file.

### Getting started

```c++
#include "jsonpp.h"
```

### Parsing & Getting

```c++
// Parse a json string.
std::string jsonString = "{\"key1\": \"value1\", \"key2\": [1, 2, 3]}";
json::Object jsonObject = json::parse(jsonString);

// Access the value of a key.
auto value1 = jsonObject.get("key1");
auto value2 = jsonObject["key2"];
```

### Creating & Setting

```c++
// Set JSON values in a json object.
json::Object jsonObject;

// Set a key to a string
jsonObject.set("key1", json::String("potato"));
jsonObject.set("key1", "potato");
jsonObject["key1"] = json::String("potato");

// Set a key to a bool
jsonObject.set("key2", json::Boolean(true));
jsonObject.set("key2", true);
```

### Arrays

```c++
// Arrays
json::Array jsonArray1;
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
```

## Contributing

Contributions are welcome. This is a simple library I built for my own use to learn more C++. If you find any bugs
or have suggestions for improvements, please open an issue or submit a pull request.

## License

Please see the [LICENSE](LICENSE) file for more information.