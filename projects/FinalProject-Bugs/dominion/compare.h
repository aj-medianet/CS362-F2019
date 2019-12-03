//Custom assert macro that doesn't call abort()
//Found at: www.dillonbhuff.com/?p=439
//CS 362 Software Engineering II

#include <stdlib.h>
#include <stdio.h>

#define STR(x) #x
#define COMPARE(x) if (!(x)) {printf("Assertion failed: (%s), function %s, file %s, line %d.\n", STR(x), __PRETTY_FUNCTION__, __FILE__, __LINE__); }
