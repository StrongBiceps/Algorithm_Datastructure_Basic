#include <iostream>
#include <cstring>
#define Arr_Row 3
#define Arr_Column 3
using namespace std;

void print_arr(const int(&_iArr)[Arr_Row][Arr_Column]);
void Init_arr(int(&_iArr)[Arr_Row][Arr_Column]);
void copy_arr(int(&_iArr)[Arr_Row][Arr_Column], const int(&_iTemp)[Arr_Row][Arr_Column]);

void convert_90_Deg(int(&_iArr)[Arr_Row][Arr_Column])
{
	int iTemp[Arr_Row][Arr_Column] = { 0 };

	for (register int i = 0; i < Arr_Row; ++i)
	{
		for (register int j = 0; j < Arr_Column; ++j)
		{
			/*
   			//1행을 3열로 switch하는 규칙으로 짠 코드
      			//1줄로 모든 규칙을 설명할 수 없다.
			if (i == 2)
			{
				iTemp[i-j][2-i] = _iArr[i][i-j];
			}
			else
			{
				iTemp[j][2-i] = _iArr[i][j];
			}*/

			//i == 2 ? iTemp[i - j][2 - i] = _iArr[i][i - j] : iTemp[j][2 - i] = _iArr[i][j];
				
			//1열을 1행으로 switch하는 규칙으로 짠 코드
			//1줄로 모든 규칙을 설명할 수 있다.
			iTemp[i][j] = _iArr[2 - j][i];
		}
	}
	copy_arr(_iArr, iTemp);
	print_arr(iTemp);
}

void print_arr(const int(&_iArr)[Arr_Row][Arr_Column])
{

	for (register int i = 0; i < Arr_Row; ++i)
	{
		for (register int j = 0; j < Arr_Column; ++j)
		{
			cout << _iArr[i][j] << "\t";
		}
		cout << endl;
	}
}

void Init_arr(int(&_iArr)[Arr_Row][Arr_Column])
{
	for (register int i = 0; i < Arr_Row; ++i)
	{
		for (register int j = 1; j <= Arr_Column; ++j)
		{
			_iArr[i][j - 1] = (3 * i) + j;
		}
	}
}

void copy_arr(int(&_iArr)[Arr_Row][Arr_Column], const int(&_iTemp)[Arr_Row][Arr_Column])
{
	for (register int i = 0; i < Arr_Row; ++i)
	{
		for (register int j = 0; j < Arr_Column; ++j)
		{
			_iArr[i][j] = _iTemp[i][j];
		}
	}
}

int main()
{
	int iArr[3][3] = {};

	Init_arr(iArr);

	for (register int i = 0; i < 4; ++i)
	{
		convert_90_Deg(iArr);
		cout << endl;
	}
	return 0;
}
