#include <iostream>
#include <random>
#include <Windows.h>
using namespace std;

random_device rd;
mt19937_64 mt(rd());
uniform_int_distribution<int> dist(1, 9);

void Baseball_Game();
void Init_array(bool* _bArr, const int _iSize);
void Input(int* _iArr, const int _iSize);
void compare(int* _iArr, const int _iSize_i, bool* _bArr, int& _iStrike, int& _iBall);
void print_arr(int* _iArr, const int _iSize, const int _iCount);
void print_strikeAndBall(const int& _iStrike, const int& _iBall);
void System_Helper();

int main()
{
	Baseball_Game();
}

void Baseball_Game()
{
	bool bArr[10] = {};
	int iCount = 1;
	int iInput[3] = {};
	int iStrike = 0, iBall = 0;

	Init_array(bArr, 10);

	while (iCount != 10)
	{
		cout << endl;
		cout << iCount << "회 시작" << endl;
		Input(iInput, 3);

		print_arr(iInput, 3, iCount);

		compare(iInput, 3, bArr, iStrike, iBall);

		print_strikeAndBall(iStrike, iBall);
		++iCount;

		if (iStrike == 3)
		{
			System_Helper();
			cout << "승리했습니다." << endl;
			return;
		}
	}
	System_Helper();
	cout << "패배" << endl;
}

void Init_array(bool* _bArr, const int _iSize)
{
	for (register int i = 0; i < _iSize; ++i)
	{
		_bArr[dist(mt)] = 1;
	}
}

void Input(int* _iArr, const int _iSize)
{
	for (register int i = 0; i < _iSize; ++i)
	{
		cout << i + 1 << " 번째 수를 입력하시오: ";
		cin >> _iArr[i];
		cout << endl;
	}

	System_Helper();
}

void compare(int* _iArr, const int _iSize_i, bool* _bArr, int& _iStrike, int& _iBall)
{
	int iCorrect = 0;

	for (register int i = 0; i < _iSize_i; ++i)
	{
		if (_bArr[_iArr[i]] == 1)
		{
			++iCorrect;
		}
	}

	if (iCorrect > 0)
	{
		++_iStrike;
	}
	else
	{
		++_iBall;
	}
}

void print_arr(int* _iArr, const int _iSize, const int _iCount)
{
	cout << _iCount << "회차: ";

	for (register int i = 0; i < _iSize; ++i)
	{
		cout << _iArr[i] << " ";
	}
}

void print_strikeAndBall(const int& _iStrike, const int& _iBall)
{
	cout << "스트라이크: " << _iStrike << " " << "볼: " << _iBall;
	cout << endl;
}

void System_Helper()
{
	Sleep(1000);
	system("cls");
}