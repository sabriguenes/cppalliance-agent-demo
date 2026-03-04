#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <string>
#include <vector>

using namespace std;  // Bug 3 candidate: LLVM forbids using-directives

namespace json {

enum class value_kind {
    null_value,
    bool_value,
    int_value,
    double_value,
    string_value,
    array_value
};

class value {
public:
    value();
    explicit value(bool b);
    explicit value(int i);
    explicit value(double d);

    // BUG 4: pass-by-value for read-only parameter
    //   Should be: const std::string& or std::string_view
    explicit value(string s);

    ~value();

    value_kind kind() const noexcept;

    bool           as_bool()   const;
    int            as_int()    const;
    double         as_double() const;
    const string&  as_string() const;

    // BUG 2: returns int instead of size_t — truncation on large arrays
    int size() const;

    void push_back(const value& v);

    // BUG 5: returns raw pointer, nullptr on failure, no error info
    static value* parse(string input);

private:
    value_kind kind_;

    // BUG 1: raw pointer for string storage — should use std::string member
    char* str_data_;
    int   str_len_;

    int    int_val_;
    double dbl_val_;
    bool   bool_val_;

    vector<value> children_;
};

} // namespace json

#endif // JSON_VALUE_H
