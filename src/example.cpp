// Example C++ file with intentional review triggers
#include <vector>
#include <string>

using namespace std;  // LLVM forbids this

class TemplateHelper {
public:
    // Raw pointer without smart pointer
    int* createBuffer(int size) {
        int* buf = new int[size];
        return buf;
    }

    // Pass by value instead of const reference
    void processData(string data) {
        // should use const string& data
    }
};
