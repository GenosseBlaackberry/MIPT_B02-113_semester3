/* Обобщённая сортировка */

#include <iostream>
#include <cstdlib>


struct Rectangle {
    double length;
    double width;
};


template <typename T>
struct Comparator {
    virtual int operator()(T* const, T* const) const = 0;
};


struct Double_Comparator final: Comparator<double>{
    int operator()(double* const a, double* const b) const {
        if (*a < *b) {
            return -1;
        }
        if (*a == *b) {
            return 0;
        }
        return 1;
    }
};



struct Rectangle_Comparator final: Comparator<Rectangle>{
    int operator()(Rectangle* const a, Rectangle* const b) const {
        double a_square = a->length * a->width;
        double b_square = b->length * b->width;
        if (a_square < b_square) {
            return -1;
        }
        if (a_square == b_square) {
            return 0;
        }
        return 1;
    }
};


void swap(void* first, void* second, unsigned int e_size) {
    using namespace std;
    void* tmp = malloc(e_size);
    if (tmp == 0) {
        cout << "Error in memory alocation";
        free(tmp);
        return;
    }
    memcpy(tmp, first, e_size);
    memcpy(first, second, e_size);
    memcpy(second, tmp, e_size);
    free(tmp);
    return;
}

template <typename T>
void sort(T* start, unsigned int l_size, Comparator<T> & comparator) {
    return;
}


template <>
void sort<double>(double* start, unsigned int l_size, Comparator<double> & comparator) {
    if (l_size <= 1) {
        return;
    }

    unsigned int e_size = sizeof(double), i = 0, j = (l_size - 1);
    unsigned int x = (l_size - 1) / 2;
    char* s = (char*)start;


    do {
        while (comparator((double*)(s + i * e_size), (double*)(s + x * e_size)) == -1) {
            i++;
        }
        while (comparator((double*)(s + j * e_size), (double*)(s + x * e_size)) == 1) {
            j--;
        }

        if (i <= j)
        {
            if (comparator((double*)(s + i * e_size), (double*)(s + j * e_size)) == 1)
            {
                swap((double*)(s + i * e_size), (double*)(s + j * e_size), e_size);
            }
            i++;
            if (j > 0) {
                j--;
            }
        }
    } while (i <= j);


    if (i < (l_size - 1)) {
        sort((double*)(s + i * e_size), l_size - i, comparator);
    }
    if (j > 0) {
        sort(start, j + 1, comparator);
    }
    return;
}


template <>
void sort<Rectangle>(Rectangle* start, unsigned int l_size, Comparator<Rectangle>& comparator) {
    if (l_size <= 1) {
        return;
    }

    unsigned int e_size = sizeof(Rectangle), i = 0, j = (l_size - 1);
    unsigned int x = (l_size - 1) / 2;
    char* s = (char*)start;


    do {
        while (comparator((Rectangle*)(s + i * e_size), (Rectangle*)(s + x * e_size)) == -1) {
            i++;
        }
        while (comparator((Rectangle*)(s + j * e_size), (Rectangle*)(s + x * e_size)) == 1) {
            j--;
        }

        if (i <= j)
        {
            if (comparator((Rectangle*)(s + i * e_size), (Rectangle*)(s + j * e_size)) == 1)
            {
                swap((Rectangle*)(s + i * e_size), (Rectangle*)(s + j * e_size), e_size);
            }
            i++;
            if (j > 0) {
                j--;
            }
        }
    } while (i <= j);


    if (i < (l_size - 1)) {
        sort((Rectangle*)(s + i * e_size), l_size - i, comparator);
    }
    if (j > 0) {
        sort(start, j + 1, comparator);
    }
    return;
}



void double_check() {
    using namespace std;
    unsigned int n;
    cout << "Please, enter the list length" << endl;
    cin >> n;
    double* a = new (nothrow) double[n];
    if (a == nullptr) {
        cout << "Error in memory alocation";
        delete[] a;
        return;
    }
    cout << "Please, enter the list" << endl;
    for (unsigned int i = 0; i < n; i++) {
        cin >> a[i];
    }

    Double_Comparator comparator;
    sort<double>(a, n, comparator);

    for (unsigned int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }

    delete[] a;
    return;
}


void rectangle_check() {
    using namespace std;
    unsigned int n;
    cout << "Please, enter the list length" << endl;
    cin >> n;
    Rectangle* a = new (nothrow) Rectangle[n];
    if (a == nullptr) {
        cout << "Error in memory alocation";
        delete[] a;
        return;
    }
    cout << "Please, enter the list" << endl;

    for (unsigned int i = 0; i < n; i++) {
        cin >> a[i].length >> a[i].width;
    }

    Rectangle_Comparator comparator;
    sort(a, n, comparator);

    for (unsigned int i = 0; i < n; i++) {
        cout << a[i].length << " " << a[i].width << endl;
    }

    delete[] a;
    return;
}


void check() {
    using namespace std;
    unsigned int n;
    cout << "If you want to sort type double, please, enter 0" << endl;
    cout << "If you want to sort rectangle squares, please, enter 1" << endl;
    cout << endl;
    cin >> n;
    if (n == 0) {
        double_check();
    }
    else if (n == 1) {
        rectangle_check();
    }
    return;
}


int main()
{
    check();
    return 0;
}
