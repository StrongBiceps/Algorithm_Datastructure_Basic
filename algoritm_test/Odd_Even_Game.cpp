#include <iostream>
#include <random>
#include <Windows.h>
using namespace std;
//Ȧ¦ ����

int main()
{
	int iMin = 1, iMax = 10, iRound = 3, iWin = 0, iLose = 0;
	random_device rd;
	mt19937_64 mt(rd());
	uniform_int_distribution<int> range(iMin, iMax);

	while (true)
	{
		if (iRound == 0)
		{
			Sleep(1000);
			system("cls");
			cout << "��: " << iWin << "\t" << "��: " << iLose;
			break;
		}

		int iRandom = range(mt);
		int iInput = 0;

		if (iRound != 3)
		{
			Sleep(1000);
			system("cls");
		}

		cout << "�����Ͻÿ�" << endl;
		cout << "1. Ȧ�� 2.¦�� 3.����" << endl;
		cin >> iInput;

		switch (iInput)
		{
		case 1:
		{
			if (0 == iRandom % 2)
			{
				system("cls");
				cout << "�й�" << endl;
				++iLose;
				break;
			}
			else
			{
				system("cls");
				cout << "�¸�" << endl;
				++iWin;
				break;
			}
		}
		case 2:
		{
			if (0 == iRandom % 2)
			{
				system("cls");
				cout << "�¸�" << endl;
				++iWin;
				break;
			}
			else
			{
				system("cls");
				cout << "�й�" << endl;
				++iLose;
				break;
			}
		}
		case 3:
		{
			system("cls");
			cout << "��: " << iWin << "\t" << "��: " << iLose;
			break;
		}
		}

		if (3 == iInput)
		{
			break;
		}

		--iRound;
	}
	return 0;
}