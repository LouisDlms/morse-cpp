#include "Tree.h"
#include <iostream>
#include <fstream>

using namespace std;

Tree* create_morse_tree() {
    Tree* tree = new Tree('ET');

    //TODO : Création de l'arbre de décodage, en partant du bas ?
    return tree;
}

void encode_from_file(char& file) {
    // check si file exist
    // message = readfile(*argv[2])
    // encode(message)
}

// Encode un message -> audio
void encode(char& e) {
    Tree* tree = create_morse_tree();
}

// Décode un audio -> message
void decode(char& file) {
    // Check si le fichier existe bien

    Tree* tree = create_morse_tree();
}

int main(int argc, char* argv[]) {
    if(argc < 3) {
        // std::cout << Message d'erreur
        return 1;
    }

    switch(*argv[1]) {
        case '-e':
            if(*argv[2] == '-f') {
                if(argc == 3) {
                    return 1;
                }
                encode_from_file(*argv[3]);
            }
            encode(*argv[2]);
            break;
        case '-ef':
            encode_from_file(*argv[3]);
            break;
        case '-d':
            decode(*argv[2]);
            break;
        default:
            return 1;
    }

    return 0;
}