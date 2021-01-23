#include "Wav.h"
#include "Latin.h"
#include <cmath>
#include <fstream>

using namespace std;

class Encode{
    protected:
        Tree* _tree;
        // C4 NOTE
        const double _two_pi = 6.283185307179586476925286766559;
        const double _max_amplitude = 32760;  // "volume"
        const double _hz        = 44100;    // samples per second
        const double _frequency = 300;  // middle C
    
    public:
        Encode();
        Encode(Tree* tree);
        void write_space(ofstream& f, double& ti, int nb_points);
        void write_morse(ofstream& f, double& ti, char& c);
        void encode(string& message, double& ti);
        void encode_from_file(string& path, double& ti);
};