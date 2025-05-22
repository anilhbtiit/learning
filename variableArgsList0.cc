#include <stdarg.h>
#include <stdio.h>

#define CHECK_ARG_INT(arg) do { \
    if ((arg) < 0) { \
        printf("Error: Integer argument %d is negative!\n", arg); \
    } else { \
        printf("Valid Integer: %d\n", arg); \
    } \
} while (0)

void my_checked_function(int num_args, ...) {
    va_list args;
    va_start(args, num_args);

    for (int i = 0; i < num_args; i++) {
        int arg = va_arg(args, int);
        CHECK_ARG_INT(arg);  // Apply sanity check macro
    }

    va_end(args);
}

int main() {
    my_checked_function(4, 10, -5, 20, 21);  // One negative argument, will trigger the check
    return 0;
}

