#include "Wav.h"

Wav::Wav() {}

std::ostream& Wav::write_word(std::ostream& outs, int value, unsigned size) {
    // Generic function to write a value into a .WAV file
    for (; size; --size, value >>= 8)
        outs.put( static_cast <char> (value & 0xFF) );
    return outs;
}