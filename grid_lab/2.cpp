#include <iostream>
#include <cassert>


template<typename T>
T default_value() {
	return 0;
};


template <typename T, unsigned N>
class Grid final {

private:
	using size_type = unsigned;
	T default_entity = default_value<T>();
	size_type size;
	Grid<T, N - 1>* data;
	bool indexing;
	const unsigned MAX_TRIES = 10;

public:
	using output_type = size_type;

	//метод создание тела сетки
	void make_data(unsigned tries = 0) {
		if (tries == MAX_TRIES) {
			throw;
		}
		data = static_cast<Grid<T, N - 1>*>(operator new[](size * sizeof(Grid<T, N - 1>)));
		if (data == nullptr) {
			std::cout << "Error in memory alocation!" << std::endl;
			make_data(tries + 1);
		}
		return;
	}


	//конструкторы
	Grid(T const& t) : size(1) {
		make_data();
		data[0] = t;
	}

	template<typename... Args>
	Grid(size_type size, Args ... subgrid) : size(size) {
		make_data();
		for (unsigned i = 0; i < size; i++) {
			new (data + i) Grid<T, N - 1>(subgrid...);
		}
	}

	//деструктор
	~Grid() {
		if (data != nullptr) {
			for (unsigned i = 0; i < size; i++) {
				data[i].~Grid();
			}
			operator delete(data);
		}
	}

	//конструктор копирования
	Grid(Grid<T, N> const& other) {
		size = other.get_size();
		make_data();
		for (unsigned i = 0; i < size; ++i) {
			new (data + i) Grid<T, N - 1>(other.data[i]);
		}
	}

	//конструктор перемещения
	Grid(Grid<T, N>&& other) noexcept {
		size = other.get_size();
		data = other.data;
		other.data = nullptr;
	}

	//копирующие присваивание
	Grid<T, N>& operator=(Grid<T, N>& other) {
		Grid<T, N> tmp(other);
		std::swap(this->size, tmp.size);
		std::swap(this->data, tmp.data);
		return *this;
	}

	//перемещающее присваивание
	Grid<T, N>& operator=(Grid<T, N>&& other) noexcept {
		Grid<T, N> tmp(other);
		std::swap(this->size, tmp.size);
		std::swap(this->data, tmp.data);
		return *this;
	}

	//оператор доступа к значению элемента
	template<typename... Args>
	T operator ()(size_type idx, Args ... subgrid) const {
		return data[idx](subgrid ...);
	}

	//оператор индексирования
	Grid<T, N - 1>& operator[](size_type idx) const {
		return data[idx];
	}

	//оператор получения размера
	size_type get_size() const {
		return size;
	}


	//оператор печати сетки
	void print() {
		using namespace std;
		for (unsigned i = 0; i < size; i++) {
			data[i].print();
			cout << endl;
		}
	}
};


template <typename T>
class Grid<T, 1> final {

private:
	using size_type = unsigned;
	T default_entity = default_value<T>();
	size_type size;
	T* data;
	const unsigned MAX_TRIES = 10;

public:
	using output_type = size_type;

	//метод создание тела сетки
	void make_data(unsigned tries = 0) {
		if (tries == MAX_TRIES) {
			throw;
		}
		data = new (std::nothrow) T[size];
		if (data == nullptr) {
			std::cout << "Error in memory alocation!" << std::endl;
			make_data(tries + 1);
		}
		return;
	}

	//конструкторы
	Grid(T const& t) : size(1) {
		make_data();
		data[0] = t;
	}

	Grid(size_type size) : size(size) {
		make_data();
		for (unsigned i = 0; i < size; i++) {
			data[i] = default_entity;
		}
	}

	Grid(size_type size, T const& t) : size(size) {
		make_data();
		for (unsigned i = 0; i < size; i++) {
			data[i] = t;
		}
	}

	//деструктор
	~Grid() {
		if (data != nullptr) {
			delete[] data;
		}
	}

	//конструктор копирования
	Grid(Grid<T, 1> const& other) {
		size = other.get_size();
		make_data();
		for (unsigned i = 0; i < size; i++) {
			data[i] = other(i);
		}
	}

	//конструктор перемещения
	Grid(Grid<T, 1>&& other) {
		size = other.size;
		data = other.data;
		other.data = nullptr;
	}

	//копирующие присваивание
	Grid<T, 1>& operator=(Grid<T, 1>& other) {
		size = other.size;
		make_data();
		for (unsigned i = 0; i < size; i++) {
			data[i] = other(i);
		}
		return *this;
	}

	//перемещающее присваивание
	Grid<T, 1>& operator=(Grid<T, 1>&& other) noexcept {
		Grid<T, 1> tmp(other);
		std::swap(this->size, tmp.size);
		std::swap(this->data, tmp.data);
		return *this;
	}

	//присваивание к единичному элементу
	Grid<T, 1>& operator=(T const& t) {
		for (auto it = data, end = data + size; it < end; it++) {
			*it = t;
		}
		return *this;
	}

	//оператор доступа к значению элемента
	T operator ()(size_type idx) const {
		return data[idx];
	}

	//оператор доступа к ссылке на элемент
	T& operator ()(size_type idx) {
		return data[idx];
	}

	//оператор индексирования
	T* operator[](size_type idx) {
		return data + idx;
	}

	//оператор получения размера
	size_type get_size() const {
		return size;
	}

	//оператор печати сетки
	void print() {
		using namespace std;
		for (unsigned i = 0; i < size; i++) {
			cout << data[i] << " ";
		}
		cout << endl;
	}
};


void check() {
	Grid<float, 3> const g3(2, 3, 4, 1.0f);
	assert(1.0f == g3(1, 1, 1));

	Grid<float, 2> g2(2, 5, 2.0f);
	assert(2.0f == g2(1, 1));

	g2 = g3[1];
	assert(1.0f == g2(1, 1));
}

int main() {
	Grid<unsigned, 2> a(7, 7, 8);
	Grid<unsigned, 2> b = a;
	Grid<unsigned, 2> d = std::move(a);
	Grid<float, 1> c(1.f);
	c = 7;
	c.print();
	check();
	return 0;
}
