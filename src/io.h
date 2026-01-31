#ifndef OZERO_IO_H
#define OZERO_IO_H

#ifndef ozero_max
/**
 * Returns the maximum of two values.
 * Template version provides type safety and compile-time type checking.
 *
 * @param x The first value to compare
 * @param y The second value to compare
 * @return The greater of x and y
 */
template<typename T>
inline T ozero_max(T x, T y) {
	return (x > y) ? x : y;
}
#endif

#ifndef ozero_min
/**
 * Returns the minimum of two values.
 * Template version provides type safety and compile-time type checking.
 *
 * @param x The first value to compare
 * @param y The second value to compare
 * @return The lesser of x and y
 */
template<typename T>
inline T ozero_min(T x, T y) {
	return (x < y) ? x : y;
}
#endif

#endif// OZERO_IO_H