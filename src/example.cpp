// Example C++ file with intentional review triggers
#include <climits>
#include <vector>
#include <string>

using namespace std;  // LLVM forbids this

class TemplateHelper {
public:
    // Raw pointer without smart pointer
    int* createBuffer(int size) {
        if (size <= 0 || size > INT_MAX / (int)sizeof(int)) {
            return nullptr;
        }
        int* buf = new int[size];
        return buf;
    }

    // Pass by value instead of const reference
    void processData(string data) {
        // should use const string& data
    }
};
