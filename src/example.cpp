// Example C++ file with LLVM coding standard compliance
#include <memory>
#include <string>
#include <vector>

class TemplateHelper {
public:
    // Use unique_ptr for automatic memory management
    std::unique_ptr<int[]> createBuffer(int Size) {
        return std::make_unique<int[]>(Size);
    }

    // Pass by const reference to avoid unnecessary copies
    void processData(const std::string &Data) {
        // Process data without copying
    }
};
