#ifndef _WAV_H_
#define _WAV_H_

#include <iostream>

// Wav Header: stock all the informations relative to the file we have to decode (encoding parameters)
typedef struct WAV_HEADER{
    char                RIFF[4];        // RIFF Header      Magic header
    unsigned int       ChunkSize;      // RIFF Chunk Size  
    char                WAVE[4];        // WAVE Header      
    char                fmt[4];         // FMT header       
    unsigned int       Subchunk1Size;  // Size of the fmt chunk                                
    unsigned short      AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM 
    unsigned short      NumOfChan;      // Number of channels 1=Mono 2=Sterio                   
    unsigned int       SamplesPerSec;  // Sampling Frequency in Hz                             
    unsigned int       bytesPerSec;    // bytes per second 
    unsigned short      blockAlign;     // 2=16-bit mono, 4=16-bit stereo 
    unsigned short      bitsPerSample;  // Number of bits per sample      
    char                Subchunk2ID[4]; // "data"  string   
    unsigned int       Subchunk2Size;  // Sampled data length    

} wav_hdr;

class Wav {
    public:
        Wav();
        static std::ostream& write_word(std::ostream& outs, int value, unsigned size = sizeof(int));
};

#endif