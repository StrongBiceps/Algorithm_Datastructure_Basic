#include <iostream>
#include <Windows.h>
#include <random>
#define Row 5
#define Column 5
using namespace std;

random_device rd;
mt19937_64 mt(rd());
uniform_int_distribution<int> dist(0, Row* Column);

int iRow_check[Row] = {};
int iColumn_check[Column] = {};
int iDiagonal_check[2] = { };
int iRow_check_PC[Row] = {};
int iColumn_check_PC[Column] = {};
int iDiagonal_check_PC[2] = { };
bool bWinner_Decision = false;

void init_arr(char(&_cArr)[Row][Column]);
void my_turn(char(&_cArr)[Row][Column], int& _iCount);
void PC_turn(char(&_cArr)[Row][Column], char(&_cArr_PC)[Row][Column], int& iCount);
void input_key(int& _iInput);
void print_arr(const char(&_cArr)[Row][Column], const char(&_cArr_PC)[Row][Column]);
void print_arr_sep(const char(&_cArr)[Row][Column]);
void System_Helper();
void copy_arr(char(&_cArr)[Row][Column], char(&_cArr_PC)[Row][Column]);

int main()
{
	char cArr[Row][Column] = {};
	int iCount = 0;

	init_arr(cArr);
	while (true)
	{
		cout << "\t    " << "===User===" << "\t\t\t\t\t      " << "===PC===" << endl;
		my_turn(cArr, iCount);
		if (bWinner_Decision == true)
		{
			break;
		}
		System_Helper();

		if (iCount == 25)
			break;
	}
	return 0;
}

void init_arr(char(&_cArr)[Row][Column])
{
	for (register int i = 0; i < Row; ++i)
	{
		for (register int j = 1; j <= Column; ++j)
		{
			_cArr[i][j - 1] = (5 * i) + j;
		}
	}
}

void my_turn(char(&_cArr)[Row][Column], int& _iCount)
{
	int iInput = 0;
	char cArr_PC[Row][Column] = {};
	copy_arr(_cArr, cArr_PC);

	system("cls");
	while (true)
	{
		cout << "\t    " << "===User===" << "\t\t\t\t\t      " << "===PC===" << endl;
		print_arr(_cArr, cArr_PC);
		input_key(iInput);

		if (iInput % 5 == 0)
		{
			if (_cArr[(iInput / 5) - 1][Column - 1] == 'O' ||
				_cArr[(iInput / 5) - 1][Column - 1] == 'X')
			{
				cout << "잘못된 입력입니다." << endl;
				System_Helper();
				continue;
			}
			else
			{
				_cArr[(iInput / 5) - 1][Column - 1] = 'O';
				++iRow_check[(iInput / 5) - 1];
				++iColumn_check[Column - 1];

				int iAdd = ((iInput / 5) - 1) + (Column - 1);

				if (((iInput / 5) - 1) == (Column - 1))
				{
					if (iAdd == 4)
					{
						++iDiagonal_check[1];
					}
					++iDiagonal_check[0];
				}
				else if (iAdd == 4)
				{
					++iDiagonal_check[1];
				}

				if (iDiagonal_check[0] == 5 || iDiagonal_check[1] == 5 || iRow_check[(iInput / 5) - 1] == 5 || iColumn_check[Column - 1] == 5)
				{
					cout << "\t    " << "===User===" << "\t\t\t\t\t      " << "===PC===" << endl;
					print_arr(_cArr, cArr_PC);
					cout << endl << "승자: User" << endl;
					bWinner_Decision = true;
					return;
				}
				break;
			}
		}
		else
		{
			if (_cArr[iInput / 5][(iInput % 5) - 1] == 'O' ||
				_cArr[iInput / 5][(iInput % 5) - 1] == 'X')
			{
				cout << "잘못된 입력입니다." << endl;
				System_Helper();
				continue;
			}
			else
			{
				_cArr[iInput / 5][(iInput % 5) - 1] = 'O';
				++iRow_check[(iInput / 5)];
				++iColumn_check[(iInput % 5) - 1];

				int iAdd = ((iInput / 5)) + ((iInput % 5) - 1);

				if (((iInput / 5)) == ((iInput % 5) - 1))
				{
					if (iAdd == 4)
					{
						++iDiagonal_check[1];
					}
					++iDiagonal_check[0];
				}
				else if (iAdd == 4)
				{
					++iDiagonal_check[1];
				}

				if (iDiagonal_check[0] == 5 || iDiagonal_check[1] == 5 || iRow_check[(iInput / 5)] == 5 || iColumn_check[iInput % 5 - 1] == 5)
				{
					cout << "\t    " << "===User===" << "\t\t\t\t\t      " << "===PC===" << endl;
					print_arr(_cArr, cArr_PC);
					cout << endl << "승자: User" << endl;
					bWinner_Decision = true;
					return;
				}
				break;
			}
		}
	}
	copy_arr(_cArr, cArr_PC);
	++_iCount;
	PC_turn(_cArr, cArr_PC, _iCount);
}

