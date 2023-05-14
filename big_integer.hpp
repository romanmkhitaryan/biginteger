#include <iostream>
#include <string>

class BigInteger {
public:
    void set_value(std::string);
    std::string get_value() const;

    void set_sign(bool);
    bool is_negative() const;

private:
    std::string m_value;
    bool m_is_negative;

public:
    enum comparison_type {
        less = 0,
        equal,
        bigger
    };

    void print();

    static comparison_type compare_two_big_intagers(BigInteger*, BigInteger*);
    static BigInteger subtract(BigInteger*, BigInteger*);
    static BigInteger add(BigInteger*, BigInteger*);

public:

    bool operator>(BigInteger& other);
    bool operator<(BigInteger& other);
    bool operator==(BigInteger& other);
    bool operator!=(BigInteger& other);
    bool operator>=(BigInteger& other);
    bool operator<=(BigInteger& other);
    BigInteger operator-();
    BigInteger& operator++();
    BigInteger operator++(int);
    BigInteger operator--();
    BigInteger operator--(int);
    BigInteger operator+(BigInteger& other);
    BigInteger operator-(BigInteger& other);
    BigInteger& operator+=(BigInteger& other);
    BigInteger& operator-=(BigInteger& other);

public:
    BigInteger(int);
    BigInteger(int*, unsigned int, bool = false);
    ~BigInteger();
};