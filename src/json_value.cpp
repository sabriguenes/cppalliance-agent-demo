#include "json_value.h"
#include <cstdlib>
#include <stdexcept>

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

// Bug 4 fixed: const reference; Bug 1 fixed: std::string member
value::value(const string& s)
    : kind_(value_kind::string_value)
    , str_data_(s)
    , int_val_(0)
    , dbl_val_(0.0)
    , bool_val_(false)
{}

value::~value() = default;

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
    static const string empty;
    if (kind_ != value_kind::string_value)
        return empty;
    return str_data_;
}

// Bug 2 fixed: returns size_t; Bug 3 fixed: no cast needed
size_t value::size() const {
    return children_.size();
}

void value::push_back(const value& v) {
    kind_ = value_kind::array_value;
    children_.push_back(v);
}

// Bug 5 fixed: returns unique_ptr, throws on parse error
// Bug 4 fixed: const reference parameter
std::unique_ptr<value> value::parse(const string& input) {
    if (input.empty())
        throw std::runtime_error("parse error: empty input");

    // Trim whitespace
    size_t start = input.find_first_not_of(" \t\n\r");
    if (start == string::npos)
        throw std::runtime_error("parse error: input contains only whitespace");

    char first = input[start];

    if (first == '"') {
        size_t end = input.find('"', start + 1);
        if (end == string::npos)
            throw std::runtime_error("parse error: unterminated string literal");
        string content = input.substr(start + 1, end - start - 1);
        return std::make_unique<value>(content);
    }

    if (first == 't' && input.substr(start, 4) == "true")
        return std::make_unique<value>(true);

    if (first == 'f' && input.substr(start, 5) == "false")
        return std::make_unique<value>(false);

    if (first == 'n' && input.substr(start, 4) == "null")
        return std::make_unique<value>();

    // Try parsing as number
    char* endptr = nullptr;
    double num = strtod(input.c_str() + start, &endptr);
    if (endptr != input.c_str() + start) {
        // Bug 3 fixed: static_cast instead of C-style cast
        if (num == static_cast<int>(num) && num >= -2147483648.0 && num <= 2147483647.0)
            return std::make_unique<value>(static_cast<int>(num));
        return std::make_unique<value>(num);
    }

    throw std::runtime_error("parse error: unexpected token");
}

} // namespace json
