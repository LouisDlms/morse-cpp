# Morse <-> Latin (or any other) Alphabet

Encode a Message written in Latin Alphabet or any other alphabet that you could translate into a binary tree - to Morse: the output of the program is an audio .wav file

> To encode a message: ./morse -e < message > < duration of a ti: default is 0.1 >

> To encode a message from a file: ./morse -ef < text file: default is input.txt > < ti: 0.1 >

Decode any audio .wav file that contains Morse into a Message written in Latin or any other alphabet

> To decode a .wav file: ./morse -d < .wav file: default is output.wav > < duration of a ti: default is 0.1 >

Compilation:

> To compile: make

## DELMAS Louis - Mines ParisTech - 24/01/21