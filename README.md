compiler : g++ main.cpp
executer : ./a.out ficher.txt
VM : https://perso.limsi.fr/lavergne/

---------------------------------------
g++ -std=c++20 main.cpp && ./a.out testWhile.txt | ./msm

si inclure bibliothèque standard, mettre le fichier en argv[1]: 
    g++ -std=c++20 main.cpp && ./a.out bibliothequeStandard.txt testPointeurTab.txt | ./msm 

si entrée/sortie (print, read) dans programme :
    ATTENTION : recv et send doivent être appelés comme une variable "recv", "send expression"
    mettre assembleur générer dans prog.s et executer :
    ./msm prog.s

---------------------------------------

Pour retirer les optimisations, il suffit de commenter la ligne 611 dans le fichier main.cpp

---------------------------------------

ATTENTION :
    Lors d'une erreur de compilation, le compilateur indique la ligne de l'erreur en considérant la ligne de déclaration de la dernière fonction en traitement comme étant la ligne 1. (ligne 1 = de la dernière fonction déclarer en traitement)