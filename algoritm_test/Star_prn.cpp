#include <iostream>
using namespace std;
//별 출력 프로그램
int main()
{
	for (int i = 5; i >= 1; --i)
	{
		for (int j = 1; j <= 5; ++j)
		{
			if (i <= j)
			{
				cout << "*";
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 1; i <= 5; ++i)
	{
		for (int j = 1; j <= 5; ++j)
		{
			if (i > j)
			{
				cout << " ";
			}
			else
			{
				cout << "*";
			}
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 1; i <= 5; ++i)
	{
		for (int j = 1; j <= i; ++j)
		{
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 5; i >= 1; --i)
	{
		for (int j = 1; j <= i; ++j)
		{
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;

	return 0;
}