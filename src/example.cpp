// Example C++ file with intentional review triggers
#include <memory>
#include <vector>
#include <string>

using namespace std;  // LLVM forbids this

class TemplateHelper {
public:
    std::unique_ptr<int[]> createBuffer(int size) {
        auto buf = std::make_unique<int[]>(size);
        if (!buf) {
            return nullptr;
        }
        return buf;
    }

    // Pass by value instead of const reference
    void processData(string data) {
        // should use const string& data
    }
};
