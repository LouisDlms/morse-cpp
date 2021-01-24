# Encodage Alphabet -> Audio Morse

On fournit en entrée du programme un message et la durée d'un ti.

On lit le message caractère par caractère. Avec la classe Encode, on convertit le caractère en "chemin", c'est-à-dire qu'on fournit un nombre binaire composé de 0 et de 1 : 0 correspond à un ti, 1 à un taa. 

Puis, en lisant ce mot binaire bit par bit, on écrit dans notre .WAV un ti ou un taa selon si le bit lu est un 0 ou un 1.

