/*
 * BIG CALCULATOR
 *
 *  Created on: 02-01-2012
 *      Author: herop-kde
 */

#include "functions.hpp"
#include <ctime>

int main()
{
#ifdef EG1
	int i;
	big_num a;
	big_num b = 1;
	clock_t start = clock();
	for (i = 1; i < 1000; i++)
	{
		cout << i << '\r' << flush;
		a.set(i);
		b = b * a;
	}
	std::cout << ((double)clock() - start)/CLOCKS_PER_SEC << endl;
	std::cout << b;
#endif
	big_num a = "2882893987";
	big_num b = "10928";
	cout << a/b;
}
