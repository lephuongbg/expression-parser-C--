/*
 * ominus.cpp
 *
 *  Created on: 03-01-2012
 *      Author: herop-kde
 */

#include "functions.hpp"

/*****************************************************
 * Function: abs_compare()                           *
 *                                                   *
 * USE: to compare the absolute value of two number  *
 *                                                   *
 * PARAMETER: two number of type big_num             *
 *                                                   *
 * RETURN:                                           *
 * 	1		n1 > n2                                  *
 * -1		n2 < n2                                  *
 * 	0		n1 = n2                                  *
 *****************************************************/
int abs_compare (big_num n1, big_num n2)
{
	//Compare the lengths of these numbers
	if (n1.number.length() > n2.number.length())
		return 1;
	else if (n1.number.length() < n2.number.length())
		return -1;
	//If they have the same length, compare their digits from left to right
	else
	{
		for (unsigned int i = 0; i < n1.number.length(); i++)
		{
			if (n1.number.at(i) > n2.number.at(i))
				return 1;
			else if (n1.number.at(i) < n2.number.at(i))
				return -1;
		}
		return 0;
	}
}

/************************************************
 * 												*
 *       OPERATOR OVERLOADING: MINUS			*
 * 												*
 ************************************************/
big_num big_num::operator-(big_num op2)
{
	big_num temp;
	int index1, index2;
	int carry = 0;

	/*CONSIDER DIFFERENT SITUATIONS*/
	//If the minuend is negative, change minus to plus
	if (op2.sign == -1)
	{
		return (*this + op2);
	//If not but the subtrahend is negative, also change minus
	//to plus with the result is also negative
	} else {
		if (sign == -1)
		{
			op2.sign = -1;
			temp = op2 + *this;
			return temp;
		}
	}
	//Now, if the subtrahend is smaller than the minuend,
	//we swap their position and return the negative result of the new operation
	if (abs_compare(*this, op2) == -1)
	{
		temp = op2 - *this;
		temp.sign = -1;
		return temp;
	}

	/*DOING THE SUBSTRACTION*/
	//Make the index for subtrahend and minuend
	index1 = number.length() - 1;
	index2 = op2.number.length() - 1;
	//Subtract digit by digit from right to left until there's no digit of minuend left
	for ( ;index2 != -1; index1--, index2--)
	{
		if (number.at(index1) >= number.at(index2))
		{
			carry += number.at(index1) - op2.number.at(index2);
			temp.number.insert(0,1,D2C(carry));
			carry = 0;
		}
		else
		{
			carry += 10 + number.at(index1) - op2.number.at(index2);
			temp.number.insert(0,1,D2C(carry%10));
			carry = -1;
		}
	}
	//Now put the other digits of subtrahend into the result
	while (index1 >= 0)
	{
		if (carry == -1)	//Do not forget the carry phase
		{
			if (number.at(index1) != 0)
			{
				temp.number.insert(0,1,carry+number.at(index1));
				carry = 0;
			}
			else
			{
				temp.number.insert(0,1,'9');
				carry = -1;
			}
		}
		index1--;
	}

	return temp;
}
