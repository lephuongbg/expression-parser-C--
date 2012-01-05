/*
 * MISCELLANEOUS
 *
 *  Created on: 05-01-2012
 *      Author: herop
 */

#include "functions.hpp"

/*****************************************************
 * FUNCTION: abs_compare()                           *
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

/********************************************************
 * 														*
 * FUNCTION: s2n() - Convert string to number			*
 * 														*
 ********************************************************/
int s2n (const string& str)
{
	int n;
	istringstream convert(str);
	convert >> n;
	return n;
}

