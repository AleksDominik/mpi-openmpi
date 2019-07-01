# mpi-openmpi
Resolution de systeme tridiagonal par programmation parallèle

# l'objection
Utilisation de la programation en parallèle pour l'implementation d'un algorithme de sous-structuration afin de résoudre une équation linéaire.<br>

Contient
  un fichier principale test.cpp 
  un fichier util.h contenant les fonction principale

# Fonctionnement
1. Creation des tableau a b c et f qui comportent respectivement la sous-diagonale, la diagonale principale et la diagonale supérieur
2. Diffusion des tableau dans chaque processus qui va ensuite enregistrer le composant qui lui correspond dans les variables aint bint cint et fint
3. Réalisation des deux premiere transformation et communication de l'interface du processus i au processus i-1 afin de realiser la jonction des interfaces
4. Rassemblement des interfaces dans le processus 0 qui va ensuite resoudre un système tridiagonale
5. Diffusion des composant resolu
6. Resolution du reste des composants.
