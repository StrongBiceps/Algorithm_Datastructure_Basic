#include <iostream>
#include <conio.h>
#include <Windows.h>
#define Row 5
#define Column 5
#define Down 50
#define Left 52
#define Right 54
#define Up 56
using namespace std;

void init_arr(int(&_iArr)[Row][Column]);
void print_arr(const int(&_iArr)[Row][Column]);
void Keyboard_input(int& _iInput);
void move_arr(int(&_iArr)[Row][Column], const int& _iInput, int& _iZeroIndex_1, int& _iZeroIndex_2);
void System_Helper();

int main()
{
	int iArr[Row][Column] = {};
	int iInput = 0;
	int iZeroIndex_1 = 0;
	int iZeroIndex_2 = 0;

	init_arr(iArr);

	while (true)
	{
		cout << endl;
		cout << "방향키를 입력하시오" << endl;
		print_arr(iArr);
		Keyboard_input(iInput);

		move_arr(iArr, iInput, iZeroIndex_1, iZeroIndex_2);
		System_Helper();
	}

	return 0;
}

void init_arr(int(&_iArr)[Row][Column])
{
	for (register int i = 0; i < Row; ++i)
	{
		for (register int j = 0; j < Column; ++j)
		{
			_iArr[i][j] = (5 * i) + j;
		}
	}
}

void print_arr(const int(&_iArr)[Row][Column])
{
	for (register int i = 0; i < Row; ++i)
	{
		for (register int j = 0; j < Column; ++j)
		{
			cout << _iArr[i][j] << "\t";
		}
		cout << endl;
	}
}

void Keyboard_input(int& _iInput)
{


	_iInput = _getch();

	//_iInput = getchar();
}

void move_arr(int(&_iArr)[Row][Column], const int& _iInput, int& _iZeroIndex_1, int& _iZeroIndex_2)
{
	int iTemp = 0;

	switch (_iInput)
	{
	case Down:
	{
		if (_iZeroIndex_1 + 1 > Row - 1)
		{
			cout << "움직일 수 없습니다." << endl;
			break;
		}
		else
		{
			iTemp = _iArr[_iZeroIndex_1 + 1][_iZeroIndex_2];
			_iArr[_iZeroIndex_1 + 1][_iZeroIndex_2] = _iArr[_iZeroIndex_1][_iZeroIndex_2];
			_iArr[_iZeroIndex_1][_iZeroIndex_2] = iTemp;

			_iZeroIndex_1 += 1;

			break;
		}
	}
	case Up:
		if (_iZeroIndex_1 - 1 < 0)
		{
			cout << "움직일 수 없습니다." << endl;
			break;
		}
		else
		{
			iTemp = _iArr[_iZeroIndex_1 - 1][_iZeroIndex_2];
			_iArr[_iZeroIndex_1 - 1][_iZeroIndex_2] = _iArr[_iZeroIndex_1][_iZeroIndex_2];
			_iArr[_iZeroIndex_1][_iZeroIndex_2] = iTemp;

			_iZeroIndex_1 -= 1;
			break;
		}
	case Right:
	{
		if (_iZeroIndex_2 + 1 > Column - 1)
		{
			cout << "움직일 수 없습니다." << endl;
			break;
		}
		else
		{
			iTemp = _iArr[_iZeroIndex_1][_iZeroIndex_2 + 1];
			_iArr[_iZeroIndex_1][_iZeroIndex_2 + 1] = _iArr[_iZeroIndex_1][_iZeroIndex_2];
			_iArr[_iZeroIndex_1][_iZeroIndex_2] = iTemp;

			_iZeroIndex_2 += 1;
			break;
		}
	}
	case Left:
	{
		if (_iZeroIndex_2 - 1 < 0)
		{
			cout << "움직일 수 없습니다." << endl;
			break;
		}
		else
		{
			iTemp = _iArr[_iZeroIndex_1][_iZeroIndex_2 - 1];
			_iArr[_iZeroIndex_1][_iZeroIndex_2 - 1] = _iArr[_iZeroIndex_1][_iZeroIndex_2];
			_iArr[_iZeroIndex_1][_iZeroIndex_2] = iTemp;

			_iZeroIndex_2 -= 1;
			break;
		}
	}
	}
}

void System_Helper()
{
	//Sleep(500);
	system("cls");
}