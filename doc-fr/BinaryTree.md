# Arbre binaire

Pour passer d'un alphabet quelconque au code MORSE, la structure d'arbre binaire est particulièrement adaptée puisque chaque noeud a alors deux descendant : le chemin de gauche correspond à un ti, le chemin de droite à un taa.

La classe Tree fournit les outils de parcours d'un arbre binaire représenté par un simple tableau. Il suffit alors d'appliquer ses méthodes pour récupérer le code Morse à partir d'un caractère donné, et inversement.

L'avantage d'une telle structure de classe (Latin étant une classe fille de Tree) est qu'elle permet facilement d'implémenter de nouveaux alphabets. Pour l'instant, seule la classe Latin est implémentée et permet de passer de l'alphabet latin au code Morse, mais on pourrait très facilement créer une nouvelle classe fille Japanese pour représenter l'alphabet japonais. On pourrait de même créer une classe LatinAdvanced pour y rajouter les caractères spéciaux et autres.

Une fois une instance de classe Latin créée, il suffit de la passer en argument des instances de classe Encode et Decode pour indiquer à nos objets qu'on souhaite encoder ou décoder en utilisant telle arbre de décodage.