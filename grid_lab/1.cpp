#include <iostream>
#include <cassert>


template<typename T>
T default_value() {
	return 0;
};



template <typename T>
class Grid final {

private:
	using size_type = unsigned;
	T default_entity = default_value<T>();
	size_type y_size, x_size;
	T* data;
	bool indexing;

public:
	using output_type = size_type;

	//метод создание тела сетки
	void make_data() {
		data = new (std::nothrow) T[(y_size + 1) * (x_size + 1)];
		if (data == nullptr) {
			std::cout << "Error in memory alocation!" << std::endl;
			delete[] data;
		}
		return;
	}

	//конструкторы
	Grid(T const& t) : y_size(1), x_size(1) {
		make_data();
		data[0] = t;
	}

	Grid(size_type y_size, size_type x_size) : y_size(y_size), x_size(x_size) {
		make_data();
		for (unsigned i = 0; i < (y_size) * (x_size); i++) {
			data[i] = default_entity;
		}
	}

	Grid(size_type y_size, size_type x_size, T const& t) : y_size(y_size), x_size(x_size) {
		make_data();
		for (unsigned i = 0; i < (y_size + 1) * (x_size + 1); i++) {
			data[i] = t;
		}
	}

	//деструктор
	~Grid() {
		delete[] data;
	}

	//конструктор копирования
	Grid(Grid<T> const& other) {
		x_size = other.get_x_size();
		y_size = other.get_y_size();
		make_data();
		for (unsigned i = 0; i < y_size; i++) {
			for (unsigned j = 0; j < x_size; j++) {
				data[i * x_size + j] = other(i, j);
			}
		}
	}

	//конструктор перемещения
	Grid(Grid<T>&& other) {
		x_size = other.x_size;
		y_size = other.y_size;
		data = other.data;
		other.data = nullptr;
	}

	//копирующие присваивание
	Grid<T>& operator=(Grid<T>& other) {
		x_size = other.x_size;
		y_size = other.y_size;
		make_data();
		for (unsigned i = 0; i < y_size; i++) {
			for (unsigned j = 0; j < x_size; j++) {
				data[i * x_size + j] = other(i, j);
			}
		}
		return *this;
	}

	//перемещающее присваивание
	Grid<T>& operator=(Grid<T>&& other) noexcept {
		Grid<T> tmp(other);
		std::swap(this->x_size, tmp.x_size);
		std::swap(this->y_size, tmp.y_size);
		std::swap(this->data, tmp.data);
		return *this;
	}

	//присваивание к единичному элементу
	Grid<T>& operator=(T const& t) {
		for (auto it = data, end = data + x_size * y_size; it < end; it++) {
			*it = t;
		}
		return *this;
	}

	//оператор доступа к значению элемента
	T operator ()(size_type y_idx, size_type x_idx) const {
		return data[y_idx * x_size + x_idx];
	}

	//оператор доступа к ссылке на элемент
	T& operator ()(size_type y_idx, size_type x_idx) {
		return &data[y_idx * x_size + x_idx];
	}

	//оператор индексирования
	T* operator[](size_type idx) {
		if (indexing = false) {
			return data + idx * x_size;
		}
		indexing = false;
		return data + idx;
	}

	//оператор получения координаты y
	size_type get_y_size() const {
		return y_size;
	}

	//оператор получения координаты x
	size_type get_x_size() const {
		return x_size;
	}

	//оператор печати сетки
	void print() {
		using namespace std;
		for (unsigned i = 0; i < y_size; i++) {
			for (unsigned j = 0; j < x_size; j++) {
				cout << data[i * x_size + j] << " ";
			}
			cout << endl;
		}
	}
};


void check() {
	float t = 0.0f;
	Grid<float> g(3, 2, t);

	assert(3 == g.get_y_size());
	assert(2 == g.get_x_size());

	using gsize_t = Grid<int>::output_type;

	for (gsize_t y_idx = 0; y_idx < g.get_y_size(); ++y_idx)
		for (gsize_t x_idx = 0; x_idx < g.get_x_size(); ++x_idx) {
			assert(0.0f == g[y_idx][x_idx]);
		}

	for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
		for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
			g[y_idx][x_idx] = 1.0f;

	for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
		for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
			assert(1.0f == g[y_idx][x_idx]);

}

int main() {
	Grid<unsigned> a(7, 7, 8);
	Grid<unsigned> b = a;
	Grid<unsigned> c(1);
	c = 7;
	c.print();
	check();
	return 0;
}
