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
	sign = (n >= 0) ? 1 : -1;
	std::stringstream convert;
	convert << n;
	number =  convert.str();
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