void PC_turn(char(&_cArr)[Row][Column], char(&_cArr_PC)[Row][Column], int& _iCount)
{
	if (_iCount == 25)
	{
		cout << "게임이 끝났습니다." << endl;
		System_Helper();
		return;
	}

	while (true)
	{
		int iPC_Input = dist(mt);

		if (iPC_Input == 0)
		{
			if (_cArr[0][0] == 'O' || _cArr[0][0] == 'X')
				continue;
			_cArr_PC[0][0] = 'X';

			++iRow_check_PC[0];
			++iColumn_check_PC[0];
			++iDiagonal_check_PC[0];

			if (iDiagonal_check_PC[0] == 5 || iDiagonal_check_PC[1] == 5 || iRow_check_PC[0] == 5 || iColumn_check_PC[0] == 5)
			{
				cout << "\t    " << "===User===" << "\t\t\t\t\t      " << "===PC===" << endl;
				print_arr(_cArr, _cArr_PC);
				cout << endl << "승자: PC" << endl;
				bWinner_Decision = true;
				return;
			}
			break;
		}
		if (iPC_Input % 5 == 0)
		{
			if (_cArr_PC[(iPC_Input / 5) - 1][Column - 1] == 'O' ||
				_cArr_PC[(iPC_Input / 5) - 1][Column - 1] == 'X')
				continue;
			else
			{
				_cArr_PC[(iPC_Input / 5) - 1][Column - 1] = 'X';
				++iRow_check_PC[(iPC_Input / 5) - 1];
				++iColumn_check_PC[Column - 1];

				int iAdd = ((iPC_Input / 5) - 1) + (Column - 1);

				if (((iPC_Input / 5) - 1) == (Column - 1))
				{
					if (iAdd == 4)
					{
						++iDiagonal_check_PC[1];
					}
					++iDiagonal_check_PC[0];
				}
				else if (iAdd == 4)
				{
					++iDiagonal_check_PC[1];
				}

				if (iDiagonal_check_PC[0] == 5 || iDiagonal_check_PC[1] == 5 || iRow_check_PC[(iPC_Input / 5) - 1] == 5 || iColumn_check_PC[Column - 1] == 5)
				{
					cout << "\t    " << "===User===" << "\t\t\t\t\t      " << "===PC===" << endl;
					print_arr(_cArr, _cArr_PC);
					cout << endl << "승자: PC" << endl;
					bWinner_Decision = true;
					return;
				}
				break;
			}
		}
		else
		{
			if (_cArr_PC[iPC_Input / 5][(iPC_Input % 5) - 1] == 'O' ||
				_cArr_PC[iPC_Input / 5][(iPC_Input % 5) - 1] == 'X')
				continue;
			else
			{
				_cArr_PC[iPC_Input / 5][(iPC_Input % 5) - 1] = 'X';
				++iRow_check_PC[(iPC_Input / 5)];
				++iColumn_check_PC[Column - 1];

				int iAdd = ((iPC_Input / 5)) + ((iPC_Input % 5) - 1);

				if (((iPC_Input / 5)) == ((iPC_Input % 5) - 1))
				{
					if (iAdd == 4)
					{
						++iDiagonal_check_PC[1];
					}
					++iDiagonal_check_PC[0];
				}
				else if (iAdd == 4)
				{
					++iDiagonal_check_PC[1];
				}

				if (iDiagonal_check_PC[0] == 5 || iDiagonal_check_PC[1] == 5 || iRow_check_PC[(iPC_Input / 5) - 1] == 5 || iColumn_check_PC[(iPC_Input % 5) - 1] == 5)
				{
					cout << "\t    " << "===User===" << "\t\t\t\t\t      " << "===PC===" << endl;
					//cout << " " << iDiagonal_check_PC[0] << " " << " " << iDiagonal_check_PC[1]<< iRow_check_PC[(iPC_Input / 5) - 1]<< iColumn_check_PC[(iPC_Input % 5) - 1]<<endl;
					print_arr(_cArr, _cArr_PC);
					cout << endl << "승자: PC" << endl;
					bWinner_Decision = true;
					return;
				}
				break;
			}
		}
	}

	++_iCount;
	cout << "\t    " << "===User===" << endl;
	print_arr_sep(_cArr);
	System_Helper();
	cout << "\t    " << "===PC===" << endl;
	print_arr_sep(_cArr_PC);
	System_Helper();
	copy_arr(_cArr_PC, _cArr);
}

void input_key(int& _iInput)
{
	cout << "숫자를 입력하시오: ";
	cin >> _iInput;
	System_Helper();
}

void print_arr(const char(&_cArr)[Row][Column], const char(&_cArr_PC)[Row][Column])
{
	for (register int i = 0; i < Row; ++i)
	{
		for (register int j = 0; j < Column; ++j)
		{
			if (_cArr[i][j] == 'O' || _cArr[i][j] == 'X')
				cout << _cArr[i][j] << "\t";
			else
				cout << static_cast<int>(_cArr[i][j]) << "\t";
		}
		cout << "\t";
		for (register int j = 0; j < Column; ++j)
		{
			if ((static_cast<int>(_cArr_PC[i][j]) == 79) || (static_cast<int>(_cArr_PC[i][j]) == 88))
				cout << _cArr_PC[i][j] << "\t";
			else
				cout << static_cast<int>(_cArr_PC[i][j]) << "\t";
		}
		cout << endl;
	}
}

void print_arr_sep(const char(&_cArr)[Row][Column])
{
	for (register int i = 0; i < Row; ++i)
	{
		for (register int j = 0; j < Column; ++j)
		{
			if ((_cArr[i][j] == 'O') || (_cArr[i][j] == 'X'))
				cout << _cArr[i][j] << "\t";
			else
				cout << static_cast<int>(_cArr[i][j]) << "\t";
		}
		cout << endl;
	}
}

void copy_arr(char(&_cArr)[Row][Column], char(&_cArr_PC)[Row][Column])
{
	for (register int i = 0; i < Row; ++i)
	{
		for (register int j = 0; j < Column; ++j)
		{
			_cArr_PC[i][j] = _cArr[i][j];
		}
	}
}

void System_Helper()
{
	Sleep(100);
	system("cls");
}