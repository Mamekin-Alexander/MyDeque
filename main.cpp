#include "Vector.h"
#include <iostream>
int main()
{
	my::Vector<int> v = { 1,2,3,4 };
	my::Vector<int>::Iterator i = v.begin();
	while (i != v.end())
	{
		std::cout << *i;
		i++;
	}
	return 0;
}
