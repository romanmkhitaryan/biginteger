#include "big_integer.hpp"

int main() {
    // int a[4] = {1324234,2,3,5};
    BigInteger num1(-76);
    BigInteger num2(6);
    BigInteger num67("-190787");
    BigInteger num3 = num2 * num1;

    std::cout << (num1 < num2) << std::endl;

    num3.print();

    // BigInteger num2(a, 4, true);

    // BigInteger num3 = num11 + num12;
    // BigInteger num4 = num11 - num12;

    // std::cout << "get_val :: " << num3.get_value() << std::endl;
    // std::cout << "get_val :: " << num4.get_value() << std::endl;

    // bool asasa = num12 > num11;
    // std::cout << (num12.is_negative() ? "-" : "") << num12.get_value();
    // std::cout << " > ";
    // std::cout << (num11.is_negative() ? "-" : "") << num11.get_value();
    // std::cout << std::endl;
    // std::cout <<  ((num12 > num11) ? "true" : "false") << std::endl;

    return 0;
}
