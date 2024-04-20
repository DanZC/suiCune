#include "main.h"
//#define REDIRECTED(x) redirectFunc[a##x] = x
#define REDIRECTED(x) redirectFunc[a##x] = convertedFunc[a##x] = x
#define CONVERTED(x) convertedFunc[a##x] = x
#define CONVERTED_SCRIPT(x) redirectFunc[a##x] = convertedFunc[a##x] = (void (*)(void))&x

void init_function_pointers(void);