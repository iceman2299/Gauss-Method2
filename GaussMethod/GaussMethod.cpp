#include <iostream>
#include <clocale>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;


int col, row; //число строк и столбцов для ввода

//Блок используемых функций:
int checkreal(double**);

//Функция инициализации матрицы
double** matrix()
{
	int colzn = col + 1;
	double** a;
	a = new double* [colzn];
	for (int i = 0; i < colzn; i++)
	{
		a[i] = new double[row];
	}
	return a;
};

//Функция инициализации значений
double* xses()
{
	double* x;
	x = new double[row];
	return x;
}

//Функция ввода матрицы с клавиатуры
void inputK(double** a)
{
	for (int j = 0; j < row; j++)
	{
		for (int i = 0; i < col; i++)
		{
			cout << "Введите \x1b[32m" << j + 1 << "-e \x1b[0mчисло \x1b[32m" << i + 1 << "-го \x1b[0mстолбца\n";
			cin >> a[i][j];
		}
		cout << "Введите значение \x1b[36m" << j + 1 << "-й \x1b[0mстроки\n";
		cin >> a[col][j];
	}
}


//Функция вывода матрицы на экран
void moutputS(double** a)
{
	for (int j = 0; j < row; j++)
	{
		for (int i = 0; i < col; i++)
		{
			cout << setw(15) << a[i][j] << " ";
		}
		cout << setw(15) << "|" << a[col][j];
		cout << "\n";
	}
}

//Функция вывода значений на экран
void xoutputS(double* x)
{
	for (int j = 0; j < row; j++)
	{
		cout << "x" << j + 1 << " = " << x[j];
		cout << "\n";
	}
}

//Функция обмена строк матрицы
int strchange(double** a, int nulstr, int nowcol)
{
	double* buf;
	int colzn = col + 1;
	buf = new double[colzn];
	if (nulstr == row - 1)
	{
		int kod = checkreal(a);
		return kod;
	}
	for (int j = nulstr + 1; j < row; j++)
	{
		if (a[nowcol][j] != 0)
		{
			for (int i = 0; i < colzn; i++)
			{
				buf[i] = a[i][nulstr];
				a[i][nulstr] = a[i][j];
				a[i][j] = buf[i];
				//cout << i << " й член " << j << " Строки " << "Сменен с " << a[i][j] << " На " << a[i][nulstr] << endl;//(отладочная опция)
			}
			return 0;
		}
	}
	return 5;
}

//Функция прямого хода метода гаусса
int strway(double** a, double** b)
{
	double koef=0;
	int k = min(col, row);
	for (int j = 0; j < k; j++)
	{
		if (a[j][j] == 0)
		{
			if (j < row)
			{
				int kod = strchange(a, j, j);
				switch (kod)
				{
				case 5:
					return 5;
				case 2:
					return 2;
				case 3:
					return 3;
				}
				
			}
		}
		if (a[j][j] != 0)
		{
			koef = a[j][j];//Коэффициент деления строки
			for (int i = 0; i < col + 1; i++)
			{
				{
					
					a[i][j] = (a[i][j] / koef) + 0.0;
				}
			}
			for (int l = j + 1; l < row; l++)
			{
				double koef2 = a[j][l];//Коэффициент вычитания строки из нижних для неё
				for (int m = 0; m < col + 1; m++)
				{
					a[m][l] = (a[m][l] - (a[m][j] * koef2));
				}
			}
		}
		cout << j + 1 << "-й шаг:\n";
		moutputS(a);
	}
	return 0;
}

//Функция обратного хода метода гаусса
void bckway(double* x, double** a)
{
	x[row - 1] = a[col][row - 1];
	for (int j = row-2; j > -1; j--)
	{
		for (int i = col-1; i > j; i--)
		{
			a[col][j] = a[col][j] - a[i][j] * x[i];
		}
		x[j] = a[col][j];	
	}
}

