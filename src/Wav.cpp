#include "Wav.h"

Wav::Wav() {}

std::ostream& Wav::write_word(std::ostream& outs, int value, unsigned size) {
    for (; size; --size, value >>= 8)
        outs.put( static_cast <char> (value & 0xFF) );
    return outs;
}