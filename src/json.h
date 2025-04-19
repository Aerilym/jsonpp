#ifndef JSON_H
#define JSON_H

#include <map>
#include <string>
#include <utility>
#include <variant>
#include <vector>


namespace json {
    // Forward declarations of the inner classes.
    class String;
    class Number;
    class Boolean;
    class Array;
    class Object;

    // Define a variant type that can hold any JSON value type.
    using Value = std::variant<String, Number, Boolean, Array, Object>;


    class ValueInterface {
    public:
        virtual std::string serialize() = 0;
        virtual ~ValueInterface() = default;
    };

    class String final : public ValueInterface {
        std::string data;

    public:
        String() : data() {
        }

        explicit String(std::string data) : ValueInterface(), data(std::move(data)) {
        }

        std::string serialize() override;

        String& operator=(std::string& value);
    };

    class Number final : public ValueInterface {
        std::string data;

    public:
        Number() : data() {
        }

        explicit Number(std::string data) : ValueInterface(), data(std::move(data)) {
        }

        std::string serialize() override;
    };

    class Boolean final : public ValueInterface {
        bool data;

    public:
        Boolean() : data(false) {
        }

        explicit Boolean(const bool data) : ValueInterface(), data(data) {
        }

        std::string serialize() override;
    };

    class Array final : public ValueInterface {
        std::vector<Value> data;

    public:
        Array() : data() {
        }

        explicit Array(std::vector<Value> data) : ValueInterface(), data(std::move(data)) {
        }

        std::string serialize() override;

        // Read-only access via operator[] (throws if index out of range).
        Value& operator[](size_t index);

        const Value& operator[](size_t index) const;

        // A setter method that extends the vector if needed.
        void set(size_t index, const Value& value);

        // Optional: A push_back method to add elements at the end.
        void push_back(const Value& value);

        // Optional: Get the size of the array.
        size_t size() const;
    };

    class Object final : public ValueInterface {
        std::map<std::string, Value> data;

    public:
        Object() : data() {
        }

        explicit Object(std::map<std::string, Value> data) : ValueInterface(), data(std::move(data)) {
        }

        std::string serialize() override;
        // Getter with x.get(key) syntax.
        Value get(const std::string& key);

        // Setter with x.set(key, value) syntax.
        Value set(const std::string& key, const Value& value);

        Value set(const std::string& key, const std::string& value);

        Value set(const std::string& key, const bool& value);

        // Getter/Setter with x[i] syntax.
        Value& operator[](const std::string& key);

        // Const version for read-only access.
        const Value& operator[](const std::string& key) const;

    };

    Object parse(const std::string& json);
};

#endif //JSON_H
