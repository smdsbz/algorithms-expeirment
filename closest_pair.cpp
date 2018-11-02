#include <iostream>
using std::cout; using std::cin; using std::endl;
#include <string>
using std::string; using std::to_string;
#include <vector>
using std::vector;
#include <array>
using std::array;

// #include "common_algs.hpp"
#include <cmath>
using std::pow; using std::sqrt;
#include <algorithm>
using std::sort;


template <class DATA_T>
class Point {

    const DATA_T    x;
    const DATA_T    y;

public:

    Point(DATA_T x, DATA_T y) : x(x), y(y) { return; }

    virtual ~Point(void) { return; }

    virtual Point &operator =(const Point &other) {
        *(DATA_T *)&this->x = other.x;
        *(DATA_T *)&this->y = other.y;
        return *this;
    }

    virtual DATA_T getX(void) const { return this->x; }

    virtual DATA_T getY(void) const { return this->y; }

    virtual string str(void) const {
        return (
            string("(") + to_string(this->x) + string(", ")
            + to_string(this->y) + string(")")
        );
    }

    static bool leqX(
        const Point<DATA_T> &lhs,
        const Point<DATA_T> &rhs
    ) {
        return lhs.x <= rhs.x;
    }

    static bool leqY(
        const Point<DATA_T> &lhs,
        const Point<DATA_T> &rhs
    ) {
        return lhs.y <= rhs.y;
    }

    static double getL2Distance(
        const Point<DATA_T> &lhs,
        const Point<DATA_T> &rhs
    ) {
        return sqrt(
            pow(lhs.getX() - rhs.getX(), 2)
            + pow(lhs.getY() - rhs.getY(), 2)
        );
    }

};

typedef Point<int> iPoint;


class ClosestPair {

    vector<iPoint> points = {
        iPoint(51, 92), iPoint(42, 32), iPoint(-32, 35), iPoint(23, 3),
        iPoint(52, 1)
    };

public:

    static bool isIn(
        iPoint *key,
        vector<iPoint *> pool
    ) {
        for (auto &point : pool) {
            if (key == point) { return true; }
        }
        return false;
    }

    static bool isInVertBand(
        iPoint *ppoint,
        double mid_x,
        double delta
    ) {
        int x_coord = ppoint->getX();
        return (
            (x_coord >= mid_x - delta)
            && (x_coord <= mid_x + delta)
        );
    }

    static double getClosestPair(
        vector<iPoint *> x_sorted,
        vector<iPoint *> y_sorted
    );

public:

    ClosestPair(void) { return; }
    ~ClosestPair(void) { return; }

    void ClosestPair::solve(void) {

        cout << "Here's all the points:" << endl;
        for (auto &point : this->points) {
            cout << point.str() << endl;
        }

        cout << endl;

        // get pre-sort x-array and y-array
        // HACK: use address to uniquely identify Point
        vector<iPoint *> x_sorted;
        sort(this->points.begin(), this->points.end(), iPoint::leqX);
        for (auto &point : this->points) {
            x_sorted.push_back(&point);
        }
        vector<iPoint *> y_sorted;
        sort(this->points.begin(), this->points.end(), iPoint::leqY);
        for (auto &point : this->points) {
            y_sorted.push_back(&point);
        }

        cout << "Distance between closest pair: "
            << ClosestPair::getClosestPair(x_sorted, y_sorted) << endl;

        iPoint r1(52, 1), r2(23, 3);
        cout << "Distance between "
            << r1.str() << " and " << r2.str()
            << " is " << iPoint::getL2Distance(r1, r2) << endl;

        return;
    }


};


double ClosestPair::getClosestPair(
    vector<iPoint *> x_sorted,
    vector<iPoint *> y_sorted
) {
    // simplest case return
    unsigned range = x_sorted.size();
    if (range <= 3) {     // NOTE: promised larger than 1
        double dist_0_1 = iPoint::getL2Distance(*x_sorted[0], *x_sorted[1]);
        if (range == 2) {
            return dist_0_1;
        }
        double dist_0_2 = iPoint::getL2Distance(*x_sorted[0], *x_sorted[2]),
            dist_1_2 = iPoint::getL2Distance(*x_sorted[1], *x_sorted[2]);
        double min_dist = (dist_0_1 < dist_0_2) ? dist_0_1 : dist_0_2;
        min_dist = (min_dist < dist_1_2) ? min_dist : dist_1_2;
        return min_dist;
    }
    // split problem set
    // make pl and pr, i.e., xl and xr
    unsigned split_idx = (range - 1) / 2 + 1;   // NOTE: split_idx goes to right
    double split_x_coord = static_cast<double>(
        x_sorted[split_idx - 1]->getX()
        + x_sorted[split_idx]->getX()
    ) / 2.0;
    vector<iPoint *> xl, xr;
    for (unsigned idx = 0; idx != split_idx; ++idx) {
        xl.push_back(x_sorted[idx]);
    }
    for (unsigned idx = split_idx; idx != range; ++idx) {
        xr.push_back(x_sorted[idx]);
    }
    // make yl and yr, keep order
    vector<iPoint *> yl, yr;
    for (auto &ppoint : y_sorted) {
        if (ClosestPair::isIn(ppoint, xl)) {
            yl.push_back(ppoint);
        } else {
            yr.push_back(ppoint);
        }
    }
    // recursive call
    double delta_l = ClosestPair::getClosestPair(xl, yl);
    double delta_r = ClosestPair::getClosestPair(xr, yr);
    double min_delta = (delta_l < delta_r) ? delta_l : delta_r;
    // merge step
    // focus on points in vertical band
    vector<iPoint *> y_in_range;
    for (auto &ppoint : y_sorted) {
        if (ClosestPair::isInVertBand(ppoint, split_x_coord, min_delta)) {
            y_in_range.push_back(ppoint);
        }
    }
    unsigned y_in_range_len = y_in_range.size();
    unsigned y_in_range_one_less_len = y_in_range_len - 1;
    // find minimum with delta_mid considered
    for (unsigned offset = 0; offset != y_in_range_one_less_len; ++offset) {
        for (unsigned other_offset = offset + 1,
                __virtrange = other_offset + 8,
                other_range = (
                    (__virtrange < y_in_range_len) ?
                    (__virtrange) : y_in_range_len
                ); other_offset != other_range; ++other_offset) {
            double delta_pair = iPoint::getL2Distance(
                *y_in_range[offset],
                *y_in_range[other_offset]
            );
            if (delta_pair < min_delta) {
                min_delta = delta_pair;
            }
        }
    }
    return min_delta;
}


/******* Main *******/

int main(void) {
    ClosestPair().solve();
    return 0;
}
