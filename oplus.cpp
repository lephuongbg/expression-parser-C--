/*
 * OVERLOADING PLUS OPERATOR
 *
 *  Created on: 02-01-2012
 *      Author: herop-kde
 */

#include "functions.hpp"

/************************************************
 * 												*
 *       OPERATOR OVERLOADING: PLUS				*
 * 												*
 ************************************************/
big_num big_num::operator+(big_num op2)
{
	big_num temp;

	int index1, index2;
	int carry = 0;

	/*CONSIDERING DIFFERENT SITUATION*/
	//Compare the two operands' signs
	switch (sign * op2.sign) {
	case 1:						//=>Same:
		if (sign == -1)			//If both are negative, make the result also negative
			temp.sign = -1;
		break;
	case -1:					//=>Different:
		if (sign == -1)			//Change the sum operation to substraction operation
			return (op2 - *this*(-1));
		else
			return (*this - op2*(-1));
		break;
	default:
		break;
	}

	/*DOING THE ADDITION*/
	index1 = number.length() - 1;
	index2 = op2.number.length() - 1;

	/*Add digit by digit until there's no digit left in one of the two operands*/
	for ( ;index1 != -1 && index2 != -1; index1--, index2--)
	{
		carry += C2D(number.at(index1)) + C2D(op2.number.at(index2));
		temp.number.insert(0,1,D2C(carry%10));
		carry /= 10;
	}

	/*Carry the digits left in the other operand to the result*/
	while (index1 >= 0)
	{
		temp.number.insert(0,1,D2C(C2D(number.at(index1)+carry)));
		carry = 0;
		index1--;
	}
	while (index2 >= 0)
	{
		temp.number.insert(0,1,D2C(C2D(op2.number.at(index2)+carry)));
		carry = 0;
		index2--;
	}
	//Last check the carry var
	if (carry != 0)
		temp.number.insert(0,1,D2C(carry));

	return temp;
}

big_num big_num::operator+(int op2)
{
	big_num temp(op2);
	return (*this + temp);
}
