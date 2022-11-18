#include <iostream>
#include <ctime>
#include <iterator>
#include <vector>
#include <list>
#include <deque>

template <typename T>
unsigned int Josephus(T container, unsigned int step, unsigned int index = 0) {
	unsigned int size = container.size();

	if (size == 1) {
		return container[0];
	}
	
	index = (index + step) % size;

	container.erase(container.begin() + index);

	return Josephus(container, step, index);
}

void check() {
	unsigned int const N = 1000;
	unsigned int const STEP = 257;
	clock_t clock();
	CLOCKS_PER_SEC;

	double start_t = (double)clock() / CLOCKS_PER_SEC;

	std::cout << "vector" << std::endl;
	std::vector <int> v;
	for (unsigned int i = 0; i < N; i++) {
		v.push_back(i);
	}
	std::cout << Josephus<std::vector <int>>(v, STEP) << std::endl;
	double vector_t = (double)clock() / CLOCKS_PER_SEC;
	std::cout << vector_t - start_t;

	std::cout << std::endl;
	std::cout << "deque" << std::endl;
	std::deque <int> d;
	for (unsigned int i = 0; i < N; i++) {
		d.push_back(i);
	}
	std::cout << Josephus<std::deque <int>>(d, STEP) << std::endl;
	double deque_t = (double)clock() / CLOCKS_PER_SEC;
	std::cout << deque_t - vector_t;

}


int main()
{
	check();
}
