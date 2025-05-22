#include <type_traits>
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<Numeric T, Numeric... Args>
auto add(T a, Args... args);

template<Numeric T, Numeric... Args>
auto subtract(T a, Args... args);

template<Numeric T, Numeric... Args>
auto multiply(T a, Args... args); 
