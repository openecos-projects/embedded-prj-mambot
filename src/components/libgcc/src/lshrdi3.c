#include <stdint.h>

// 64位逻辑右移函数实现
uint64_t __lshrdi3(uint64_t a, int b) {
    union {
        uint64_t u64;
        struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
            uint32_t low;
            uint32_t high;
#else
            uint32_t high;
            uint32_t low;
#endif
        } u32;
    } input, result;
    
    if (b == 0) return a;
    if (b >= 64) return 0;
    
    input.u64 = a;
    
    if (b < 32) {
        // 右移小于32位
        result.u32.low = (input.u32.low >> b) | (input.u32.high << (32 - b));
        result.u32.high = input.u32.high >> b;
    } else {
        // 右移大于等于32位
        result.u32.low = input.u32.high >> (b - 32);
        result.u32.high = 0;
    }
    
    return result.u64;
}