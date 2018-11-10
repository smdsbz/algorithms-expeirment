#include <iostream>
#include <iomanip>
#include <limits>
#include <iterator>
#include <array>


const unsigned n = 5;

typedef int weight_t;
typedef std::array<weight_t, n> weight_row_t;
typedef std::array<weight_row_t, n> weight_matrix_t;

typedef std::array<std::array<int, n>, n> precursor_matrix_t;

const weight_t pos_infty = std::numeric_limits<weight_t>::max() / 2;    // HACK: `/2` to allow two infty add up
const int nil = -1;

weight_matrix_t W{
   weight_row_t{ 0, 3, 8, pos_infty, -4 },
   weight_row_t{ pos_infty, 0, pos_infty, 1, 7 },
   weight_row_t{ pos_infty, 4, 0, pos_infty, pos_infty },
   weight_row_t{ 2, pos_infty, -5, 0, pos_infty },
   weight_row_t{ pos_infty, pos_infty, pos_infty, 6, 0 }
};


class Solution {
public:

    weight_matrix_t    W;
    precursor_matrix_t P;

};


Solution floyd_warshall(weight_matrix_t W) {
    unsigned n = W.size();
    // initialized precursor matrix
    precursor_matrix_t P;
    for (unsigned i = 0; i != n; ++i) {
        for (unsigned j = 0; j != n; ++j) {
            if (i == j) {
                P[i][j] = nil;
            } else if (W[i][j] >= pos_infty) {
                P[i][j] = nil;
            } else {
                P[i][j] = i + 1;
            }
        }
    }

    // Floyd-Warshall Algorithm
    weight_matrix_t D_last{W};
    weight_matrix_t D_new;
    for (unsigned k = 0; k != n; ++k) {
        for (unsigned i = 0; i != n; ++i) {
            for (unsigned j = 0; j != n; ++j) {
                D_new[i][j] = D_last[i][j];
                weight_t temp = D_last[i][k] + D_last[k][j];
                if (temp < D_new[i][j]) {
                    D_new[i][j] = temp;
                    P[i][j] = P[k][j];
                }
            }
        }   // end for i, j
        D_last = D_new;
    }   // end for k
    // end of F-W Alg.

    Solution solution;
    solution.W = D_new;
    solution.P = P;
    return solution;
}


int main(void) {

    Solution solution = floyd_warshall(W);

    std::cout << "D^{(n)} matrix:" << std::endl;
    for (auto &row : solution.W) {
        for (auto &each : row) {
            std::cout << std::setw(8) << std::right << each;
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;;

    std::cout << "P^{(n)} matrix:" << std::endl;
    for (auto &row : solution.P) {
        for (auto &each : row) {
            if (each == nil) {
                std::cout << std::setw(8) << std::right << "nil";
            } else {
                std::cout << std::setw(8) << std::right << each;
            }
        }
        std::cout << std::endl;
    }

    return 0;
}
