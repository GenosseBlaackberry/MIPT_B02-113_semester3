#include <iostream>


class Rect {
private:
    double x1, y1, x2, y2;
    const bool empty;


public:
    Rect(double x1, double y1, double x2, double y2) : x1(x1), y1(y1), x2(x2), y2(y2), empty(0) {};
    Rect() : x1(0), y1(0), x2(0), y2(0), empty(1) {};

    void output() const{
        using namespace std;
        if (empty){
            cout << "empty rectangle" << endl;
            return;
        }
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
        double min(double, double);
        double max(double, double);

        double new_x1, new_y1, new_x2, new_y2;

        new_x1 = max(min(x1, x2), min(rect.x1, rect.x2));
        new_y1 = max(min(y1, y2), min(rect.y1, rect.y2));
        new_x2 = min(max(x1, x2), max(rect.x1, rect.x2));
        new_y2 = min(max(y1, y2), max(rect.y1, rect.y2));

        if (new_x1 > new_x2 || new_y1 > new_y2 || empty || rect.empty) {
            Rect output;
            return output;
        }

        Rect output(new_x1, new_y1, new_x2, new_y2);
        return output;
    };

    Rect unification(Rect rect) {
        double min(double, double);
        double max(double, double);

        double new_x1, new_y1, new_x2, new_y2;

        if (empty) {
            return rect;
        };
        if (rect.empty) {
            return *this;
        };

        new_x1 = min(min(x1, x2), min(rect.x1, rect.x2));
        new_y1 = min(min(y1, y2), min(rect.y1, rect.y2));
        new_x2 = max(max(x1, x2), max(rect.x1, rect.x2));
        new_y2 = max(max(y1, y2), max(rect.y1, rect.y2));

        Rect output(new_x1, new_y1, new_x2, new_y2);
        return output;
    };
};


double min(double a, double b) {
    if (a <= b) {
        return a;
    };
    return b;
};


double max(double a, double b) {
    if (a >= b) {
        return a;
    };
    return b;
};


void check() {
    using namespace std;
    double x1, y1, x2, y2;
    unsigned t = 1;
    unsigned n;

    cout << "Enter two rectangles" << endl;
    cin >> x1 >> y1 >> x2 >> y2;
    Rect a(x1, y1, x2, y2);
    cin >> x1 >> y1 >> x2 >> y2;
    Rect b(x1, y1, x2, y2);

    while (t != 0) {
        cout << " 0 - see intersection and unification\n 1 - move rectangle\n 2 - set new size" << endl;
        cin >> t;
        if (t == 1) {
            cout << "Choose rectangle" << endl;
            cin >> n;
            cout << "enter dx and dy" << endl;
            double dx, dy;
            cin >> dx >> dy;
            if (n == 1) {
                a.translation(dx, dy);
            }
            else if (n == 2) {
                b.translation(dx, dy);
            }
        }
        else if (t == 2) {
            cout << "Choose rectangle" << endl;
            cin >> n;
            cout << "enter dx and dy" << endl;
            double dx, dy;
            cin >> dx >> dy;
            if (n == 1) {
                a.scaling(dx, dy);
            }
            else if (n == 2) {
                b.scaling(dx, dy);
            }
        };
    };

    Rect c = a.intersection(b);
    Rect d = a.unification(b);

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

