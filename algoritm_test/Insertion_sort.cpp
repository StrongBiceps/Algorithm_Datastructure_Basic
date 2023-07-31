#include <iostream>
//오름차순 삽입 정렬
void insertion_sort(int* a, int Num)
{
	for (int i = 1; i < Num; ++i)
	{
		int cur = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > cur)
		{
			a[j + 1] = a[j];
			--j;
		}
		a[j + 1] = cur;
	}
}

int main()
{
	int iTemp[5] = { 10,5,2,6,9 };

	insertion_sort(iTemp, 5);

	for (auto i : iTemp)
	{
		std::cout << i << " ";
	}
	return 0;
}