/* #include "include/Tree.h" */
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const unsigned int MORSE_TREE_LENGTH = 30;
const char MORSE_TREE [] {'E', 'T', 'I', 'A', 'N', 'M', 'S', 'U', 'R', 'W', 'D', 'K', 'G', 'O', 'H', 'V', 'F', '\0', 'L', '\0', 'P', 'J', 'B', 'X', 'C', 'Y', 'Z', 'Q', '\0', '\0'};

// C4 NOTE
constexpr double two_pi = 6.283185307179586476925286766559;
constexpr double max_amplitude = 32760;  // "volume"

double hz        = 44100;    // samples per second
double frequency = 300;  // middle C
double seconds   = 0.1;      // duree d'un point

ostream& write_word(ostream& outs, int value, unsigned size = sizeof(int) ) {
    for (; size; --size, value >>= 8)
        outs.put( static_cast <char> (value & 0xFF) );
    return outs;
}

void write_space(ofstream& f, int nb_points) {
    int N = hz*nb_points*seconds;
    for (int n = 0; n < N; n++)
    {
        write_word( f, 0, 2 );
        write_word( f, 0, 2 );
    }
}

void write_morse(ofstream& f, char c) {
    unsigned int path = 1;
    for(int i = 1; i<=MORSE_TREE_LENGTH; i++) {
        if(MORSE_TREE[i-1] == c) {
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

    cout << c << " : ";

    for(int i = 0; i<(int)log2(path); i++) {
        bool point = (path & (1<<i)) == 0;
        cout << (int)!point;
        
        int N = hz*seconds;
        N *= point ? 1 : 3;  // total number of samples, on multiplie par le nb de points nécessaire
        for (int n = 0; n < N; n++)
        {
            double amplitude = (double)n / N * max_amplitude;
            double value     = sin( (two_pi * n * frequency) / hz );
            write_word( f, (int)(                 amplitude  * value), 2 );
            write_word( f, (int)((max_amplitude - amplitude) * value), 2 );
        }

        write_space(f, 1);
    }
    cout << endl;
}

void encode_from_file(string& file) {
    // check si file exist
    // message = readfile(*argv[2])
    // encode(message)
}

// Encode un message -> audio
void encode(string& message) {
    /* Tree* tree = Tree::create_morse_tree(); */

    // ENCODING
    ofstream f("output.wav", ios::binary);

    // 1. Write the file headers
    f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
    write_word(f,     16, 4 );  // no extension data
    write_word(f,      1, 2 );  // PCM - integer samples
    write_word(f,      2, 2 );  // two channels (stereo file)
    write_word(f,  44100, 4 );  // samples per second (Hz)
    write_word(f, 176400, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8
    write_word(f,      4, 2 );  // data block size (size of two integer samples, one for each channel, in bytes)
    write_word(f,     16, 2 );  // number of bits per sample (use a multiple of 8)

    // Write the data chunk header
    size_t data_chunk_pos = f.tellp();
    f << "data----";  // (chunk size to be filled in later)
    
    // 2. Write the audio samples
    // Reading each letter of the message and encoding using the tree
    const int message_length = message.length();

    for(int i = 0; i < message_length; i++) {
        char c = message[i];
        if(c == ' ') {
            write_space(f, 7);
        } else {
            write_morse(f, c);
            if(message[i+1] != ' ') {
                write_space(f, 2 ); // 2 + 1 = pause de 3 points entre chaque lettre
            }
        }
    }
    
    // 3. Write the file footer
    // (We'll need the final file size to fix the chunk sizes above)
    size_t file_length = f.tellp();

    // Fix the data chunk header to contain the data size
    f.seekp( data_chunk_pos + 4 );
    write_word( f, file_length - data_chunk_pos + 8 );

    // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
    f.seekp( 0 + 4 );
    write_word( f, file_length - 8, 4 );
}

// Décode un audio -> message
void decode(string& file) {
    // Check si le fichier existe bien

   /*  Tree* tree = Tree::create_morse_tree(); */
}

int main(int argc, char* argv[]) {
    if(argc < 3) {
        // std::cout << Message d'erreur
        return 1;
    }

    string arg;
    arg.assign(argv[1]);

    if(arg == "-e") {
        arg.assign(argv[2]);
        if(arg == "-f") {
            if(argc == 3) {
                return 1;
            }
            arg.assign(argv[3]);
            encode_from_file(arg);
        }
        arg.assign(argv[2]);
        cout << arg << endl;
        encode(arg);
    } else if(arg == "-ef") {
        arg.assign(argv[3]);
        encode_from_file(arg);
    } else if(arg == "-d") {
        arg.assign(argv[2]);
        decode(arg);
    } else {
        return 1;
    }

    return 0;
}