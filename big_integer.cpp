#include "big_integer.hpp"
#include <iostream>
#include <string>
#include <cmath>

void BigInteger::
set_value(std::string val)
{
    m_value = val;
}

std::string BigInteger::
get_value() const
{
    return m_value;
}

void BigInteger::
set_sign(bool b)
{
    m_is_negative = b;
}

bool BigInteger::
is_negative() const
{
    return m_is_negative;
}

bool is_number_negative(int i)
{
    return i < 0;
}

std::string int_to_string(unsigned int i)
{
    return std::to_string(i);
}

int string_to_int(std::string str)
{
    int res = 0;

    for(int i = 0; i < str.size(); ++i)
    {
        res += int(str[i] - '0');
        res *= 10;
    }

    return res / 10;
}

std::string reverse_string(const std::string& str)
{
    std::string res = "";

    for(int i = str.size() - 1; i >= 0; --i)
    {
        res += str[i];
    }

    return res;

}

std::string remove_zeros(std::string str)
{
	int i = 0;
	
	std::string res = str;

	for(; i < str.size(); ++i){
		if(str[i] != '0'){
			break;
		}
	}

	res.erase(0, i);

	return res;
}

std::string get_concated_string(int * arr, unsigned int size)
{
    std::string res = "";

    for(int i = 0; i < size; ++i)
    {
        res += int_to_string(arr[i]);
    }

    return res;
}

BigInteger::comparison_type BigInteger::
compare_two_big_intagers(BigInteger *a, BigInteger *b)
{
	if(a->is_negative() && !b->is_negative())
	{
		return BigInteger::comparison_type::less;
	} else if(!a->is_negative() && b->is_negative())
	{
		return BigInteger::comparison_type::bigger;
	} else {
		if(a->get_value().size() == b->get_value().size()){
			
			std::string a_val = a->get_value();
			std::string b_val = b->get_value();

			for(int i = 0; i < a_val.size(); ++i)
			{
				if(a_val[i] > b_val[i]){
					return BigInteger::comparison_type::bigger;
				} else if(a_val[i] < b_val[i]){
					return BigInteger::comparison_type::less;
				}
			}
			return BigInteger::comparison_type::equal;
		} else {
			bool res_for_abs_values = false;
	
			if((a->get_value().size() > b->get_value().size()) ^ (a->is_negative()))
			{
				return BigInteger::comparison_type::bigger;
			} else {
				return BigInteger::comparison_type::less;
			}
			
		}
	}
}

void BigInteger::
print()
{
	std::cout << "number  << " << (is_negative() ? "-" : "") << get_value() << std::endl;
}

bool BigInteger::
operator>(BigInteger& other)
{
	BigInteger::comparison_type res = compare_two_big_intagers(this, &other);

	if(BigInteger::comparison_type::bigger == res){
		return true;
	} else {
		return false;
	}
}

bool BigInteger::
operator<(BigInteger& other)
{
	BigInteger::comparison_type res = compare_two_big_intagers(this, &other);

	if(BigInteger::comparison_type::less == res){
		return true;
	} else {
		return false;
	}
}

bool BigInteger::
operator==(BigInteger& other)
{
	BigInteger::comparison_type res = compare_two_big_intagers(this, &other);

	if(BigInteger::comparison_type::equal == res){
		return true;
	} else {
		return false;
	}
}

bool BigInteger::
operator!=(BigInteger& other)
{
	BigInteger::comparison_type res = compare_two_big_intagers(this, &other);

	if(BigInteger::comparison_type::equal == res){
		return false;
	} else {
		return true;
	}
}

bool BigInteger::
operator>=(BigInteger& other)
{
	BigInteger::comparison_type res = compare_two_big_intagers(this, &other);

	if(BigInteger::comparison_type::less == res){
		return false;
	} else {
		return true;
	}
}

bool BigInteger::
operator<=(BigInteger& other)
{
	BigInteger::comparison_type res = compare_two_big_intagers(this, &other);

	if(BigInteger::comparison_type::bigger == res){
		return false;
	} else {
		return true;
	}
}

BigInteger BigInteger::
operator-()
{
	BigInteger tmp(*this);
	tmp.set_sign(!is_negative());
	return tmp;
}

BigInteger& BigInteger::
operator++()
{
	BigInteger tmp(1);
	*this += tmp;
	return *this;
}

BigInteger BigInteger::
operator++(int)
{
	BigInteger tmp(1);
	BigInteger tmp_this = *this;
	*this += tmp;
	return tmp_this;
}

BigInteger BigInteger::
operator--()
{
	BigInteger tmp(1);
	*this -= tmp;
	return *this;
}

BigInteger BigInteger::
operator--(int)
{
	BigInteger tmp(1);
	BigInteger tmp_this = *this;
	*this -= tmp;
	return tmp_this;
}

BigInteger BigInteger::
operator-(BigInteger& other)
{
	BigInteger tmp = (-other);
	return (*this) + tmp;
}

BigInteger& BigInteger::
operator+=(BigInteger& other)
{
	BigInteger tmp = *this + other;
	*this = tmp;
	return *this;
}

