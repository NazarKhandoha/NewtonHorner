#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

//Знаходимо занчення ф-ії в точці х
double return_rez(double x, double x_m[], double **matrix_x, int n)
{
	double rez = 0, rez_ = 0;
	for (int i = 0; i<n; i++)
	{
		rez_ = matrix_x[0][i];
		for (int j = 0; j<i; j++)
			rez_ = rez_*(x - x_m[j]);
		rez = rez + rez_;
	}
	return rez;
}

//Заповнюємо таблицю розділених різниць
void fill_matrix(int n, double f_xr[], double **matrix_e, double x[])
{
	for (int i = 0; i < n; i++)
		matrix_e[i][0] = f_xr[i];
	int y = n, rt = 0;
	for (int i = 1, r = 0; i < n; i++, r++)
	{
		for (int k = 0; k < y - 1; k++)
		{
			double ret = (matrix_e[k + 1][i - 1] - matrix_e[k][i - 1]) / (x[k + r + 1] - x[k]);
			matrix_e[k][i] = ret;
		}
		y--;
	}

}


void vuvid_polinom(double **matrix, double x[], int n)
{
	for (int i = 0; i<n; i++)
	{
		if (i == 4 || i == 5 || i == 6 || i == 7 || i == 8 || i == 9)
			cout << "\n";
		if (i == 0)
			cout << matrix[0][i] << "";
		else
		{
			cout << "+(" << matrix[0][i] << ")";
		}
		for (int j = 0; j<i; j++)
			cout << "(x-" << x[j] << ") ";
	}
}

void main()
{
	setlocale(0, "ukr");
	double x[10] = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 };
	double f_x[10] = { 2.00000, 1.95533, 1.82533, 1.62160, 1.36235, 1.07073, 0.77279, 0.49515, 0.26260, 0.09592 };
	// кількість інтервалів розбиття
	int n = 10;

	double **matrix;
	matrix = new double*[n];
	for (int i = 0; i < n; i++)
		matrix[i] = new double[n];
	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++)
			matrix[i][j] = 0;

	fill_matrix(n, f_x, matrix, x);

	cout << "Таблиця роздiлених рiзниць:" << endl;
	for (int i = 0; i<n; i++, cout << "\n")
		for (int j = 0; j<n; j++)
			cout << matrix[i][j] << setprecision(2) << "\t";
	cout << "Iнтерполяцiйний многочлен Ньютона:" << endl;
	cout << "L(x) = ";
	vuvid_polinom(matrix, x, n);
	int k;
	cout << "\n\n";
	cout << "Введiть кiлькiсть значень якi потрiбно порахувати :";
	cin >> k;
	double *a = new double[k];
	cout << "Введiть значення :\n";
	for (int i = 0; i<k; i++)
	{
		cout << "a[" << i + 1 << "]=";
		cin >> a[i];
	};
	cout << "Обчислити значення  многочлена в точках: ";
	for (int j = 0; j<k; j++)
	{
		cout << "\nx'="; printf("%4.3f", a[j]); cout << ": L[x']= "; printf("%4.8f   ", return_rez(a[j], x, matrix, n));
	}


}
