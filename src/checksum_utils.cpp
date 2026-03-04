#include <cstddef>
#include <cstdint>

// Calculate checksum of a byte buffer
int calculate_checksum(const unsigned char* data, size_t size) {
    uint8_t checksum = 0;
    for (size_t i = 0; i < size; ++i) {
        checksum += data[i];
    }
    return checksum;
}
