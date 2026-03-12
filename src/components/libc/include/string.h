#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Copy memory from source to destination
 * @param dest Destination memory address
 * @param src Source memory address
 * @param n Number of bytes to copy
 * @return Pointer to destination
 */
void* memcpy(void* dest, const void* src, size_t n);

/**
 * @brief Set memory to a specific value
 * @param s Memory address to set
 * @param c Value to set (as unsigned char)
 * @param n Number of bytes to set
 * @return Pointer to memory address
 */
void* memset(void* s, int c, size_t n);

/**
 * @brief Calculate length of string
 * @param s String to measure
 * @return Length of string (excluding null terminator)
 */
size_t strlen(const char* s);

#ifdef __cplusplus
}
#endif

#endif /* STRING_H */