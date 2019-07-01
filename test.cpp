// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream> // Inclusion de la bibliothèque d’E/S
#include <mpi.h>  // the famous one
#include <stdio.h>  // lib standard
#include<vector> // le type de donnees vector
#include "utils.h" // mes propres fonctions
#include <cstdlib> //inclus la fonction rand qui permet de generer un entier de manier aleatoire
#include <typeinfo>
using namespace std;


int main(int argc, char** argv) {
	
	// Initialize the MPI environment
	MPI_Init(NULL, NULL);

	// Get the number of processes
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// Get the rank of the process
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	// Get the name of the processor
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);
	int cc=0;//taille a envoyer
	int ddd;
	vector <double> a;//tableau des variables globale
	vector<double> b;
	vector <double> c;
	vector <double> f;
	if (world_rank==0) {
		//creation du tableau
		int N,P; 
		P = world_size;
		cout <<"entrer la dimension de la matrice suivi du nombre de processeur utilise";
		cin >> N;
		const int ff = N;
		//cout << "entrer les valeurs de la sous diagonale";
		a.push_back(0);
		c.push_back(0);
		for (int i = 0; i < N-1; i = i + 1) {
			double d;
			d = fRand(1, 6);//genere des entiers entre 1 et 5 pour tester et eviter une executuion trop longue //permet egalement d'eviter les division par zero
			//cin >> d;
			a.push_back(d);
			double dd;
			dd = fRand(1, 6);
			//cin >> d;
			c.push_back(dd);
		};

		for (int i = 0; i < N ; i = i + 1) {
			double d;
			d = fRand(1, 6);
			//cin >> d;
			b.push_back(d);
			double s;
			s = fRand(1, 6);
			//cin >> d;
			f.push_back(s);
		};
		cc = a.size();
		for (int j = 1; j < P; j = j++) {
			
		cout << "envoi de la taille du tableau " << 1<<endl;
		 MPI_Send(&cc, 1, MPI_INT, j, 2, MPI_COMM_WORLD);

		}
		cout << "envoie de la taille realise";
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Bcast(&a[0], cc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Bcast(&b[0], cc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Bcast(&c[0], cc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Bcast(&f[0], cc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		cout << "diffusion du tableau a" << endl;
		
		afficher(c);
	}
	else {
		MPI_Recv(&cc, 3, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		cout << "reception de la taille du tableau " <<cc<< endl;
		a.resize(cc);
		b.resize(cc);
		c.resize(cc);
		f.resize(cc);
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Bcast(&a[0], cc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Bcast(&b[0], cc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Bcast(&c[0], cc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Bcast(&f[0], cc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		//cout << "reception du tableau a"<< a[0]<<endl;
		//afficher(a);
		//ddd= a[0];.
		
		/*if (world_rank ==1 ) {
			cout << "hh"<< "premier element";
		}*/
	
	}
	//cout << "dfff"<<world_rank << a[0]<< endl;

	vector<double> aint;
	vector<double> bint;
	vector<double> cint;
	vector<double> fint;
	int NN = cc / world_size;
	cout << "frat" << NN;
	//dicvision de chaque composant pour avoir le bon composant
	if (world_rank==world_size-1) {// le dernier process recupere l'ensemble des valeurs restantes

		for (int ii = NN * (world_rank ); ii < a.size(); ii++) {
			aint.push_back(a[ii]);
			bint.push_back(b[ii]);
			cint.push_back(c[ii]);
			fint.push_back(f[ii]);
		}
		/*const int gg = a.size() - 1;
		cint.erase(gg);*/
	}
	else if(world_rank == 0) {
		for (int ii = NN * (world_rank ); ii < NN * (world_rank +1);ii++) {
			aint.push_back(a[ii]);
			bint.push_back(b[ii]);
			cint.push_back(c[ii]);
			fint.push_back(f[ii]);
		}
		/*cint.erase(0);*/
		
	}
	else {
		for (int ii = NN * (world_rank); ii < NN * (world_rank + 1); ii++) {
			aint.push_back(a[ii]);
			bint.push_back(b[ii]);
			cint.push_back(c[ii]);
			fint.push_back(f[ii]);
		}

	}
	afficher(aint);
	MPI_Barrier(MPI_COMM_WORLD);
	firststepmodif(aint, bint, cint, fint);

	MPI_Barrier(MPI_COMM_WORLD);
	secondstepmodif(aint, bint, cint, fint);//deuxieme transformation
	int longf = aint.size();
	//afficher(cint);
	vector<double> interface;//creation du vecteur d'interface considere commme le dernier element de chaque sous domaine
	interface.push_back(aint[longf-1]);
	interface.push_back(bint[longf - 1]);
	interface.push_back(cint[longf - 1]);
	interface.push_back(fint[longf - 1]);
	//interface.resize(3);
	//afficher(interface);


	vector<double> interfacerec;
	interfacerec.resize(4);//interface du sous domaine suivant
	MPI_Barrier(MPI_COMM_WORLD);
	//afficher(interface);

	cout << "debut de lenvoie des interfaces "<<world_rank;

	if (world_rank < world_size - 1) {
		MPI_Recv(&interfacerec[0], 4, MPI_DOUBLE, world_rank + 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


	}

	if (world_rank > 0) {//la derniere composante ne recoit rien 
		MPI_Send(&interface[0], 4, MPI_DOUBLE, world_rank - 1, 2, MPI_COMM_WORLD);

	}

	MPI_Barrier(MPI_COMM_WORLD);

	//afficher(interfacerec);
	//jonction des interfaces le resultat est stocke dans la variable interface qui contient  les valeurs interface de la composante actuelle
	//probleme de division par zero
	if (world_rank != world_size - 1) {//le dernier composant de recoit pas de composant donc les valeurs d'interface ne sont pas modifiees
		if (interfacerec[1] != 0) {//si cette valeur est null aucune jonction n'est possible car declenchant une division par zero

		//on peut affecter les valeurs directement sans utilisation de variable pivot parce qu'il n 'a 
		//pas  des les expression de reutilisation entre variable modifee

			interface[1] = interface[1] - interfacerec[0] * interface[2] / interfacerec[1];
			interface[2] = -interfacerec[2] * interface[2] / interfacerec[1];
			interface[3] = interface[3] - interfacerec[3] * interface[2] / interfacerec[1];
			cout << "modification des interfaces " << interface[2] << endl;
			bint[longf - 1] = interface[1];
			cint[longf - 1] = interface[2];
			fint[longf - 1] = interface[3];
			//afficher(cint);
		}
	}

	
	if (world_rank == world_size-1) {
		afficher(interface);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	if (world_rank >0) {
		MPI_Gather(&interface[0], 4, MPI_DOUBLE, NULL, 4, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	}
	else {
		vector<double>recinter;
		recinter.resize(4 *(world_size));
		MPI_Gather(&interface[0], 4, MPI_DOUBLE, &recinter[0], 4, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		cout << "reception du tas";
		afficher(recinter);
		vector<double> aa;//variable utilisees pour la resolution de l'equation tridiagonal des interfaces
		vector<double> bb;
	    vector<double> cc;
		vector<double> ff;

		for (int ind = 0; ind < (world_size * 4); ind=ind+4) {
			aa.push_back(recinter[ind]);
			bb.push_back(recinter[ind+1]);
			cc.push_back(recinter[ind+2]);
			ff.push_back(recinter[ind+3]);


		}
		afficher(aa);
		aa.erase(aa.begin(), aa.begin() + 1);
		cc.pop_back();

		x = tridiagonal_solver(aa, bb, cc, ff);

	}

	

	
	/*;
	cint.erase(cint.begin(), cint.begin() + 1);
	vector<double> x;
	x.resize(bint.size());

	cout << "resolution de x";

	afficher(x);*/

	
	
	//cout << "jonction des interfaces" << endl;
	

	
	// Finalize the MPI environment.
	MPI_Finalize();
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
