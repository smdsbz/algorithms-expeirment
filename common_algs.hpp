#ifndef __COMMON_ALGS_HPP__
#define __COMMON_ALGS_HPP__

// use `vector`s
#include <vector>

// random number generator
#include <cstdlib>
#include <ctime>

/******* Helper Functions *******/

/**
 * Returns a random integer in range [lower, upper).
 */
int randint(int lower, int upper);

/**
 * Prints a vector of type `T` to stdout.
 *
 * 2 spaces between elements, ends with `end`
 */
template <typename T>
void print_vector(std::vector<T>   &src,
                  const char       *end="\n");

/******* Algorithms *******/

/**
 * Split given vector `src` from `left` to `right` (inclusive), returns index
 * of the split position, where elements left of split position are all *less
 * than or equal to* split element, elements right of split position are all
 * *greater than* split element.
 */
template <typename T>
unsigned partition(std::vector<T>   &src,
                   const unsigned    left,
                   const unsigned    right,
                   const bool        random = false);

/**
 * The Quick Sort algorithm.
 */
template <typename T>
std::vector<T> & quick_sort(std::vector<T>  &src);

#endif
