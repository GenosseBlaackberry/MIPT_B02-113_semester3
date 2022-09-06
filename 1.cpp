#include <iostream>
#include <cstdlib>


struct rectangle {
    double length;
    double width;
};


int double_comparator(void* first, void* second) {
    double* a = (double*)first;
    double* b = (double*)second;
    if (*a < *b) {
        return -1;
    }
    if (*a == *b) {
        return 0;
    }
    return 1;
}


int rectangle_comparator(void* first, void* second) {
    rectangle* a = (rectangle*)first;
    rectangle* b = (rectangle*)second;
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


void sort(void* start, unsigned int e_size, unsigned int l_size, int comparator(void*, void*)) {

    if (l_size <= 1) {
        return;
    }

    unsigned int i = 0, j = (l_size - 1);
    unsigned int x = (l_size - 1) / 2;
    char* s = (char*)start;

    do {
        while (comparator((void*)(s + i * e_size), (void*)(s + x * e_size)) == -1) {
            i++;
        }
        while (comparator((void*)(s + j * e_size), (void*)(s + x * e_size)) == 1) {
            j--;
        }

        if (i <= j)
        {   
            if (comparator((void*)(s + i * e_size), (void*)(s + j * e_size)) == 1)
            {
                swap((void*)(s + i * e_size), (void*)(s + j * e_size), e_size);
            }
            i++;
            if (j > 0) {
                j--;
            }
        }
    } while (i <= j);


    if (i < (l_size - 1)) {
        sort((void*)(s + i * e_size), e_size, l_size - i, comparator);
    }
    if (j > 0) {
        sort(start, e_size, j + 1, comparator);
    }

    return;
}


void double_check() {
    using namespace std;
    unsigned int n;
    cout << "Please, enter the list length" << endl;
    cin >> n;
    double *a = new (nothrow) double[n];
    if (a == nullptr) {
        cout << "Error in memory alocation";
        delete[] a;
        return;
    }
    cout << "Please, enter the list" << endl;
    for (unsigned int i = 0; i < n; i++) {
        cin >> a[i];
    }
        
    sort(a, sizeof(double), n, double_comparator);
    
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
    rectangle *a = new (nothrow) rectangle[n];
    if (a == nullptr) {
        cout << "Error in memory alocation";
        delete[] a;
        return;
    }
    cout << "Please, enter the list" << endl;

    for (unsigned int i = 0; i < n; i++) {
        cin >> a[i].length >> a[i].width;
    }

    sort(a, sizeof(rectangle), n, rectangle_comparator);

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

