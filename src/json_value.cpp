#include "json_value.h"
#include <cstdlib>

using namespace std;  // Bug 3: LLVM coding standards violation

namespace json {

value::value()
    : kind_(value_kind::null_value)
    , int_val_(0)
    , dbl_val_(0.0)
    , bool_val_(false)
{}

value::value(bool b)
    : kind_(value_kind::bool_value)
    , int_val_(0)
    , dbl_val_(0.0)
    , bool_val_(b)
{}

value::value(int i)
    : kind_(value_kind::int_value)
    , int_val_(i)
    , dbl_val_(0.0)
    , bool_val_(false)
{}

value::value(double d)
    : kind_(value_kind::double_value)
    , int_val_(0)
    , dbl_val_(d)
    , bool_val_(false)
{}

value::value(const string& s)
    : kind_(value_kind::string_value)
    , str_data_(s)
    , int_val_(0)
    , dbl_val_(0.0)
    , bool_val_(false)
{}

value::~value() {
}

value_kind value::kind() const noexcept {
    return kind_;
}

bool value::as_bool() const {
    return bool_val_;
}

int value::as_int() const {
    return int_val_;
}

double value::as_double() const {
    return dbl_val_;
}

const string& value::as_string() const {
    return str_data_;
}

size_t value::size() const {
    return children_.size();
}

void value::push_back(const value& v) {
    kind_ = value_kind::array_value;
    children_.push_back(v);
}

optional<value> value::parse(const string& input) {
    if (input.empty())
        return nullopt;

    // Trim whitespace
    size_t start = input.find_first_not_of(" \t\n\r");
    if (start == string::npos)
        return nullopt;

    char first = input[start];

    if (first == '"') {
        size_t end = input.find('"', start + 1);
        if (end == string::npos)
            return nullopt;
        string content = input.substr(start + 1, end - start - 1);
        return value(content);
    }

    if (first == 't' && input.substr(start, 4) == "true")
        return value(true);

    if (first == 'f' && input.substr(start, 5) == "false")
        return value(false);

    if (first == 'n' && input.substr(start, 4) == "null")
        return value();

    // Try parsing as number
    char* endptr = nullptr;
    double num = strtod(input.c_str() + start, &endptr);
    if (endptr != input.c_str() + start) {
        if (num == static_cast<int>(num) && num >= -2147483648.0 && num <= 2147483647.0)
            return value(static_cast<int>(num));
        return value(num);
    }

    return nullopt;
}

} // namespace json
