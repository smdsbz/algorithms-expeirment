#include <iostream>
#include <stdexcept>
#include <string>
#include <iterator>
#include <vector>
#include <queue>
#include <array>

std::string str_k_(unsigned x) {
    return std::string("k_") + std::to_string(x);
}

std::string str_d_(unsigned x) {
    return std::string("d_") + std::to_string(x);
}

typedef std::vector<std::vector<unsigned> > root_table_t;
typedef std::array<unsigned, 3> triplet;    // { from, split, to }

unsigned &get_item(root_table_t    &tab,
                   size_t           i,
                   size_t           j) {
    size_t n = tab.size();
    size_t col_len = tab[i - 1].size();
    return tab[i - 1][n - j];
}

enum _ConstructMode { LEFT, RIGHT, ROOT };

void _construct_tree(root_table_t &tab,
        unsigned split, unsigned from, unsigned to,
        _ConstructMode mode) {
    /**
     * Note:
     * While `mode` is `ROOT`, `split` is ignored
     */

    // simplest case return: leaf node
    if (from > to) {
        switch (mode) {
            case LEFT: {
                std::cout << str_d_(to) << " is " << str_k_(to + 1)
                    << "'s left child" << std::endl;
                break;
            }
            case RIGHT: {
                std::cout << str_d_(from - 1) << " is " << str_k_(from - 1)
                    << "'s right child" << std::endl;
                break;
            }
        }
        return;
    }

    // normal cases
    unsigned new_split_num = get_item(tab, from, to);
    switch (mode) {
        case LEFT: {
            std::cout << str_k_(new_split_num) << " is " << str_k_(split)
                << "'s left child" << std::endl;
            split = new_split_num;
            break;
        }
        case RIGHT: {
            std::cout << str_k_(new_split_num) << " is " << str_k_(split)
                << "'s right child" << std::endl;
            split = new_split_num;
            break;
        }
        case ROOT: {
            std::cout << str_k_(new_split_num) << " is root" << std::endl;
            split = new_split_num;
            break;
        }
        throw std::runtime_error("should not reach this line");
    }

    _construct_tree(tab, split, from, new_split_num - 1, LEFT);
    _construct_tree(tab, split, new_split_num + 1, to, RIGHT);

    return;
}


void construct_optimal_bst(root_table_t tab) {
    _construct_tree(tab, 0, 1, tab.size(), ROOT);
    return;
}


int main(void) {

    unsigned i_1[] = { 2, 2, 2, 1, 1 };
    unsigned i_2[] = { 4, 2, 2, 2 };
    unsigned i_3[] = { 5, 4, 3 };
    unsigned i_4[] = { 5, 4 };
    unsigned i_5[] = { 5 };
    root_table_t tab;
    tab.push_back(std::vector<unsigned>(std::begin(i_1), std::end(i_1)));
    tab.push_back(std::vector<unsigned>(std::begin(i_2), std::end(i_2)));
    tab.push_back(std::vector<unsigned>(std::begin(i_3), std::end(i_3)));
    tab.push_back(std::vector<unsigned>(std::begin(i_4), std::end(i_4)));
    tab.push_back(std::vector<unsigned>(std::begin(i_5), std::end(i_5)));

    construct_optimal_bst(tab);

    return 0;
}
