#include <iostream>
#include <vector>
#include <set>
#include <random>


class State {
    public:
        virtual bool contains(int s) const{
            return 0;
        }
};


class DiscreteState: public State {
private:
    int const state;

public:
    DiscreteState(int state) : state(state) { }

    bool contains(int s) const override {
        return s == state;
    }
};


class SegmentState: public State {
private:
    int const beg, end;

public:
    SegmentState() : beg(0), end(-1) { }
    SegmentState(int beg, int end) : beg(beg), end(end) { }

    bool contains(int s) const override {
        return s >= beg && s <= end;
    }
};


class SetState: public State {
private:
    std::set<int> const states;

public:
    SetState() : states() { }
    SetState(std::set<int> const& src) : states(src) { }

    bool contains(int s) const override {
        return states.count(s) > 0;
    }
};


class ContinuousStateWithGaps : public State {
private:
    std::vector<SegmentState> const segments;
    SetState gaps;

public:
    ContinuousStateWithGaps(std::vector<SegmentState> const& src, SetState gaps) : segments(src), gaps(gaps) {};

    bool contains(int s) const override {

        if (gaps.contains(s)) {
            return 0;
        }

        for (auto i : segments) {
            if (i.contains(s)) {
                return 1;
            }
        }
        return gaps.contains(s);
    }
};


class ContinuousStateWithAdds : public State {
private:
    std::vector<SegmentState> const segments;
    SetState adds;

public:
    ContinuousStateWithAdds(std::vector<SegmentState> const& src, SetState adds) : segments(src), adds(adds) {};

    bool contains(int s) const override {
        for (auto i : segments) {
            if (i.contains(s)) {
                return 1;
            }
        }
        return adds.contains(s);
    }
};


class ContinuousStateWithGapsAndAdds : public State {
private:
    std::vector<SegmentState> const segments;
    SetState gaps, adds;

public:
    ContinuousStateWithGapsAndAdds(std::vector<SegmentState> const& src, SetState gaps, SetState adds) : segments(src), gaps(gaps), adds(adds) {};

    bool contains(int s) const override {
        bool flag = 0;
        for (auto i : segments) {
            if (i.contains(s)) {
                flag = 1;
            }
        }
        return (flag && adds.contains(s)) || (flag && not (gaps.contains(s))) || (adds.contains(s) && not (gaps.contains(s)));
    }
};


class UnitedStates : public State {
private:
    State a, b;

public:
    UnitedStates(State a, State b) : a(a), b(b) {};

    bool contains(int s) const override {
        return (a.contains(s) || b.contains(s));
    }
};


class IntersectedStates : public State {
private:
    State a, b;

public:
    IntersectedStates(State a, State b) : a(a), b(b) {};

    bool contains(int s) const override {
        return (a.contains(s) && b.contains(s));
    }
};


class NegationState : public State {
private:
    State const& a;
public:
    NegationState(State const& a) :a(a) {}

    bool contains(int s) const override {
        return!a.contains(s);
    }
};


class ProbabilityTest {
private:
    int const E_min, E_max;
public:
    ProbabilityTest(int E_min, int E_max) :
        E_min(E_min), E_max(E_max) {}
    float test(
        State const& s,
        unsigned test_count,
        unsigned seed) const {
        std::default_random_engine reng(seed);
        std::uniform_int_distribution<int> dstr(E_min, E_max);

        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(reng))) ++good;
        return
            static_cast<float>(good) / static_cast<float>(test_count);
    }
};


void check(){
    DiscreteState ds(101);
    SegmentState ss1(0, 100);
    SegmentState ss2(50, 150);
    UnitedStates us(ds, ss1);
    IntersectedStates is(ss1, ss2);
    NegationState ng(ds);
    ProbabilityTest pt(-1000, 1000);
    std::cout << pt.test(ds, 30000, 0.7) << std::endl;
    std::cout << pt.test(ss1, 30000, 0.7) << std::endl;
}


int main(int argc, const char* argv[]) {
    check();
    return 0;
}
