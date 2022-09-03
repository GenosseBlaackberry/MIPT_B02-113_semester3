#include <iostream>
#include <cstdlib>


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


void swap(void* first, void* second, unsigned int e_size) {
    using namespace std;
    void* tmp = malloc(e_size);
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
        while (comparator((void*)(s + i * e_size), (void*)(s + x * e_size)) == -1)
            i++;
        while (comparator((void*)(s + j * e_size), (void*)(s + x * e_size)) == 1)
            j--;

        if (i <= j)
        {   
            if (i < j)
            {
                swap((void*)(s + i * e_size), (void*)(s + j * e_size), e_size);
            }
            i++;
            j--;
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


void check() {
    using namespace std;
    unsigned int n;
    cin >> n;
    double *a = new double[n];
    for (unsigned int i = 0; i < n; i++) {
        cin >> a[i];
    }
        
    sort(a, sizeof(double), n, double_comparator);

    /*hoarasort(a, 0, n - 1);*/
    
    for (unsigned int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    return;
}


int main()
{   
    check();
    return 0;
}
