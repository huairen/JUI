#ifndef JMATH_H_
#define JMATH_H_

#define INT32_MAX 2147483647
#define INT32_MIN -2147483648

inline int GetMin(int a, int b)
{
	return a < b ? a : b;
}

inline int GetMax(int a, int b)
{
	return a > b ? a : b;
}
#endif