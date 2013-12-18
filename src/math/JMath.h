#ifndef JMATH_H_
#define JMATH_H_


#if _MSC_VER < 1600
#define INT32_MAX 2147483647
#define INT32_MIN -2147483648
#endif

inline int GetMin(int a, int b)
{
	return a < b ? a : b;
}

inline int GetMax(int a, int b)
{
	return a > b ? a : b;
}
#endif