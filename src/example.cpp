// Example C++ file with intentional review triggers
#include <vector>
#include <string>
#include <string_view>

using namespace std;  // LLVM forbids this

class TemplateHelper {
public:
    // Raw pointer without smart pointer
    int* createBuffer(int size) {
        int* buf = new int[size];
        return buf;
    }

    // Read-only string parameter using std::string_view
    void processData(std::string_view data) {
        // Uses string_view for efficient read-only parameter passing
    }
};
