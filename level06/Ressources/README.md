## level06
- La lecture du [code source désassemblé](/level06/source.c) fait apparaître que l'on retrouve le même type de faille que pour le [niveau 03](/level03/Ressources/README.md) : il faudra parvenir à inverser la logique de vérification du mot de passe, pour passer la chaîne attendue au binaire. En pratique, cela veut dire faire le nécessaire pour que la fonction `auth` renvoie zéro (et pouvoir ainsi lancer un *shell* en tant que `level06`). L'utilisation de [`ptrace`](https://linux.die.net/man/2/ptrace) va empêcher l'utilisation de `gdb` pour contourner ces vérifications.
- La fonction `auth` reçoit deux arguments (`login` et `serial`) sur lesquels elle procède aux vérifications suivantes :
    - Sur la chaîne de caractères `login` :
        - La chaîne doit faire entre 6 et 32 caractères.
        - Tous les caractères doivent être imprimables (c'est-à-dire avoir une valeur ASCII comprise entre 32 et 127)
    - Sur l'entier positif `serial` :
        - Il doit être égal à la valeur de `bin`, qui est obtenue de la façon suivante : la variable est initialisée avec la valeur `(login[3] ^ 0x1337U) + 0x5eeded` ; puis pour chaque caractère de `login`, on y ajoute `(login[i] ^ bin) % 1337`.
- Pour se faciliter la tâche, on va simplement recréer [un petit programme](/level06/Ressources/solver.c) qui va refaire ces mêmes opérations et nous donner la valeur de `serial`. Ainsi, en utilisant `level06` comme valeur pour `login`, on sait que `serial` devra être `6233721`.
- Cela permet bien de lancer un *shell* en tant que `level07` ; `cat /home/users/level07/.pass` pour récupérer le *flag*.