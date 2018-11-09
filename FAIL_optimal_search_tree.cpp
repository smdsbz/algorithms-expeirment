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


class Node {
public:

    unsigned        id;
    Node           *left;
    Node           *right;

    Node(unsigned id, Node *left = 0, Node *right = 0)
            : id(id), left(left), right(right) {
        return;
    }
    ~Node(void) {
        if (this->left) {
            delete this->left;
        }
        if (this->right) {
            delete this->right;
        }
        this->left = 0;
        this->right = 0;
        return;
    }

    const std::string str(void) {
        return str_k_(this->id);
    }

};


class BinarySearchTree {
public:

    Node   *root;

    BinarySearchTree(Node *root = 0) : root(root) { return; }
    ~BinarySearchTree(void) {
        if (this->root) {
            delete this->root;
        }
        this->root = 0;
        return;
    }

    static void _traverse_child(Node *parent, Node *child, bool is_left) {
        if (child == 0) {
            if (is_left) {
                std::cout << str_d_(parent->id - 1) << " is "
                    << parent->str() << "'s left child" << std::endl;
            } else {
                std::cout << str_d_(parent->id) << " is "
                    << parent->str() << "'s right child" << std::endl;
            }
        } else {
            if (is_left) {
                std::cout << child->str() << " is " << parent->str()
                    << "'s left child" << std::endl;
            } else {
                std::cout << child->str() << " is " << parent->str()
                    << "'s right child" << std::endl;
            }
            BinarySearchTree::_traverse_child(child, child->left, true);
            BinarySearchTree::_traverse_child(child, child->right, false);
        }
        return;
    }

    void traverse(void) {
        std::cout << this->root->str() << " is root node" << std::endl;
        BinarySearchTree::_traverse_child(this->root, this->root->left, true);
        BinarySearchTree::_traverse_child(this->root, this->root->right, false);
        return;
    }

};


void _construct_tree(BinarySearchTree &tree, root_table_t &tab,
        Node *split, unsigned from, unsigned to,
        _ConstructMode mode) {
    // if (mode != ROOT) {
    //     std::cout << "split: " << split->str() << std::endl;
    // } else {
    //     std::cout << "split: (root)" << std::endl;
    // }
    // std::cout << "from: " << from << std::endl;
    // std::cout << "to: " << to << std::endl;
    // if (mode == ROOT) {
    //     std::cout << "mode: root" << std::endl;
    // } else if (mode == LEFT) {
    //     std::cout << "mode: left" << std::endl;
    // } else if (mode == RIGHT) {
    //     std::cout << "mode: right" << std::endl;
    // }
    // std::getchar();

    // simplest case return: leaf node
    if (from > to) {
        return;
    }

    // normal cases
    unsigned new_split_num = get_item(tab, from, to);
    switch (mode) {
        case LEFT: {
            // std::cout << new_split_num << " left to "; std::cout << split->str() << std::endl;
            split->left = new Node(new_split_num);
            split = split->left;
            break;
        }
        case RIGHT: {
            // std::cout << new_split_num << " right to "; std::cout << split->str() << std::endl;
            split->right = new Node(new_split_num);
            split = split->right;
            break;
        }
        case ROOT: {
            tree.root = new Node(new_split_num);
            split = tree.root;
            break;
        }
        throw std::runtime_error("should not reach this line");
    }

    _construct_tree(tree, tab, split, from, new_split_num - 1, LEFT);
    _construct_tree(tree, tab, split, new_split_num + 1, to, RIGHT);

    return;
}


void construct_optimal_bst(root_table_t tab) {
    BinarySearchTree tree;
    _construct_tree(tree, tab, 0, 1, tab.size(), ROOT);
    tree.traverse();
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
