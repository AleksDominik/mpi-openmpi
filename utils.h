#pragma once
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
void afficher(vector <double>&v) {
	cout << "debut de l'affichage" << endl;

	for (int i = 0; i < v.size(); i = i + 1) {
		cout << v[i] << " ";

	};
	cout << endl;
}
double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}


void print(vector<int> const& v)
{
	for (auto& i : v)
		std::cout << i << ' ';

	std::cout << '\n';
}

void firststepmodif(vector <double> &a, vector <double>& b, vector <double>& c, vector <double>& f ) {// premiere etape de la modification de la matrix
	vector<double> temp;
	temp.resize(4);
	for (int j = 1; j < a.size(); j++) {
		temp.clear();
		temp.resize(4);
		double zeroavoid;
		if (b[j - 1] == 0) {//pour eviter de diviser pa zero on divisera par 1 en considerant qu'il s'agit d'une operation matricielle
			//et que cette division ne se ferai  pas si le coeficient bJ est deja nul
			zeroavoid = 1;
		}
		else {
			zeroavoid = b[j - 1];
		}

		temp[0] = a[j - 1] * a[j]/ zeroavoid;
		temp[1] = b[j] - c[j - 1] * a[j] / zeroavoid;
		temp[2] = c[j];
		temp[3] = f[j] - f[j - 1] * a[j]/ zeroavoid;


		a[j] = temp[0];
		b[j] = temp[1];
		c[j] = temp[2];
		f[j] = temp[3];



	};


}
void secondstepmodif(vector <double>& a, vector <double>& b, vector <double>& c, vector <double>& f) {  // deuxieme etape de la modification de la matrix
	vector<int> temp;
	temp.resize(4);
	for (int j = a.size()-3; j >=0; j--) {
		temp.clear();
		temp.resize(4);
		double zeroavoid;
		if (b[j +1] == 0) {//pour eviter de diviser pa zero on divisera par 1 en considerant qu'il s'agit d'une operation matricielle
			//et que cette division ne se ferai  pas si le coeficient bJ est deja nul
			zeroavoid = 1;
		}
		else {
			zeroavoid = b[j + 1];
		}
		temp[0] = a[j] -a[j+1] * c[j] / zeroavoid;
		temp[1] = b[j];
		temp[2] = c[j]*c[j+1]/ zeroavoid;
		temp[3] = f[j] - f[j + 1] * c[j] / zeroavoid;


		a[j] = temp[0];
		b[j] = temp[1];
		c[j] = temp[2];
		f[j] = temp[3];

	}

	}

vector<double>tridiagonal_solver(vector<double>& a, vector<double>& b, vector<double>& c, vector<double>& f) {

	int n = f.size();
	vector<double> x(n);

	for (int i = 1; i < n; i++) {

		double m = a[i - 1] / b[i - 1];
		b[i] -= m * c[i - 1];
		f[i] -= m * f[i - 1];
	}
	// solve for last x value
	x[n - 1] = f[n - 1] / b[n - 1];

	// solve for remaining x values by back substitution
	for (int i = n - 2; i >= 0; i--)
		x[i] = (f[i] - c[i] * x[i + 1]) / b[i];

	return x;

}