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

        for (auto i : segments) {
            if (i.contains(s)) {
                return 1;
            }
        }
        return adds.contains(s) && not (gaps.contains(s));
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


class ProbabilityTest {
private:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;

public:
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count) : seed(seed), test_min(test_min), test_max(test_max), test_count(test_count) { }

    float operator()(State const& s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min, test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;

        return static_cast<float>(good) / static_cast<float>(test_count);
    }
};


int main(int argc, const char* argv[]) {
    DiscreteState d(1);
    SegmentState s1(0, 10);
    SegmentState s2(42, 47);
    SetState ss({ 1, 3, 5, 7, 23, 48, 57, 60, 90, 99 });
    ContinuousStateWithGaps cswg({ s1, s2 }, ss);
    ContinuousStateWithAdds cswa({ s1, s2 }, ss);
    ContinuousStateWithGapsAndAdds cswga({ s1, s2 }, ss, ss);
    ProbabilityTest pt(10, 0, 100, 100000);
    std::cout << pt(d) << std::endl;
    std::cout << pt(s1) << std::endl;
    std::cout << pt(ss) << std::endl;
    std::cout << pt(cswg) << std::endl;
    std::cout << pt(cswa) << std::endl;
    std::cout << pt(cswga) << std::endl;
    return 0;
}
