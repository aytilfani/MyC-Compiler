#!/bin/bash

#Gestion des erreurs sur nombre d'arguments et extension du fichier

if [ "$#" != 1 ]; then
    echo "ERREUR: Nombre d'arguments incorrect"
    echo "Essayez de recompiler \"./compil.sh <fichier>.myc\" "
    exit 1

elif [ ${1#*.} != "myc"  ]; then
    echo "ERREUR: Vous devez avoir un fichier de type .myc "
    echo "Essayez de recompiler \"./compil.sh <fichier>.myc\" "
    exit 2

elif [ ! -e "$1" ]; then
    echo "ERREUR: Fichier passé en paramètre n'existe pas"
    echo "Essayez avec un fichier existant"
    exit 3
fi

#Création de l'exécutable lang
make
#Compilation du fichier myc donné en paramètre
./lang < "$1"

if [ "$?" != 0  ]; then
    echo "Échec dans la compilation de votre fichier"
    make clean
    exit
fi

#Compilation du fichier du PCode
gcc -o out PCode/PCode.h out.c
#Suppresion des fichiers inutiles
rm -rf lex.yy.c *.o y.tab.h y.tab.c *~ y.output lang
