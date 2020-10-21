## level00
- Le dossier utilisateur contient un binaire `level00` avec le [`suid`](https://en.wikipedia.org/wiki/Setuid) de l'utilisateur `level01`.
- L'examen du [code source désassemblé](/level00/source.c) nous montre que ce premier binaire est simple à exploiter :
    - Pour exécuter `system("/bin/sh")`, il suffit de remplir le [`scanf`](https://linux.die.net/man/3/scanf) avec la valeur 5276.
- Cela nous permet de lancer un shell en tant que `level01`. `cat /home/users/level01/.pass` nous permet d'obtenir le flag.