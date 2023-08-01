#include <iostream>
#include <Windows.h>
#include <random>
using namespace std;
//���� ���� �� ����
int main()
{
	int iMin = 1, iMax = 3, iRound = 3, iWin = 0, iLose = 0;

	random_device rd;
	mt19937_64 mt(rd());
	uniform_int_distribution<int> range(iMin, iMax);

	while (true)
	{
		if (0 == iRound)
		{
			cout << "3���� ��� Win: " << iWin << " Lose" << iLose << endl;
			break;
		}

		int iRandom = range(mt), iInput = 0, iSub = 0;

		cout << "�����Ͻÿ�" << endl;
		cout << "1.���� 2.���� 3.��" << endl;
		cin >> iInput;

		Sleep(1000);
		system("cls");

		iSub = iInput - iRandom;

		if (1 > iInput || 4 < iInput)
		{
			cout << "�߸��� �Է��Դϴ�." << endl;
			Sleep(1000);
			system("cls");
			continue;
		}

		if (4 == iInput)
		{
			cout << "��� Win: " << iWin << " Lose" << iLose << endl;
			Sleep(1000);
			system("cls");
			cout << "������ �����մϴ�." << endl;
			break;
		}

		if (1 == iSub || -2 == iSub)
		{
			cout << "����� �̰���ϴ�" << endl;
			++iWin;
			Sleep(1000);
			system("cls");
			--iRound;
			continue;
		}
		else if (0 == iSub)
		{
			cout << "�����ϴ�." << endl;
			Sleep(1000);
			system("cls");
			--iRound;
			continue;
		}
		else
		{
			cout << "����� �����ϴ�." << endl;
			++iLose;
			Sleep(1000);
			system("cls");
			--iRound;
			continue;
		}
	}

	return 0;
}