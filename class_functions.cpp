/*
 * class_constructor.cpp
 *
 *  Created on: 03-01-2012
 *      Author: herop-kde
 */

#include "functions.hpp"

/****************************************
 * 										*
 *  CLASS CONSTRUCTOR FOR BIG_NUM TYPE	*
 *										*
 ****************************************/

big_num::big_num() {
	sign = 1;
	number = "";
};
big_num::big_num(int n) {
	std::stringstream convert;
	convert << n;
	number =  convert.str();
	sign = 1;
	if (n < 0)
	{
		number.erase(0,1);
		sign = -1;
	}


}
big_num::big_num(string &str) {
	if (str.at(0) == '-')
	{
		sign = -1;
		number = str.substr(1);
	} else {
		number = str;
		sign = 1;
	}
}
big_num::big_num(const char* c_str)
{
	string str(c_str);
	if (str.at(0) == '-')
	{
		sign = -1;
		number = str.substr(1);
	} else {
		number = str;
		sign = 1;
	}
}


/****************************************
 * 										*
 *  MEMBER FUNCTION FOR BIG_NUM CLASS	*
 *										*
 ****************************************/
void big_num::set(int n) {
	sign = (n >= 0) ? 1 : -1;
	std::stringstream convert;
	convert << n;
	number =  convert.str();
}
void big_num::reset() {
	number = "";
	sign = 1;
}
big_num big_num::operator=(big_num op2)
{
	number = op2.number;
	sign = op2.sign;
	return *this;
}
