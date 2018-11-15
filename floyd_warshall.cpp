#include <iostream>
#include <iomanip>
#include <limits>
#include <iterator>
#include <array>
#include <vector>


const unsigned n = 5;

typedef int weight_t;
typedef std::array<weight_t, n> weight_row_t;
typedef std::array<weight_row_t, n> weight_matrix_t;

typedef std::array<std::array<int, n>, n> precursor_matrix_t;

const weight_t pos_infty = std::numeric_limits<weight_t>::max() / 2;    // HACK: `/2` to allow two infty add up
const int nil = -1;


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
    weight_matrix_t D{W};
    for (unsigned k = 0; k != n; ++k) {
        for (unsigned i = 0; i != n; ++i) {
            for (unsigned j = 0; j != n; ++j) {
                weight_t temp;
                if (D[i][k] >= pos_infty || D[k][j] >= pos_infty) {
                    temp = pos_infty;
                } else {
                    temp = D[i][k] + D[k][j];
                }
                if (temp < pos_infty && temp < D[i][j]) {
                    D[i][j] = temp;
                    P[i][j] = P[k][j];
                }
            }
        }   // end for i, j
    }   // end for k
    // end of F-W Alg.

    Solution solution;
    solution.W = D;
    solution.P = P;
    return solution;
}


int main(void) {

    std::vector<weight_matrix_t> testcase;

    weight_matrix_t W_1{
        weight_row_t{ 0, 3, 8, pos_infty, -4 },
        weight_row_t{ pos_infty, 0, pos_infty, 1, 7 },
        weight_row_t{ pos_infty, 4, 0, pos_infty, pos_infty },
        weight_row_t{ 2, pos_infty, -5, 0, pos_infty },
        weight_row_t{ pos_infty, pos_infty, pos_infty, 6, 0 }
    };
    testcase.push_back(W_1);

    weight_matrix_t W_2{
        weight_row_t{ 0, 123, pos_infty, pos_infty, pos_infty },
        weight_row_t{ pos_infty, 0, pos_infty, pos_infty, pos_infty },
        weight_row_t{ pos_infty, pos_infty, 0, pos_infty, pos_infty },
        weight_row_t{ pos_infty, pos_infty, pos_infty, 0, pos_infty },
        weight_row_t{ pos_infty, pos_infty, pos_infty, pos_infty, 0 }
    };
    testcase.push_back(W_2);


    for (auto &W : testcase) {

        std::cout << "W matrix:" << std::endl;
        for (auto &row : W) {
            for (auto &each : row) {
                if (each >= pos_infty) {
                    std::cout << std::setw(8) << std::right << "infty";
                } else {
                    std::cout << std::setw(8) << std::right << each;
                }
            }
            std::cout << std::endl;
        }

        Solution solution = floyd_warshall(W);

        std::cout << "D^{(n)} matrix:" << std::endl;
        for (auto &row : solution.W) {
            for (auto &each : row) {
                if (each < pos_infty) {
                    std::cout << std::setw(8) << std::right << each;
                } else {
                    std::cout << std::setw(8) << std::right << "infty";
                }
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

        std::cout << "=====================" << std::endl;

    }

    return 0;
}
