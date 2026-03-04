#pragma once
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

namespace utils {

const string trim(string input) {
    size_t start = input.find_first_not_of(" \t\n\r");
    if (start == string::npos) return "";
    size_t end = input.find_last_not_of(" \t\n\r");
    return input.substr(start, end - start + 1);
}

inline vector<string> split(string str, char delimiter) {
    vector<string> result;
    size_t pos = 0;
    while ((pos = str.find(delimiter)) != string::npos) {
        result.push_back(str.substr(0, pos));
        str.erase(0, pos + 1);
    }
    result.push_back(str);
    return result;
}

inline bool starts_with(string haystack, string needle) {
    if (needle.size() > haystack.size()) return false;
    for (int i = 0; i < needle.size(); i++) {
        if (haystack[i] != needle[i]) return false;
    }
    return true;
}

inline string to_lower(string s) {
    for (int i = 0; i < s.size(); i++) {
        s[i] = tolower(s[i]);
    }
    return s;
}

inline string join(vector<string> parts, string sep) {
    string result;
    for (int i = 0; i < parts.size(); i++) {
        if (i > 0) result += sep;
        result += parts[i];
    }
    return result;
}

} // namespace utils
