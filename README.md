# OverRide
- [ISO](https://projects.intra.42.fr/uploads/document/document/1831/OverRide.iso)
- [PDF](https://cdn.intra.42.fr/pdf/pdf/11429/en.subject.pdf)

Dernier projet de la branche sécurité du cursus de l'école 42.  
On démarre en se connectant sur la VM en SSH avec `level00:level00`. Il faut ensuite exploiter les failles du binaire `levelX` pour obtenir le mot de passe de l'utilisateur `levelX+1`

## Sommaire
- [level00](/level00/Ressources/README.md) : utilisation basique de `gdb`
- [level01](/level01/Ressources/README.md) : injection de [*shellcode*](https://en.wikipedia.org/wiki/Shellcode) et redirection de l'exécution
- [level02](/level02/Ressources/README.md) : [*format string*](https://en.wikipedia.org/wiki/Uncontrolled_format_string) pour lire la pile et récupérer le contenu du fichier `.pass`
- [level03](/level03/Ressources/README.md) : inversion de la logique de vérification du mot de passe
- [level04](/level04/Ressources/README.md) : écriture de mon propre *shellcode* pour lire le contenu du fichier `.pass`
- [level05](/level05/Ressources/README.md) : *format string* avec réécriture d'adresse en deux parties (octets de poids faible, puis octets de poids fort)
- [level06](/level06/Ressources/README.md) : inversion de la logique de vérification du mot de passe
- [level07](/level07/Ressources/README.md) : *shellcode* stocké directement dans le binaire (en contournant les limitations d'index)
- [level08](/level08/Ressources/README.md) : utilisation d'un lien symbolique pour forcer le binaire à obtenir le contenu du fichier `.pass`
- [level09](/level09/Ressources/README.md) : enchaînement de deux [*buffer overflow*](https://en.wikipedia.org/wiki/Buffer_overflow) pour rediriger l'exécution