compiler : g++ main.cpp
executer : ./a.out ficher.txt
VM : https://perso.limsi.fr/lavergne/

---------------------------------------
g++ -std=c++20 main.cpp && ./a.out testWhile.txt | ./msm

si inclure bibliothèque standard, mettre le fichier en argv[1]: 
    g++ -std=c++20 main.cpp && ./a.out bibliothequeStandard.txt testPointeurTab.txt | ./msm 

si entrée/sortie dans programme :
   mettre assembleur générer dans prog.s et executer :
    ./msm prog.s