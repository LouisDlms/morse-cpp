#include "Tree.h"

Tree::Tree() {}

int Tree::char_to_path(char& c) {
    unsigned int path = 1; // We have to start with a 1, else the bit push to the left doesn't work
    for(int i = 1; i<=this->_tree_length; i++) {
        // Search the character in the tree
        if(this->_tree[i-1] == c) {
            int j = i;
            while(j != 0) {
                path = path << 1; // Push to the left
                if(j%2 == 0) {
                    path = path | 1; // If we are in the right branch (taa), we put a 1 in the binary word
                    j = (j-2)/2;
                } else {
                    j = (j-1)/2; // Else we let at 0
                }
            }
        }
    }
    path = (path == 1) ? 0 : path; // If the character isn't in the tree, return path = 0
    // Binary path : 0 = left (ti) - 1 = right (taa)
    return path;
}

char Tree::path_to_char(int& path) {
    // Not a binary path !! but the exact position of the character in the tree
    return this->_tree[path];
}