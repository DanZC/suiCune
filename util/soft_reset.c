#include <setjmp.h>
#include "soft_reset.h"

jmp_buf reset_point;

noreturn void SoftReset(int value) {
    longjmp(reset_point, value);
}
