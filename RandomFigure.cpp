//�����. ��������� ������ � ����� points.txt: x0 y0 z0 R
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
#define ZOOM 8
#ifndef SIZE
#define SIZE 800
#endif // SIZE
//============================================================================
//������� ������� bmp-�����
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
	//��������� bmp-�����
	ofstream bmf;
	//������� �������� bmp-��������
	char canvas[SIZE][SIZE];
	void print(char s[100]) {
		rawData[19] = SIZE / 256;
		rawData[18] = SIZE % 256;
		rawData[23] = SIZE / 256;
		rawData[22] = SIZE % 256;
		//���������� bmp-����� (������������ �������� ����� ������)
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
//����� �������� bmp-�����
//============================================================================
bmp a;
double canvas[SIZE][SIZE];
int main() {
	srand(time(0));
	//���������� �� txy-����� ���������� � �����: ���������� ������ � ������
	//======================================================================
	ifstream pts;
	pts.open("C:\\randompictures\\startpoints.txt");
	if (!pts)
	{
		cout << "No\n\n";
	}
	else
	{
		cout << "Yes!\n\n";
	}
	int pn = 170; // ����� ����� �����
	double **startpoints = new double*[pn];
	for (int i = 0; i < pn; i++)
		startpoints[i] = new double[3];
	for (int i = 0; i < pn; i++)
		for (int j = 0; j < 3; j++)
			pts >> startpoints[i][j];
	
	//g - ����������� ����������� ����������; q - ���������� ����������; edge - ����� �����;
	int q, g = 15;
	double edge = 100;
	q = (int)edge;
	cout << edge << " " << q << endl;
	//������ ��������� ���������� � ����
	ofstream coord;
	coord.open("C:\\coordinate.txt");
	//������� �������������
	for (int i = 0; i < pn; i++) {
		for (int j = 0; j < 3; j++)
			coord << startpoints[i][j] << " ";
		
	}
	coord.close();
	//======================================================================
	double **matrixpr = new double*[pn];
	for (int i = 0; i < pn; i++)
		matrixpr[i] = new double[pn];
	for (int i = 0; i < pn; i++) {
		for (int j = 0; j < pn; j++) {
			matrixpr[i][j] = 0;
		}
	}
	ifstream arr12;
	arr12.open("C:\\randompictures\\matrixpr.txt");
	for (int i = 0; i < pn; i++) {
		for (int j = 0; j < pn; j++) {
			arr12 >> matrixpr[i][j];
		}
	}
	arr12.close();
	//======================================================================
	//������� �����
	//======================================================================
	double *x = new double[pn];
	double *y = new double[pn];
	double *z = new double[pn];
	for (int i = 0; i < pn; i++) {
		x[i] = 0;
		y[i] = 0;
		z[i] = 0;
	}
	
	for (int i = 0; i < pn; i++) {
		x[i] = startpoints[i][0];
		y[i] = startpoints[i][1];
		z[i] = startpoints[i][2];
	}
	//======================================================================
	//������ ������������� �� ������� ��������� ������� � ����������� ���� � ������ ����� ����
	//======================================================================
	//�������������� �������
	//======================================================================
	//�������������� ����������� ����
	double e = 100, w;
	w = 64 * PI / 623;
	//������� �����
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
			//���� �����
			for (int k = 0; k < pn; k++) {
				double r = sqrt((i - x[k])*(i - x[k])*ZOOM*ZOOM + (j - y[k])*(j - y[k])*ZOOM*ZOOM + z[k] * z[k] * ZOOM*ZOOM);
				C = cos(w * r) * e / r;
				A += C;
				B += C;
			}
			//����� �����
			for (int p = 0; p < pn; p++) {
				for (int o = 0; o < pn; o++) {
						if (matrixpr[p][o] == 1) {
							q = (int)(0.2*sqrt((x[p] - x[o])*(x[p] - x[o]) + (y[p] - y[o])*(y[p] - y[o]) + (z[p] - z[o])*(z[p] - z[o])));
							for (int l = 1; l <= q; l++) {
								double newX, newY, newZ;
								newX = (x[p] - x[o])*l / (q + 1) + x[o];
								newY = (y[p] - y[o])*l / (q + 1) + y[o];
								newZ = (z[p] - z[o])*l / (q + 1) + z[o];
								double r = sqrt((i - newX)*(i - newX)*ZOOM*ZOOM + (j - newY)*(j - newY)*ZOOM*ZOOM + newZ * newZ * ZOOM*ZOOM);
								C = cos(w * r) * e / r;
								A += C;
								B += C;
							}
						}
				}
			}


			//������ ������������� � ������ ����� ����
			canvas[i][j] = abs(2 * A * A + B * B);
			canvas[i][j] = canvas[i][j] * canvas[i][j];
			mn = min(mn, canvas[i][j]); mx = max(mx, canvas[i][j]);
		}
	}
	//======================================================================
	//������������� ������� ����� (� ����������� �� �������������)
	//======================================================================
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++) {
			a.canvas[i][j] = 255 * (((canvas[i][j] - mn) / (mx - mn)));
		}
	//======================================================================
	//����� ������ � bmp-����
	//======================================================================
	const char *str1 = "image.bmp";
	char *str2 = const_cast<char*>(str1);
	a.print(str2);
	//======================================================================
	cout << "runtime = " << clock() / 1000.0 << " c" << endl;
	system("pause");
	return 0;
}