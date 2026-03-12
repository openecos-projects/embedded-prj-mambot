#ifndef LIBGCC_H
#define LIBGCC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief GCC Runtime Library Support Functions
 * 
 * This header provides declarations for compiler runtime support functions
 * that are typically provided by libgcc. These functions are used by the
 * compiler to implement operations that are not directly supported by the
 * target hardware.
 */

/* Arithmetic Operations */

/**
 * @brief 32-bit unsigned integer multiplication
 * @param a First operand
 * @param b Second operand
 * @return Product of a and b
 */
unsigned int __mulsi3(unsigned int a, unsigned int b);

/**
 * @brief 64-bit integer multiplication
 * @param a First operand (64-bit)
 * @param b Second operand (64-bit)
 * @return Product of a and b (64-bit)
 */
uint64_t __muldi3(uint64_t a, uint64_t b);

/**
 * @brief 64-bit logical right shift
 * @param a Value to shift
 * @param b Number of bits to shift
 * @return Result of logical right shift
 */
uint64_t __lshrdi3(uint64_t a, int b);

/* Division Operations (implemented in assembly) */

/**
 * @brief 32-bit unsigned integer division
 * @param a Dividend
 * @param b Divisor
 * @return Quotient of a/b
 */
unsigned int __udivsi3(unsigned int a, unsigned int b);

/**
 * @brief 32-bit unsigned integer modulo
 * @param a Dividend
 * @param b Divisor
 * @return Remainder of a%b
 */
unsigned int __umodsi3(unsigned int a, unsigned int b);

/**
 * @brief 32-bit signed integer division
 * @param a Dividend
 * @param b Divisor
 * @return Quotient of a/b
 */
int __divsi3(int a, int b);

/**
 * @brief 32-bit signed integer modulo
 * @param a Dividend
 * @param b Divisor
 * @return Remainder of a%b
 */
int __modsi3(int a, int b);

#ifdef __cplusplus
}
#endif

#endif /* LIBGCC_H */