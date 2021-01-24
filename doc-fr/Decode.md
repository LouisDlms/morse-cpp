# Décodage Morse (audio) -> Alphabet

On lit le fichier .WAV et on récupère les paramètres en en-tête. On peut ainsi décoder n'importe quelle fichier .WAV contenant du Morse, pourvu qu'on donne en entrée du programme de décodage la bonne durée d'un ti élémentaire (une amélioration serait de déterminer automatiquement cette durée en évaluant le plus petit interval temporel contenu dans le fichier).

On n'enregistre pas l'amplitude du son, on se contente de regarder si elle est nulle ou non, tous les ti secondes. On obtient ainsi une ligne de 0 et de 1. 1 "1" correspond à un ti, 3 "1" à un taa, 1 "0" à un espace entre caractère Morse, 3 "0" à un espace entre caractère de l'alphabet, 7 "0" à un espace.

Il suffit donc de compter ces 0 et ces 1. Lorsqu'on rencontre 3 ou 7 "0", on décode le code Morse précédant cet instant en utilisant les méthodes de décodage de la classe Tree. On récupère donc un caractère alphabétique.

Si un caractère n'est pas présent dans l'arbre, on l'ignore dans le message final. Si le code Morse n'est pas valide, on renvoie une erreur.