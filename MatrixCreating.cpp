#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <complex>
#include <clocale>
#include <math.h>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <string.h>
using namespace std;

int main()
{
	int pn = 3;
	//создаем матрицу смежности
	double **matrixpr = new double*[pn];
	for (int i = 0; i < pn; i++)
		matrixpr[i] = new double[3];
	for (int i = 0; i < pn; i++)
		for (int j = 0; j < 3; j++)
			matrixpr[i][j] = 0;
	//массив координат точек
	double **coords = new double*[pn];
	for (int i = 0; i < pn; i++)
		coords[i] = new double[3];
	//вводим координаты точек
	ifstream points;
	points.open("C:\\randompictures\\startpoints.txt");
	for (int i = 0; i < pn; i++) {
		for (int j = 0; j < 3; j++) {
			points >> coords[i][j];
		}
	}
	points.close();
	//массив начал отрезков
	int on = 2;
	double **beginings = new double*[on];
	for (int i = 0; i < on; i++)
		beginings[i] = new double[3];
	//вводим начала
	ifstream starts;
	starts.open("C:\\randompictures\\beginings.txt");
	for (int i = 0; i < on; i++) {
		for (int j = 0; j < 3; j++) {
			starts >> beginings[i][j];
		}
	}
	starts.close();
	//массив концов отрезков
	double **endings = new double*[on];
	for (int i = 0; i < on; i++)
		endings[i] = new double[3];
	//вводим начала
	ifstream finishs;
	finishs.open("C:\\randompictures\\endings.txt");
	for (int i = 0; i < on; i++) {
		for (int j = 0; j < 3; j++) {
			finishs >> endings[i][j];
		}
	}
	finishs.close();
	//—читаем матрицу

	for (int i = 0; i < pn; i++) {
		for (int j = 0; j < 3; j++) {
			cout << coords[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < on; i++) {
		for (int j = 0; j < 3; j++) {
			cout << beginings[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < on; i++) {
		for (int j = 0; j < 3; j++) {
			cout << endings[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < pn; i++)
		for (int j = 0; j < pn; j++)
			for (int k = 0; k < on; k++)
			{
				if (coords[i][0] == beginings[k][0] && coords[i][1] == beginings[k][1] && coords[i][2] == beginings[k][2] && coords[j][0] == endings[k][0] && coords[j][1] == endings[j][1] && coords[j][2] == endings[k][2]) {
					matrixpr[i][j] = 1;
				}
				if (coords[i][0] == endings[k][0] && endings[i][1] == endings[k][1] && coords[i][2] == endings[k][2] && coords[j][0] == beginings[k][0] && coords[j][1] == beginings[j][1] && coords[j][2] == beginings[k][2]) {
					matrixpr[i][j] = 1;
				}
			}
	for (int i = 0; i < pn; i++) {
		for (int j = 0; j < pn; j++) {
			cout << matrixpr[i][j] << " ";
		}
		cout << endl;
	}



	system("pause");
	return 0;




}