//Функция копирования матриц
double** matrixcpy(double** a)
{
	double** tempmatr = matrix();
	for (int j = 0; j < row; j++)
	{
		for (int i = 0; i <= col; i++)
		{
			tempmatr[i][j] = a[i][j];
		}
	}
	return tempmatr;
}

//Функция проверки на несовместность и параметричность
int checkreal(double** a)
{
		for (int j = 0; j < row; j++)
		{
			double checkingsum = 0;
			for (int i = 0; i < col; i++)
			{
				checkingsum = fabs(checkingsum) + fabs(a[i][j]);
			}
			if (checkingsum == 0 && a[col][j] != 0)
			{
				return 3;
			}
		}
		for (int i = 0; i < col; i++)
		{
			double checkingsum = 0;
			for (int j = i; j < row; j++)
			{
				checkingsum = fabs(checkingsum) + fabs(a[i][j]);
			}
			if (checkingsum > 1)
			{
				return 2;
			}
		}

	return 0;
}

int checkanswer(double* x, double** b)
{
	for (int j = 0; j < row; j++)
	{
		double bufsum = 0;
		for (int i = 0; i < col; i++)
		{
			bufsum = bufsum + b[i][j] * x[i];
		}
		if (bufsum != b[col][j])
		{
			return 1;
		}
	}
	return 0;
}
//Конец блока функций



int main()
{
	setlocale(LC_ALL, "RUS");
	cout << "\x1b[1;36mПрограмма вычисления неизвестных в системе линейных алгебраических уравнений методом гаусса.\x1b[0m\n";
	cout << "\x1b[1;32mВведите количество столбцов матрицы коэффициентов\x1b[0m\n";
	cin >> col;
	cout << "\x1b[1;32mВведите количество строк матрицы коэффициентов\x1b[0m\n";
	cin >> row;
	double** a = matrix();
	inputK(a);
	double** b = matrixcpy(a);//Копия оригинальной матрицы, потом пригодится для сравнения значений
	system("cls");
	cout << "Исходная матрица:\n";
	moutputS(a); //Рисуем оригинальную матрицу на экране
	int kod = strway(a,b); //Прямой ход с кодами ошибок
	switch (kod)
	{
	case 2:
	{
		cerr << "\x1b[1;36mНеизвестные данной системы задаются параметрически, решений великое множество.\n\x1b[1;0m";
		return 0;
	}
	case 3:
	{
		cerr << "\x1b[1;36mСистема несовместна.\n\x1b[1;0m";
		return 0;
	}
	case 5:
	{
		system("cls");
		cerr << "\x1b[1;31mОшибка. Во время преобразований нашлась несменяемая строка с нулем по главной диагонали.\n Совет: поменяйте первую и последнюю строки в исходной матрице вручную и попробуйте еще раз.\n\x1b[1;0m";
		return 5;
	}
	}
	cout << "\x1b[1;32mИтоговая матрица после преобразований:\n\x1b[1;0m";
	moutputS(a); //Рисуем итоговую матрицу на экране
	double* x = xses(); //Память под найденные значения
	kod = checkreal(a);//Проверка возможности существования системы с кодами
	switch (kod)
	{
	case 2:
	{
		cerr << "\x1b[1;36mНеизвестные данной системы задаются параметрически, решений великое множество.\n\x1b[1;0m";
		return 0;
	}
	case 3:
	{
		cerr << "\x1b[1;36mСистема несовместна.\n\x1b[1;0m";
		return 0;
	}
	}
	bckway(x, a);
	free(a);
	kod = checkanswer(x, b);
	switch (kod)
	{
	case 1:
	{
		cerr << "\x1b[1;36mВнимание, большая погрешность при сверке ответов! Ответы могут быть не точны.\n\x1b[1;0m";
	}
	case 0:
	{
		cout << "\x1b[1;32mПроверка пройдена успешно, ответы сходятся.\n\x1b[1;0m";
	}
	}
	xoutputS(x);
	free(b);
	free(x);
	cout << "\x1b[1;36mНажмите любую клавишу чтобы выйти...\x1b[1;0m";
	cin.get();
	return 0;
}//Конец программы
