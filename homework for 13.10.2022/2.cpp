/* Очередь с приоритетом */

#include <iostream>


struct Rectangle {
    double length;
    double width;
};


template <typename T>
struct Comparator {
    virtual int operator()(T & const, T & const) const = 0;
};


template <>
struct Comparator<double> {
    int operator()(double const & a, double const & b) const {
        if (a < b) {
            return -1;
        }
        if (a == b) {
            return 0;
        }
        return 1;
    }
};


template<>
struct Comparator<Rectangle> {
    int operator()(Rectangle const & a, Rectangle const & b) const {
        double a_square = a.length * a.width;
        double b_square = b.length * b.width;
        if (a_square < b_square) {
            return -1;
        }
        if (a_square == b_square) {
            return 0;
        }
        return 1;
    }
};


template <typename T, typename P>
class PriorityQueue {
private:
    T* arr;
    P* pri;
    unsigned size;
    bool emptyness;
    Comparator<T> comparator_arr = Comparator<T>();
    Comparator<P>  comparator_pri = Comparator<P>();



public:
    PriorityQueue() : emptyness(true), size(0) {
        T* a = new (std::nothrow) T[size];
        if (a == nullptr) {
            std::cout << "Error in memory allocation" << std::endl;
        }
        arr = a;

        P* b = new (std::nothrow) P[size];
        if (b == nullptr) {
            std::cout << "Error in memory allocation" << std::endl;
        }
        pri = b;
    }

    /* Вспомогательные методы */
    void print() {
        using namespace std;
        cout << "[ ";
        for (unsigned i = 0; i < size; i++) {
            cout << arr[i] << "(" << pri[i] << ") ";

        }
        cout << "]" << endl;
    }

    void swap(unsigned i, unsigned j) {
        T temp_a;
        temp_a = arr[j];
        arr[j] = arr[i];
        arr[i] = temp_a;

        P temp_b;
        temp_b = pri[j];
        pri[j] = pri[i];
        pri[i] = temp_b;
        return;
    }

    void lift(int i) {
        if (i == 0) {
            return;
        }
        
        if (comparator_pri(pri[i], pri[(i - 1) / 2]) == 1) {
            swap(i, (i - 1) / 2);
            lift((i - 1) / 2);
        }
        else if (comparator_pri(pri[i], pri[(i - 1) / 2]) == 0) {
            if (comparator_arr(arr[i], arr[(i - 1) / 2]) == 1) {
                swap(i, (i - 1) / 2);
                lift((i - 1) / 2);
            }
        }
        return;
    }

    void sort(int i) {

        if (2 * i + 1 >= size) {
            return;
        }
        if (comparator_pri(pri[i], pri[2 * i + 1]) == -1) {
            swap(i, 2 * i + 1);
            sort(2 * i + 1);
        }
        else if (comparator_pri(pri[i], pri[2 * i + 1]) == 0) {
            if (comparator_arr(arr[i], arr[2 * i + 1]) == -1) {
                swap(i, 2 * i + 1);
                sort(2 * i + 1);
            }
        }
        if (2 + i + 2 < size) {
            if (comparator_pri(pri[i], pri[2 * i + 2]) == -1) {
                swap(i, 2 * i + 2);
                sort(2 * i + 2);
            }
            else if (comparator_pri(pri[i], pri[2 * i + 2]) == 0) {
                if (comparator_arr(arr[i], arr[2 * i + 2]) == -1) {
                    swap(i, 2 * i + 2);
                    sort(2 * i + 2);
                }
            }
        }
        return;
    }

    /* Основные методы */
    void push(T to_push, P priority) {
        if (emptyness && size == 0) {
            emptyness = false;
        }
        size++;

        T* a = new (std::nothrow) T[size];
        if (a == nullptr) {
            std::cout << "Error in memory allocation" << std::endl;
            return;
        }
        for (unsigned i = 0; i < size - 1; i++) {
            a[i] = arr[i];
        }
        a[size - 1] = to_push;
        arr = a;

        P* b = new (std::nothrow) P[size];
        if (b == nullptr) {
            std::cout << "Error in memory allocation" << std::endl;
            return;
        }
        for (unsigned i = 0; i < size - 1; i++) {
            b[i] = pri[i];
        }
        b[size - 1] = priority;
        pri = b;

        lift(size - 1);
        return;
    }

    T peek() {
        return arr[0];
    }

    void poll() {
        if (emptyness) {
            std::cout << "Can not delete from an empty heap" << std::endl;
            return;
        }
        if (not(emptyness) && size == 1) {
            emptyness = true;
        }
        size--;

        T* a = new (std::nothrow) T[size];
        if (a == nullptr) {
            std::cout << "Error in memory allocation" << std::endl;
            return;
        }
        for (unsigned i = 1; i < size; i++) {
            a[i] = arr[i];
        }
        a[0] = arr[size];
        arr = a;

        T* b = new (std::nothrow) P[size];
        if (b == nullptr) {
            std::cout << "Error in memory allocation" << std::endl;
            return;
        }
        for (unsigned i = 1; i < size; i++) {
            b[i] = pri[i];
        }
        b[0] = pri[size];
        pri = b;

        sort(0);
        return;
    }

    bool is_empty() {
        return emptyness;
    }

    void free() {
        size = 0;
        emptyness = true;
        delete[] arr;
        return;
    }
};


void check() {

    PriorityQueue<double, double> x = PriorityQueue<double, double>();
    x.print();
    x.push(7, 1); 
    x.push(3, 1);
    x.push(8, 1);
    x.push(2, 1);
    x.push(1, 1);
    x.push(0, 2);
    x.print();
    std::cout << x.peek() << std::endl;
    x.poll();
    x.print();
    x.free();
}


int main()
{
    check();
    return 0;
}
