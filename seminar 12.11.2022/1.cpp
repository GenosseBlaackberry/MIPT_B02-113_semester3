#include <iostream>
#include <ctime>
#include <iterator>
#include <vector>
#include <list>
#include <deque>

template <typename T>
int Joseph(T begin, T end) {
	auto pt = begin;
	while (pt != end) {
		std::cout << *pt << std::endl;
		pt++;
	}
	return 0;
}


int main()
{
	std::vector <int> v;
	v.push_back(1);
	v.push_back(3);
	v.push_back(3);
	v.push_back(7);
	Joseph<std::vector <int> ::iterator>(v.begin(), v.end());
}
