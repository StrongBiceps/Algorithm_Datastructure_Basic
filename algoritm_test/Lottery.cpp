#include <iostream>
#include <random>
using namespace std;

random_device rd;
mt19937_64 mt(rd());
uniform_int_distribution<int> dist(1, 45);

void Init_random_array(int* const _iArr, const int _iSize, const int& _iCount);
void Game_Lottery();
void Bubble_sort(int* _iArr, const int _iSize);
void print_arr(int* _iArr, const int _iSize);

int main()
{
	Game_Lottery();

	return 0;
}

void Game_Lottery()
{
	int iCount = 0;
	while (iCount != 6)
	{
		int iArr[6] = {};

		Init_random_array(iArr, 6, iCount);

		++iCount;
	}
}

void Bubble_sort(int* _iArr, const int _iSize)
{
	for (register int i = _iSize; i > 0; --i)
	{
		for (register int j = 0; j < i - 1; ++j)
		{
			if (_iArr[j + 1] < _iArr[j])
			{
				int iTemp = _iArr[j];
				_iArr[j] = _iArr[j + 1];
				_iArr[j + 1] = iTemp;
			}
		}
	}
}

void print_arr(int* _iArr, const int _iSize)
{
	for (register int i = 0; i < _iSize; ++i)
	{
		cout << _iArr[i] << " ";
	}
	cout << endl;
}

void Init_random_array(int* const _iArr, const int _iSize, const int& _iCount)
{
	cout << _iCount + 1 << "회차 진행" << endl;
	for (register int i = 0; i < _iSize; ++i)
	{
		_iArr[i] = dist(mt);
	}
	Bubble_sort(_iArr, _iSize);

	print_arr(_iArr, _iSize);

	cout << endl;
}
