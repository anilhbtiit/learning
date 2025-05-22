#include <template.h>

template<Numeric T, Numeric... Args>
auto add(T a, Args... args) {
    return a +( ... + args);
}

template<Numeric T, Numeric... Args>
auto subtract(T a, Args... args) {
    return a - ( ... + args);
}

template<Numeric T, Numeric... Args>
auto multiply(T a, Args... args) {
    return a * ( ... * args);
}


