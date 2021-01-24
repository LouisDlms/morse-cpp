# Ecriture et lecture de fichiers audio .WAV

## Ecriture

Nous avons choisi pour des questions de taille de fichier d'encoder nos fichiers en Mono, avec un Sampling Rate classique de 44100 Hz et 2 octets par sample. On pourrait très bien choisir d'autres paramètres d'encodage.

A l'aide de la classe Wav et de la méthode write_word, nous écrivons ainsi l'en-tête du fichier .WAV puis les données souhaitées.

## Lecture

Il faut tout d'abord récupérer les paramètres d'écriture du fichier .WAV fourni en entrée du programme de décodage. Pour cela, on lit l'en-tête du fichier et stockons les différents paramètres dans notre structure WAV_HDR.

Il suffit ensuite de récupérer les données stockées, en s'adaptant en fonction des paramètres données dans l'en-tête. Par exemple, si on fournit en entrée un fichier Stéréo, il faut pouvoir s'adapter.