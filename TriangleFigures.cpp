//Сфера. Начальные данные в файле points.txt: x0 y0 z0 R
//============================================================================
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
#define PI 3.141592653589793238
#define ZOOM 5
#ifndef SIZE
#define SIZE 800
#endif // SIZE
//============================================================================
//Задание пустого bmp-файла
//============================================================================
unsigned char rawData[54] = {
0x42, 0x4D, 0x66, 0x75, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00,
0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x64, 0x00,
0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x75,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
class bmp {
public:
	//заголовок bmp-файла
	ofstream bmf;
	//задание размеров bmp-картинки
	char canvas[SIZE][SIZE];
	void print(char s[100]) {
		rawData[19] = SIZE / 256;
		rawData[18] = SIZE % 256;
		rawData[23] = SIZE / 256;
		rawData[22] = SIZE % 256;
		//заполнение bmp-файла (закрашивание картинки белым цветом)
		bmf.open(s, ios::binary);
		for (int i = 0; i < 54; i++) {
			char c = rawData[i];
			bmf.write(&c, 1);
		}
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				for (int k = 0; k < 3; k++)
					bmf.write(&canvas[j][i], 1);
		bmf.close();
		return;
	};
};
//============================================================================
//Конец создания bmp-файла
//============================================================================
bmp a;
double canvas[SIZE][SIZE];
int main() {
	srand(time(0));
	//считывание из txy-файла информации о сфере: координаты центра и радиус
	//======================================================================
	ifstream pts;
	int numT;
	double startpoint[2][5];
	pts.open("C:\\triangle.txt");
	if (!pts)
	{
		cout << "No\n\n";
	}
	else
	{
		cout << "Yes!\n\n";
	}
	
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
			pts >> startpoint[i][j];
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
			cout << startpoint[i][j];
		}
		cout << endl;
	}
	pts.close();
	pts.close();
	//======================================================================
	//Инициализация матрицы смежности 12x12
	//======================================================================
	double matrix3[6][6];
	int fs = 6;
	for (int i = 0; i < fs; i++) {
		for (int j = 0; j < fs; j++) {
			matrix3[i][j] = 0;
		}
	}
	ifstream arr3;
	arr3.open("C:\\matrix3.txt");
	for (int i = 0; i < fs; i++) {
		for (int j = 0; j < fs; j++) {
			arr3 >> matrix3[i][j];
		}
	}
	arr3.close();
	//======================================================================
	//Задание координат вершин треугольников
	//======================================================================
	//Задание угла тета для вершин икосаэдра, вписанного в сферу
	double tetha[6];
	tetha[0] = 0;
	tetha[1] = 4 * PI / 6;
	tetha[2] = 8 * PI / 6;
	tetha[3] = 0;
	tetha[4] = 4 * PI / 6;
	tetha[5] = 8 * PI / 6;
	double phi[2];
	//phi[0] = PI/2 - acos(startpoint[0][4]);
	phi[0] = PI;
	phi[1] = PI/2 - acos(startpoint[1][4]);
	cout << cos(phi[0]) << " " << phi[1] << endl;
	double x[6], y[6], z[6];
	for (int i = 0; i < 6; i++) {
		x[i] = 0;
		y[i] = 0;
		z[i] = 0;
	}
	//Расчет декартовых координат вершин икосаэдра через полярные координат
	double R[2];
	for (int j = 0; j < 2; j++) {
		R[j] = sqrt(3.0) / 3.0 * startpoint[j][3];
		if (j == 0) {
			for (int i = 0; i < 3; i++) {
				x[i] = R[j] * sin(tetha[i]);
				y[i] = R[j] * cos(tetha[i]);
				z[i] = startpoint[j][2];
				double xi, yi;
				xi = x[i];
				yi = y[i];
				x[i] = xi * cos(phi[j]) - yi * sin(phi[j]) + startpoint[j][0];
				y[i] = xi * sin(phi[j]) + yi * cos(phi[j]) + startpoint[j][1];
				cout << x[i] << " " << y[i] << " " << z[i] << " " << R[j] << endl;
			}
		}
		if (j == 1) {
			for (int i = 3; i < 6; i++) {
				x[i] = R[j] * sin(tetha[i]);
				y[i] = R[j] * cos(tetha[i]);
				z[i] = startpoint[j][2];
				double xi, yi;
				xi = x[i];
				yi = y[i];
				x[i] = xi * cos(phi[j]) - yi * sin(phi[j]) + startpoint[j][0];
				y[i] = xi * sin(phi[j]) + yi * cos(phi[j]) + startpoint[j][1];
				cout << x[i] << " " << y[i] << " " << z[i] << " " << R[j] << endl;
			}
		}
	}
	//Расчет количества источников на ребрах треугольников;
	//g - разрешающая способность модулятора; q - количество источников; edge - длина ребра;
	int q, g = 15;
	//double edge = 2 * R / (sqrt(2 * (5 + sqrt(5)))) / g;
	double edge = 226;
	q = (int)edge;
	cout << edge << " " << q << endl;
	//======================================================================
	//Расчет интенсивности от каждого источника плоской и сферических волн в каждой точке поля
	//======================================================================
	//Характеристики системы
	//======================================================================
	//Характеристики сферических волн
	double e = 100, w;
	w = 64 * PI / 623;
	//Опорная волна
	double e0, e00, w0, theta;
	theta = 0;
	e00 = 10;
	w0 = 64 * PI * theta / 623;
	//======================================================================
	double mn = +INFINITY;
	double mx = -INFINITY;
	for (int i = 0; i < SIZE; i++) {
		//cout << "i = " << i << endl;
		for (int j = 0; j < SIZE; j++) {
			//cout << "j = " << j << endl;
			double A = 0;
			double B = cos(w0 * j * ZOOM) * e00;
			double C = 0;
			//Расчет напряженностей от вершин треугольников
			for (int k = 0; k < 6; k++) {
				double r = ZOOM * sqrt((i - x[k])*(i - x[k]) + (j - y[k])*(j - y[k]) + z[k] * z[k]);
				C = cos(w * r) * e / r;
				A += C;
				B += C;
			}
			//Расчет напряженностей от ребер треугольников
			for (int p = 0; p < fs; p++) {
				for (int o = 0; o < fs; o++) {
					if (matrix3[p][o] == 1) {
						//edge = sqrt((x[p] - x[o]) * (x[p] - x[o]) + (y[p] - y[o]) * (y[p] - y[o]) + (z[p] - z[o]) * (z[p] - z[o])) / g;
						//q = (int)edge;
						q = (int)(0.2*sqrt((x[p] - x[o])*(x[p] - x[o]) + (y[p] - y[o])*(y[p] - y[o]) + (z[p] - z[o])*(z[p] - z[o])));
						for (int l = 1; l <= q; l++) {
							double newX, newY, newZ;
							newX = (x[p] - x[o])*l / (q + 1)+x[o];
							newY = (y[p] - y[o])*l / (q + 1)+y[o];
							newZ = (z[p] - z[o])*l / (q + 1)+z[o];
							double r = ZOOM * sqrt((i - newX)*(i - newX) + (j - newY)*(j - newY) + newZ * newZ);
							C = cos(w * r) * e / r;
							A += C;
							B += C;
						}
					}
				}
			}
			//Расчет интенсивности в каждой точке поля
			canvas[i][j] = abs(2 * A * A + B * B);
			canvas[i][j] = canvas[i][j] * canvas[i][j];
			mn = min(mn, canvas[i][j]); mx = max(mx, canvas[i][j]);
		}
	}
	//======================================================================
	//Распределение яркости света (в зависимости от интенсивности)
	//======================================================================
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++) {
			a.canvas[i][j] = 255 * (((canvas[i][j] - mn) / (mx - mn)));
		}
	
	//======================================================================
	//Вывод данных в bmp-файл
	//======================================================================
	const char *str1 = "image.bmp";
	char *str2 = const_cast<char*>(str1);
	a.print(str2);
	//======================================================================
	cout << "runtime = " << clock() / 1000.0 << " c" << endl;
	system("pause");
	return 0;
}