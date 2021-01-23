#include "Decode.h"

Decode::Decode() {
    Latin* tree = new Latin();
    this->_tree = tree;
}

Decode::Decode(Tree* tree): _tree(tree) {}

void Decode::decode(string& path, double& ti) {
    cout << "Decoding wave file " << path << "..." << endl; 
    FILE* file = fopen(path.c_str(), "r");
    if (file == nullptr)
    {
        fprintf(stderr, "Unable to open wave file: %s\n", path);
    } else {
        wav_hdr wavHeader;
        int headerSize = sizeof(wav_hdr);
        size_t bytesRead = fread(&wavHeader, 1, headerSize, file);
        cout << "Success! Header Read " << bytesRead << " bytes." << endl << "-------------------------" << endl << "Header:" << endl;
        if (bytesRead > 0) {
            cout << "RIFF header                :" << wavHeader.RIFF[0] << wavHeader.RIFF[1] << wavHeader.RIFF[2] << wavHeader.RIFF[3] << endl;
            cout << "WAVE header                :" << wavHeader.WAVE[0] << wavHeader.WAVE[1] << wavHeader.WAVE[2] << wavHeader.WAVE[3] << endl;
            cout << "FMT                        :" << wavHeader.fmt[0] << wavHeader.fmt[1] << wavHeader.fmt[2] << wavHeader.fmt[3] << endl;
            cout << "Data size                  :" << wavHeader.ChunkSize << endl;

            // Display the sampling Rate from the header
            cout << "Sampling Rate              :" << wavHeader.SamplesPerSec << endl;
            cout << "Number of bits used        :" << wavHeader.bitsPerSample << endl;
            cout << "Number of channels         :" << wavHeader.NumOfChan << endl;
            cout << "Number of bytes per second :" << wavHeader.bytesPerSec << endl;
            cout << "Data length                :" << wavHeader.Subchunk2Size << endl;
            cout << "Audio Format               :" << wavHeader.AudioFormat << endl;

            cout << "Block align                :" << wavHeader.blockAlign << endl;
            cout << "Data string                :" << wavHeader.Subchunk2ID[0] << wavHeader.Subchunk2ID[1] << wavHeader.Subchunk2ID[2] << wavHeader.Subchunk2ID[3] << endl;

            //Read the data
            int bytesPerSample = wavHeader.bitsPerSample / 8; //Number of bytes per sample
            
            // Supposons qu'on connaisse la durée d'un ti
            char* buffer = new char[bytesPerSample];
            int N = wavHeader.NumOfChan * wavHeader.SamplesPerSec * ti;
            int nb = wavHeader.Subchunk2Size / ((wavHeader.bitsPerSample / 8)*N);
            bool* amp = new bool[nb];
            amp[0] = 1;
            int k = 1;

            // Decodage 0-1
            cout << "-------------------------" << endl << "Data: " << amp[0];
            while (!fseek(file, bytesRead + N/2 + bytesPerSample*k*(N+1), SEEK_SET) && (fread(buffer, bytesPerSample, 1, file) > 0))
            {
                for(int i = 0; i<bytesPerSample; i++) {
                    amp[k] = buffer[i] != 0;
                }
                cout << amp[k];
                k++;
            }
            cout << endl << "-------------------------" << endl << "Message: ";
            delete [] buffer;
            buffer = nullptr;

            bool sw = 1;
            int count = 0;
            int path = 0;
            // From 0-1 to Morse
            for(int i = 0; i<nb; i++) {
                if(amp[i] == sw) {
                    count++;
                } else {
                    if(sw) {
                        // Lettre MORSE
                        switch(count) {
                            case 1:
                                path = 2*path+1;
                                break;
                            case 3:
                                path = 2*(path+1);
                                break;
                            default:
                                throw logic_error("Invalid morse. Impossible to decode.");
                                break;
                        }
                    } else {
                        // Chgmt lettre / Espace
                        switch(count) {
                            case 1:
                                break;
                            case 3:
                                path--;
                                cout << this->_tree->path_to_char(path);
                                path = 0;
                                break;
                            case 7:
                                path--;
                                cout << this->_tree->path_to_char(path);
                                cout << " ";
                                path = 0;
                                break;
                            default:
                                throw logic_error("Invalid morse. Impossible to decode.");
                                break;
                        }
                    }   
                    sw = !sw;
                    count = 1;
                }
            }
            path--;
            cout << this->_tree->path_to_char(path) << endl;
        }
        fclose(file);
    }
}