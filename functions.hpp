/*
 * functions.hpp
 *
 *  Created on: 02-01-2012
 *      Author: herop-kde
 */

#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define D2C(x) (x + 48)	//Digit to character
#define C2D(x) (x - 48)	//Character to digit

class big_num {
public:
	string number;
	int sign;

	//Constructors
	big_num();
	big_num(int n);
	big_num(string &str);
	big_num(const char* c_str);

	//Retrieve value from an integer
	void set(int n);

	//Overloading operators
	big_num operator+(big_num op2);
	big_num operator-(big_num op2);
	big_num operator*(big_num op2);
	big_num operator/(big_num op2);
};
#ifndef OSTREAM_OP
#define OSTREAM_OP
ostream &operator<<(ostream &out, const big_num& op);

#endif /*OSTREAM_OP*/

#endif /* FUNCTIONS_HPP_ */
