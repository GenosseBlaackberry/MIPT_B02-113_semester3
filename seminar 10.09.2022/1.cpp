#include <iostream>


double min(double a, double b) {
    if (a <= b) {
        return a;
    }
    return b;
};


double max(double a, double b) {
    if (a >= b) {
        return a;
    }
    return b;
};


class Rect {
private:
    double x1, y1, x2, y2;


public:
    Rect(double x1, double y1, double x2, double y2) : x1(x1), y1(y1), x2(x2), y2(y2) {};
    Rect() : x1(0), y1(0), x2(0), y2(0) {};

    void output() {
        using namespace std;
        cout << "(" << x1 << ", " << y1 << ") ";
        cout << "(" << x2 << ", " << y1 << ") ";
        cout << "(" << x2 << ", " << y2 << ") ";
        cout << "(" << x1 << ", " << y2 << ")" << endl;
        return;
    };

    void translation(double dx, double dy) {
        x1 += dx;
        x2 += dx;
        y1 += dy;
        y2 += dy;
        return;
    };

    void scaling(double dx, double dy) {
        x2 = x1 + dx;
        y2 = y1 + dy;
        return;
    };

    Rect intersection(Rect rect) {
        double new_x1, new_y1, new_x2, new_y2;

        new_x1 = max(min(x1, x2), min(rect.x1, rect.x2));
        new_y1 = max(min(y1, y2), min(rect.y1, rect.y2));
        new_x2 = min(max(x1, x2), max(rect.x1, rect.x2));
        new_y2 = min(max(y1, y2), max(rect.y1, rect.y2));

        if (new_x1 > new_x2 || new_y1 > new_y2) {
            Rect output;
            return output;
        }

        Rect output(new_x1, new_y1, new_x2, new_y2);
        return output;
    };

    Rect unification(Rect rect) {
        double new_x1, new_y1, new_x2, new_y2;

        new_x1 = min(min(x1, x2), min(rect.x1, rect.x2));
        new_y1 = min(min(y1, y2), min(rect.y1, rect.y2));
        new_x2 = max(max(x1, x2), max(rect.x1, rect.x2));
        new_y2 = max(max(y1, y2), max(rect.y1, rect.y2));

        Rect output(new_x1, new_y1, new_x2, new_y2);
        return output;
    };
};


void check() {
    using namespace std;
    double x1, y1, x2, y2;
    bool t;

    cin >> x1 >> y1 >> x2 >> y2;
    Rect a(x1, y1, x2, y2);
    cin >> x1 >> y1 >> x2 >> y2;
    Rect b(x1, y1, x2, y2);

    Rect c = a.intersection(b);
    Rect d = a.unification(b);

    a.translation(0, 0);

    cout << "Intersection: ";
    c.output();
    cout << "Unification: ";
    d.output();

    return;
};


int main()
{   
    check();
    return 0;
};