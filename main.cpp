/* #include "include/Tree.h" */
#include <iostream>
#include <fstream>
#include <cmath>
#include "Encode.h"
#include "Decode.h"

using namespace std;

#pragma once

int main(int argc, char* argv[]) {
    if(argc < 2) {
        throw invalid_argument("Encode: ./morse -e <message> OR -e -f <file: default is input.txt> OR -ef <file: default is input.txt>\nDecode: ./morse -d <file: default is output.wav>");
        return 1;
    }

    Latin* tree = new Latin();
    Encode ENCODE(tree);
    Decode DECODE(tree);

    string arg;
    arg.assign(argv[1]);
    double ti;

    if(arg == "-e") {
        if(argc == 2) {
            throw invalid_argument("Syntax: ./morse -e <message> <ti: default is 0.1> OR -e -f <file: default is input.txt> <ti: default is 0.1> OR -ef <file: default is input.txt> <ti: default is 0.1>");
            return 1;
        }
        arg.assign(argv[2]);
        if(arg == "-f") {
            arg.assign(argc == 3 ? "input.txt" : argv[3]);
            ti = (argc < 5) ? 0.1 : atof(argv[4]);
            ENCODE.encode_from_file(arg, ti);
        }
        arg.assign(argv[2]);
        ti = (argc < 4) ? 0.1 : atof(argv[3]);
        ENCODE.encode(arg, ti);
    } else if(arg == "-ef") {
        arg.assign(argc == 2 ? "input.txt" : argv[2]);
        ti = (argc < 4) ? 0.1 : atof(argv[3]);
        ENCODE.encode_from_file(arg, ti);
    } else if(arg == "-d") {
        arg.assign(argc == 2 ? "output.wav" : argv[2]);
        ti = (argc < 4) ? 0.1 : atof(argv[3]);
        DECODE.decode(arg, ti);
    } else {
        throw invalid_argument("Encode: ./morse -e <message>  <ti: default is 0.1> OR -e -f <file: default is input.txt> <ti: default is 0.1> OR -ef <file: default is input.txt> <ti: default is 0.1>\nDecode: ./morse -d <file: default is output.wav>");
        return 1;
    }

    return 0;
}