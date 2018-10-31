#include <iostream>
using std::cout; using std::cin; using std::endl;
#include <vector>
using std::vector;

#include <cstdlib>
#include <ctime>
using std::srand; using std::rand; using std::time;

#include "common_algs.hpp"


/******* Implementations *******/

int
randint(int lower,
        int upper) {
    srand(time(nullptr));
    int span = upper - lower;
    return (rand() % span) + lower;
}


template <typename DATA_T>
void
print_vector(vector<DATA_T>    &src,
             const char        *end) {
    unsigned range = src.size();
    unsigned range_off_one = range - 1;
    for (unsigned idx = 0; idx != range; ++idx) {
        cout << src[idx];
        if (idx != range_off_one) {
            cout << " ";
        }
    }
    cout << end;
    return;
}


template <typename DATA_T>
unsigned
partition(vector<DATA_T>   &src,
          const unsigned    left,
          const unsigned    right,
          const bool        random) {
    /**
     * Note:
     * `left`, `right` are inclusive!!!
     */
    // choose split value
    unsigned split = left;
    if (random) {
        split = randint(left, right);
    }
    // split sub-array
    DATA_T &split_val = src[split];
    DATA_T temp;
    unsigned leftidx = left;
    unsigned rightidx = right;
    // part elements
    while (leftidx != rightidx) {
        if (src[leftidx] <= split_val) {
            ++leftidx;
        } else if (src[rightidx] > split_val) {
            --rightidx;
        } else {
            temp = src[leftidx];
            src[leftidx] = src[rightidx];
            src[rightidx] = temp;
        }
    }
    // place split element
    if (src[leftidx] <= split_val) {
        temp = src[leftidx];
        src[leftidx] = split_val;
        split_val = temp;
    }
    print_vector(src);
    return leftidx;
}


template <typename DATA_T>
vector<DATA_T> &
__quick_sort_recblk(vector<DATA_T>  &src,
                    unsigned         left,
                    unsigned         right) {
    if (left == right) {
        return src;
    }
    unsigned splitidx = partition(src, left, right, /*random=*/false);
    __quick_sort_recblk(src, left, splitidx - 1);
    __quick_sort_recblk(src, splitidx, right);
    return src;
}


template <typename DATA_T>
vector<DATA_T> &
quick_sort(vector<DATA_T> &src) {
    __quick_sort_recblk(src, 0, src.size() - 1);
    return src;
}


/******* Unit Test *******/

// #define TEST
#ifdef  TEST

int main(void) {
    vector<int> arr = {2, 4, 1, 32, 6, 123, 6};
    quick_sort(arr);
    print_vector(arr);
    return 0;
}

#undef  TEST
#endif