BigInteger& BigInteger::
operator-=(BigInteger& other)
{
	BigInteger tmp = *this - other;
	*this = tmp;
	return *this;
}

BigInteger BigInteger::
operator+(BigInteger& other)
{
	BigInteger* a = this;
	BigInteger* b = &other;
	

	if(!a->is_negative() && !b->is_negative())
	{
		return add(a, b);
	} else if(a->is_negative() && b->is_negative())
	{
		return -(add(a, b));
	} else if(a->is_negative() && !b->is_negative())
	{
		BigInteger a_abs = -(*a);
		
		if(a_abs > *b)
		{
			return -(subtract(a, b));
		} else {
			return subtract(b, a);
		}
	} else if(!a->is_negative() && b->is_negative())
	{
		BigInteger b_abs = -(*b);
		if(*a > b_abs)
		{
			return subtract(a, b);
		} else {
			return -(subtract(b, a));
		}
	}
	return BigInteger(0);
}

BigInteger BigInteger::
operator*(BigInteger& other)
{
	if(this->is_negative() ^ other.is_negative()){
		return -(multiply(this, &other));
	} else {
		return multiply(this, &other);
	}
}

BigInteger BigInteger::
operator/(BigInteger& other)
{
	if(this->is_negative() ^ other.is_negative()){
		return -(divide(this, &other));
	} else {
		return divide(this, &other);
	}
}

BigInteger BigInteger::
add(BigInteger* a, BigInteger* b)
{
	std::string a_r = reverse_string(a->get_value());
	std::string b_r = reverse_string(b->get_value());

	unsigned int bigger_size = std::max(a_r.size(), b_r.size());

	std::string res = "";

	bool has_reserve = false;

	for(int i = 0; i < bigger_size; ++i)
	{
		int a_tmp = 0;
		int b_tmp = 0;

		if(a_r.size() > i)
		{
			a_tmp = a_r[i] - '0';
		}
		
		if(b_r.size() > i)
		{
			b_tmp = b_r[i] - '0';
		}
	
		int tmp = a_tmp + b_tmp;

		tmp += has_reserve;

		res += char((tmp % 10) + '0');

		has_reserve = ((tmp % 10) != tmp);
	}

	if(has_reserve){
	res += char(1 + '0');
	}

	return BigInteger(reverse_string(res));
}


BigInteger BigInteger::
subtract(BigInteger* a, BigInteger* b)
{
	std::string a_r = reverse_string(a->get_value());
	std::string b_r = reverse_string(b->get_value());

	std::string res = "";

	int debt = 0;

	for(int i = 0; i < a_r.size(); ++i)
	{
		int a_tmp = (int)(a_r[i] - '0');
		int b_tmp = 0;
		
		if(b_r.size() > i){
			b_tmp = (int)(b_r[i] - '0');
		}

		if(debt != 0){
			if(a_tmp - debt >= 0) {
				a_tmp -= debt;
				debt = 0;
			} else {
				int tmp_debt = debt;
				debt = 1;
				a_tmp = a_tmp + 10 - tmp_debt;
			}
		}

		int tmp = a_tmp - b_tmp;
		
		if(tmp < 0)
		{
			debt += 1;
			res += char((a_tmp + 10 - b_tmp) + '0');
		} else{
			res += char(tmp + '0');
		}
	}
	
	res = remove_zeros(reverse_string(res));
	return BigInteger(res);
}

BigInteger BigInteger::
multiply(BigInteger* a, BigInteger* b)
{
	std::string a_r = reverse_string(a->get_value());
	std::string b_r = reverse_string(b->get_value());

	BigInteger res_of_multiple(0);

	for(int i = 0; i < a_r.size(); ++i){
		unsigned int x = (int)(a_r[i] - '0');

		int reserve = 0;
		std::string res = "";

		for(int j = 0; j < b_r.size(); ++j){
			unsigned int y = (int)(b_r[j] - '0');
			
			int tmp_val = x * y + reserve;

			reserve = 0;
			res += char((tmp_val) % 10 + '0');

			if(tmp_val > 9){
				reserve = tmp_val / 10;
			}
		}

		if(reserve != 0){
			res += char((reserve) + '0');
		}

		res = reverse_string(res);

		for(int l = 0; l < i; ++l){
			res += "0";
		}

		BigInteger tmp(res);
		tmp.print();
		res_of_multiple += tmp;
	}
	res_of_multiple.print();
	return res_of_multiple;
}

BigInteger BigInteger::
divide(BigInteger* a, BigInteger* b)
{
	return BigInteger(0);
}

BigInteger::
BigInteger(int val)
{
	// std::cout << "BigInteger constructor #1" << std::endl;

	set_sign(is_number_negative(val));

	set_value(int_to_string(std::abs(val)));

	// std::cout << "value is : " << (is_negative() ? "-" : "") << get_value() << std::endl;
}

BigInteger::
BigInteger(std::string str)
{
	if(str[0] == '-')
	{
		set_sign(true);
		str.erase(0, 1);
	} else {
		set_sign(false);
	}

	set_value(str);
}

BigInteger::
~BigInteger()
{
	// std::cout << "BigINteger destructor" << std::endl;
}