# MyC-Compiler

Le code cible a produire est du PCode. Il est ici codé en C.

On trouve ici son codage et quelques exemples, de difficulté progressive, de compilation "à la main" de code myc en PCode.

La fonction print_stack(), insérée ici ou là dans ce pcode, permet de tracer l'execution de ces exemples une fois compilés avec gcc.

Avancement:
1-un calcul d'expressions arithmétiques arbitraires.(fonctionnel)
2- des déclarations, affectations et réutilisations de variables entières.(fonctionnel)
3- des conditionelles (if, et if-else).(fonctionnel)
4- un itérateur (while).(fonctionnel)
5- un mecanisme de sous-blocs avec déclarations locales et les problèmes de visibilités et de masquages associés.(fonctionnel)
6- des fonctions à la C avec paramètres entiers et vérification de type associé (nb arguments).(fonctionnel)

Utilisation:
Pour la première utilisation faut commencer par exécuter: chmod +x compil.sh
Pour compiler un fichier: ./compil.sh <mon_fichier>.myc (l'extension doit être .myc)
Un fichier out.c et un exécutable out sont générés.
Le répertoire test contient des tests pour les différentes parties pour exécuter un test ./compil.sh /test/<fichier_test>.myc

