#include "Wav.h"
#include "Latin.h"
#include <fstream>

using namespace std;

class Decode: public Wav {
    protected:
        Tree* _tree;
    public:
        Decode();
        Decode(Tree* tree);
        void decode(string& path, double& ti);
};