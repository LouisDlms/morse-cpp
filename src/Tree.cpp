#include "Tree.h"

Tree::Tree() {}

int Tree::char_to_path(char& c) {
    unsigned int path = 1;
    for(int i = 1; i<=this->_tree_length; i++) {
        if(this->_tree[i-1] == c) {
            int j = i;
            while(j != 0) {
                path = path << 1; // on décale vers la gauche
                if(j%2 == 0) {
                    path = path | 1; // on met 1 au bit le plus faible si on est à droite
                    j = (j-2)/2;
                } else {
                    j = (j-1)/2;
                }
            }
        }
    }
    return path;
}

char Tree::path_to_char(int& path) {
    // Pas le même path que dans la fonction char_to_morse: ici est attendu la position exacte du caractère dans l'arbre
    return this->_tree[path];
}