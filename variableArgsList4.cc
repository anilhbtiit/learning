#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void my_sanity_checked_function(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    const char* p = fmt;
    int int_value;
    double double_value;

    while (*p != '\0') {
        switch (*p++) {
            case 'd':  // Integer
                int_value = va_arg(args, int);
                if (int_value < 0) {
                    printf("Error: Received negative integer: %d\n", int_value);
                } else {
                    printf("Integer: %d\n", int_value);
                }
                break;

            case 'f':  // Floating-point
                double_value = va_arg(args, double);
                if (double_value < 0.0) {
                    printf("Error: Received negative double: %f\n", double_value);
                } else {
                    printf("Double: %f\n", double_value);
                }
                break;

            default:
                printf("Error: Unknown format specifier '%c'\n", *(p - 1));
                va_end(args);
                return;
        }
    }

    va_end(args);
}

int main() {
    my_sanity_checked_function("dffd", 10, -5.3, 7.8, -100);  // Mixed integers and floats
    return 0;
}

