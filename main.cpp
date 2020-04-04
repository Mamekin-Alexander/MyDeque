#include "Deque.h"
#include <iostream>
#include <vld.h>
int main()
{
	Deque<int> d;
	for (int32_t i = 0; i < 1000; ++i)
	{
		d.PushBack(i);
	}
	for (int32_t i = 0; i < 1000; ++i)
	{
		d.PopFront();
	}
	for (int32_t i = 0; i < 1000; ++i)
	{
		d.PushBack(i);
	}
	for (int32_t i = 0; i < d.Size(); ++i)
	{
		std::cout<<d[i]<<'\n';
	}
	return 0;
}
