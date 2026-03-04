#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <memory>
#include <stdexcept>
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

    // Bug 4 fixed: const reference instead of pass-by-value
    explicit value(const string& s);

    ~value();

    value_kind kind() const noexcept;

    bool           as_bool()   const;
    int            as_int()    const;
    double         as_double() const;
    const string&  as_string() const;

    // Bug 2 fixed: returns size_t to avoid truncation
    size_t size() const;

    void push_back(const value& v);

    // Bug 5 fixed: returns unique_ptr, throws on parse error
    static std::unique_ptr<value> parse(const string& input);

private:
    value_kind kind_;

    // Bug 1 fixed: std::string member replaces raw char*/int pair
    string str_data_;

    int    int_val_;
    double dbl_val_;
    bool   bool_val_;

    vector<value> children_;
};

} // namespace json

#endif // JSON_VALUE_H
