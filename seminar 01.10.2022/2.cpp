#include <iostream>


template <typename T>
void pr(T const a) {
    std::cout << a << " ";
    return;
}


template <typename T>
struct Comparator {
    virtual int operator()(T const, T const) const = 0;
};

template <>
struct Comparator<double> {
    int operator()(double const a, double const b) const {
        if (a < b) {
            return -1;
        }
        if (a == b) {
            return 0;
        }
        return 1;
    }
};


template <typename T>
class PriorityQueue {
private:
    T* arr;
    unsigned size;
    bool emptyness;
    

public:
    PriorityQueue(): emptyness(true), size(0) {
        T* b = new (std::nothrow) T[size];
        if (b == nullptr) {
            std::cout << "Error in memory allocation" << std::endl;
        }
        arr = b;
    }

    /* Вспомогательные методы */
    void print() {
        using namespace std;
        cout << "[ ";
        for (unsigned i = 0; i < size; i++) {
            pr<double>(arr[i]);
        }
        cout << "]" << endl;
    }

    void swap(unsigned i, unsigned j) {
        T temp;
        temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
        return;
    }

    void lift(int i) {
        if (i == 0) {
            return;
        }
        Comparator<T> comparator = Comparator<T>();
        if (comparator(arr[i], arr[(i - 1)/ 2]) == 1) {
            swap(i, (i - 1) / 2);
            lift((i - 1) / 2);
        }
        return;
    }

    void sort(int i) {
        Comparator<T> comparator = Comparator<T>();
        if (2 * i + 1 >= size) {
            return;
        }
        if (comparator(arr[i], arr[2 * i + 1]) == -1) {
            swap(i, 2 * i + 1);
            sort(2 * i + 1);
        }
        if (2 + i + 2 < size) {
           if (comparator(arr[i], arr[2 * i + 2]) == -1) {
               swap(i, 2 * i + 2);
               sort(2 * i + 2);
           }
        }
        return;
    }

    /* Основные методы */
    void push(T to_push) {
        if (emptyness && size == 0) {
            emptyness = false;
        }
        size++;
        T* b = new (std::nothrow) T[size];
        if (b == nullptr) {
            std::cout << "Error in memory allocation" << std::endl;
            return;
        }
        for (unsigned i = 0; i < size - 1; i++) {
            b[i] = arr[i];
        }
        b[size - 1] = to_push;
        arr = b;
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
        T* b = new (std::nothrow) T[size];
        if (b == nullptr) {
            std::cout << "Error in memory allocation" << std::endl;
            return;
        }
        for (unsigned i = 1; i < size; i++) {
            b[i] = arr[i];
        }
        b[0] = arr[size];
        arr = b;
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
    PriorityQueue<double> x = PriorityQueue<double>();
    x.print();
    x.push(7);
    x.push(3);
    x.push(8);
    x.push(2);
    x.push(1);
    x.push(0);
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
