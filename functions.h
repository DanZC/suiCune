#include "main.h"
//#define REDIRECTED(x) redirectFunc[a##x] = x
#define REDIRECTED(x) redirectFunc[a##x] = convertedFunc[a##x] = x
#define CONVERTED(x) convertedFunc[a##x] = x

void init_function_pointers(void);