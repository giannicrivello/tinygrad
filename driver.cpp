#include "Value.hpp"



int main() {
    auto val1 = Value(3.0);
    auto val2 = Value(4.0);
    auto val3 = val1 + val2;

    auto o = val3 * val1;
   std::cout << val3.grad() << std::endl;
   o.backward(); 
   std::cout << val3.grad() << std::endl;
    return 0;
}