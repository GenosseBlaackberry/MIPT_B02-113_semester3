#include <iostream>

#include <cstdint>

class Fraction final {
private:
    // Do NOT rename
    int64_t numerator;
    uint64_t denominator;

    // Do NOT delete
    template <class T>
    friend bool operator==(const Fraction& lhs, const T& rhs);

public:
    Fraction() = delete;
    Fraction(const Fraction& rhs) {}
    Fraction& operator=(const Fraction& rhs);
    Fraction(int64_t numerator, uint64_t denominator);
    
    Fraction operator+(const Fraction& rhs) {
        return Fraction(numerator * rhs.denominator + denominator * rhs.numerator, denominator * rhs.denominator);
    }

    Fraction operator*(const Fraction& rhs) {
        return Fraction(numerator * rhs.numerator, denominator * rhs.denominator);
    }
};

int main() {
    return 0;
}
