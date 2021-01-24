#include "Encode.h"

Encode::Encode() {
    Latin* tree = new Latin();
    this->_tree = tree;
}

Encode::Encode(Tree* tree) : _tree(tree) {}

void Encode::write_space(ofstream& f, double& ti, int nb_points) {
    // Write 0 during nb_points*ti seconds (for example, a space between Morse characters = 3 points)
    int N = this->_hz*nb_points*ti;
    for (int n = 0; n < N; n++) {
        Wav::write_word( f, 0, 2 );
    }
}

bool Encode::write_morse(ofstream& f, double& ti, char& c) {
    // From alphabet to 0-1 path (cf. Encode.md doc)
    unsigned int path = this->_tree->char_to_path(c);

    if(path != 0) {
        // Read each Morse character (0 = ti / 1 = taa)
        for(int i = 0; i<(int)log2(path); i++) {
            bool point = (path & (1<<i)) == 0;
            
            int N = this->_hz*ti;
            N *= point ? 1 : 3;  // if 0, then it's a ti (left in the binary tree) - if 1, then it's a taa (3 ti) (right in the binary tree)
            for (int n = 0; n < N; n++)
            {
                double amplitude = (double)n / N * this->_max_amplitude;
                double value     = sin( (this->_two_pi * n * this->_frequency) / this->_hz );
                Wav::write_word( f, (int)(amplitude * value), 2 );
            }

            write_space(f, ti, 1); // 1 space between each Morse character
        }
        return 1;
    }
    // If path == 0, then the character isn't in the tree and we ignore it
    return 0;
}

void Encode::encode(string& message, double& ti) {
    cout << "Encoding..." << endl;
    ofstream f("output.wav", ios::binary);

    // 1. Write the file headers
    f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
    Wav::write_word(f,     16, 4 );  // no extension data
    Wav::write_word(f,      1, 2 );  // PCM - integer samples
    Wav::write_word(f,      1, 2 );  // MONO
    Wav::write_word(f,  44100, 4 );  // samples per second (Hz) 
    Wav::write_word(f, 176400, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8
    Wav::write_word(f,      2, 2 );  // 4 / data block size (size of two integer samples, one for each channel, in bytes)
    Wav::write_word(f,     16, 2 );  // number of bits per sample (use a multiple of 8)

    // Write the data chunk header
    size_t data_chunk_pos = f.tellp();
    f << "data----";  // (chunk size to be filled in later)
    
    // 2. Write the audio samples
    // Read each character of the message and encode using the tree
    const int message_length = message.length();

    for(int i = 0; i < message_length; i++) {
        char c = toupper(message[i]);
        if(c == ' ') {
            write_space(f, ti, 6); // 6 + 1 = 7
        } else {
            if(write_morse(f, ti, c) && message[i+1] != ' ') {
                write_space(f, ti, 2); // 2 + 1 = pause de 3 points entre chaque lettre
            }
        }
    }
    
    // 3. Write the file footer
    // (We'll need the final file size to fix the chunk sizes above)
    size_t file_length = f.tellp();

    // Fix the data chunk header to contain the data size
    f.seekp( data_chunk_pos + 4 );
    Wav::write_word( f, file_length - data_chunk_pos + 8 );

    // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
    f.seekp( 0 + 4 );
    Wav::write_word( f, file_length - 8, 4 );

    f.close();

    cout << "Success! Open output.wav to hear the result. Use ./morse -d to decode." << endl;
}

void Encode::encode_from_file(string& path, double& ti) {
    ifstream file(path);
    cout << "Opening text file " << path << "..." << endl;
    if (file.is_open())
    {
        // File opened
        string message;
        getline(file, message);
        cout << "Success! Line to encode: " << message << endl;
        // Encode the message from the file (first line)
        encode(message, ti);
    } else {
        throw invalid_argument("Unable to open text file: " + path);
    }
}