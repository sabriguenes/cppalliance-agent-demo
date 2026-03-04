#include "json_value.h"
#include <cstring>
#include <cstdlib>

using namespace std;  // Bug 3: LLVM coding standards violation

namespace json {

value::value()
    : kind_(value_kind::null_value)
    , str_data_(nullptr)
    , str_len_(0)
    , int_val_(0)
    , dbl_val_(0.0)
    , bool_val_(false)
{}

value::value(bool b)
    : kind_(value_kind::bool_value)
    , str_data_(nullptr)
    , str_len_(0)
    , int_val_(0)
    , dbl_val_(0.0)
    , bool_val_(b)
{}

value::value(int i)
    : kind_(value_kind::int_value)
    , str_data_(nullptr)
    , str_len_(0)
    , int_val_(i)
    , dbl_val_(0.0)
    , bool_val_(false)
{}

value::value(double d)
    : kind_(value_kind::double_value)
    , str_data_(nullptr)
    , str_len_(0)
    , int_val_(0)
    , dbl_val_(d)
    , bool_val_(false)
{}

// BUG 4: takes string by value — unnecessary copy for read-only data
value::value(string s)
    : kind_(value_kind::string_value)
    , str_len_(0)
    , int_val_(0)
    , dbl_val_(0.0)
    , bool_val_(false)
{
    // BUG 1: raw new[] allocation — should use std::string or unique_ptr
    str_len_ = (int)s.size();  // BUG 3: C-style cast
    str_data_ = new char[str_len_ + 1];
    memcpy(str_data_, s.c_str(), str_len_ + 1);
}

value::~value() {
    // BUG 1 continued: raw delete[] — no RAII, exception-unsafe
    delete[] str_data_;
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
    static const string empty;
    if (kind_ != value_kind::string_value || !str_data_)
        return empty;
    // BUG 1: must reconstruct string each call because we store char*
    static thread_local string cached;
    cached.assign(str_data_, str_len_);
    return cached;
}

// BUG 2: size_t to int truncation — undefined behavior if children_ > INT_MAX
int value::size() const {
    return (int)children_.size();  // BUG 3: C-style cast
}

void value::push_back(const value& v) {
    kind_ = value_kind::array_value;
    children_.push_back(v);
}

// BUG 5: returns nullptr on failure — caller has no way to know WHY parsing
// failed (syntax error? unexpected token? truncated input?). Should throw
// or return std::expected/std::optional with error info.
value* value::parse(string input) {  // BUG 4: pass-by-value again
    if (input.empty())
        return nullptr;  // BUG 5: silent failure

    // Trim whitespace
    size_t start = input.find_first_not_of(" \t\n\r");
    if (start == string::npos)
        return nullptr;  // BUG 5: silent failure

    char first = input[start];

    if (first == '"') {
        size_t end = input.find('"', start + 1);
        if (end == string::npos)
            return nullptr;  // BUG 5: no error message for unterminated string
        string content = input.substr(start + 1, end - start - 1);
        return new value(content);  // BUG 1: caller must remember to delete
    }

    if (first == 't' && input.substr(start, 4) == "true")
        return new value(true);  // BUG 1: raw new

    if (first == 'f' && input.substr(start, 5) == "false")
        return new value(false);  // BUG 1: raw new

    if (first == 'n' && input.substr(start, 4) == "null")
        return new value();  // BUG 1: raw new

    // Try parsing as number
    char* endptr = nullptr;
    double num = strtod(input.c_str() + start, &endptr);
    if (endptr != input.c_str() + start) {
        // BUG 3: C-style cast to check if it's an integer
        if (num == (int)num && num >= -2147483648.0 && num <= 2147483647.0)
            return new value((int)num);  // BUG 3: two C-style casts
        return new value(num);  // BUG 1: raw new
    }

    return nullptr;  // BUG 5: unknown token, no error info
}

} // namespace json
