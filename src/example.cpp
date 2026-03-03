// Example C++ file with intentional review triggers
#include <memory>
#include <vector>
#include <string>

using namespace std;  // LLVM forbids this

class TemplateHelper {
public:
    // RAII buffer using smart pointer
    std::unique_ptr<int[]> createBuffer(int size) {
        return std::make_unique<int[]>(size);
    }

    // Pass by value instead of const reference
    void processData(string data) {
        // should use const string& data
    }
};
