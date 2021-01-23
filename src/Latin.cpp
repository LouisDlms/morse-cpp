#include "Latin.h"

Latin::Latin() : Tree() {
    this->_tree_length = 62;
    char* tree = new char[this->_tree_length]                                               {'E', 'T',
                                                                                        'I', 'A', 'N', 'M',
                                                                            'S', 'U', 'R', 'W', 'D', 'K', 'G', 'O',
                                                    'H', 'V', 'F', '\0', 'L', '\0', 'P', 'J', 'B', 'X', 'C', 'Y', 'Z', 'Q', '\0', '\0',
    '5', '4', '\0', '3', '\0', '\0', '\0', '2', '\0', '\0', '+', '\0', '\0', '\0', '\0', '1', '6', '=', '/', '\0', '\0', '\0', '\0', '\0', '7', '\0', '\0', '\0', '8', '\0', '9', '0'};
    // Structure d'arbre binaire implicite: les fonctions de conversion morse/caractère permettent de le parcourir aisément
    this->_tree = tree;
}