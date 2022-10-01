#include <iostream>
#include <cstdlib>

class PriorityQueue {
private:
    
    PriorityQueue* prev;
    PriorityQueue* next;

public:
    PriorityQueue() : prev(nullptr), next(nullptr) {};

    void push() {
        return;
    }

    PriorityQueue* peek() {
        if (prev == nullptr){
            return this;
        }
        else {
            return next->peek();
        }
        return nullptr;
    }

    void poll() {
        if (prev == nullptr) {
            next->prev = nullptr;
            delete[] this;
        }
        else {
            next->poll();
        }
        return;
    }

    bool is_empty() {
        return false;
    }
};

int main()
{
    return 0;
}
