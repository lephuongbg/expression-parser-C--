/*
 * ostream
 *
 *  Created on: 03-01-2012
 *      Author: herop-kde
 */

#include "functions.hpp"

ostream &operator<<(ostream &out, const big_num& op) {
	if (op.sign == -1)
		out << '-';
	out << op.number;
	return out;
};
