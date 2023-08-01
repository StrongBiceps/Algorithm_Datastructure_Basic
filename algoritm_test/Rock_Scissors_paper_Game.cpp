#include <iostream>
#include <Windows.h>
#include <random>
using namespace std;
//가위 바위 보 게임
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
			cout << "3라운드 결과 Win: " << iWin << " Lose" << iLose << endl;
			break;
		}

		int iRandom = range(mt), iInput = 0, iSub = 0;

		cout << "선택하시오" << endl;
		cout << "1.가위 2.바위 3.보" << endl;
		cin >> iInput;

		Sleep(1000);
		system("cls");

		iSub = iInput - iRandom;

		if (1 > iInput || 4 < iInput)
		{
			cout << "잘못된 입력입니다." << endl;
			Sleep(1000);
			system("cls");
			continue;
		}

		if (4 == iInput)
		{
			cout << "결과 Win: " << iWin << " Lose" << iLose << endl;
			Sleep(1000);
			system("cls");
			cout << "게임을 종료합니다." << endl;
			break;
		}

		if (1 == iSub || -2 == iSub)
		{
			cout << "당신이 이겼습니다" << endl;
			++iWin;
			Sleep(1000);
			system("cls");
			--iRound;
			continue;
		}
		else if (0 == iSub)
		{
			cout << "비겼습니다." << endl;
			Sleep(1000);
			system("cls");
			--iRound;
			continue;
		}
		else
		{
			cout << "당신이 졌습니다." << endl;
			++iLose;
			Sleep(1000);
			system("cls");
			--iRound;
			continue;
		}
	}

	return 0;
}