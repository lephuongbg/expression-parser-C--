/*
 * MULTIPLY OPERATOR OVERLOADING
 *
 *  Created on: 03-01-2012
 *      Author: herop-kde
 */

/********************************************
 * 											*
 *      OPERATOR OVERLOADING: MULTIPLY		*
 *											*
 ********************************************/
#include "functions.hpp"

big_num big_num::operator*(big_num op2)
{
	big_num result = 0;
	int carry = 0;
	result.sign = sign*op2.sign;

	//Optimizing the speed because of the loop's attribute
	if (number.length() > op2.number.length())
		return (op2 * *this);

	for ( int i = number.length()-1; i >= 0; i--)
	{
		big_num temp;
		for ( int j = op2.number.length()-1; j >= 0; j--)
		{
			carry += C2D(number.at(i))*C2D(op2.number.at(j));
			temp.number.insert(0,1,D2C(carry%10));
			carry /= 10;
		}
		while (carry != 0)
		{
			temp.number.insert(0,1,D2C(carry%10));
			carry /= 10;
		}
		temp.number.insert(temp.number.length(), number.length()-i-1, '0');
		result = result + temp;
	}
	return result;
}

big_num big_num::operator*(int op2)
{
	big_num temp(op2);
	return (*this * temp);
}
