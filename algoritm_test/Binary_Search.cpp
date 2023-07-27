#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;

//���� �˻� �Լ��� �߰��Ѵ�.
bool linear_search(int N, vector<int>& S)
{
	for (const auto& i : S)
	{
		if (i == N)
			return true;
	}
	return false;
}

bool binary_search(int N, vector<int>& S)
{
	auto first = S.begin();
	auto last = S.end();

	while (true)
	{
		//���� �˻� ������ �߰� ���Ҹ� mid element�� ����
		auto range_length = distance(first, last);
		auto mid_element_index = first + floor(range_length / 2);
		auto mid_element = *mid_element_index;
		auto dist_mid_index = distance(first, mid_element_index);

		if (mid_element == N)
			return true;
		else if (mid_element > N)
			advance(last, -dist_mid_index);
		else
			advance(first, dist_mid_index);

		//���� �˻� ������ �ϳ��� ���Ҹ� ���� �ִٸ� false�� ��ȯ
		if (range_length == 1)
		{
			return false;
		}
	}
}

//���� �˻��� ������ ���ϱ� ���� �߰������� �� ���� �׽�Ʈ �Լ��� �����.
void run_small_search_test()
{
	auto N = 2;
	vector<int> S{1, 3, 2, 4, 5, 7, 9, 8, 6};

	sort(S.begin(), S.end());

	if (linear_search(N, S))
		cout << "���� �˻����� ���Ҹ� ã�ҽ��ϴ�." << endl;
	else
		cout << "���� �˻����� ���Ҹ� ã�� ���߽��ϴ�." << endl;

	if (binary_search(N, S))
		cout << "���� �˻����� ���Ҹ� ã�ҽ��ϴ�" << endl;
	else
		cout << "���� �˻����� ���Ҹ� ã�� ���߽��ϴ�." << endl;
}

void run_large_search_test(int size, int N)
{
	vector<int> S;
	random_device rd;
	mt19937 rand(rd());

	//[1,size] �������� ���� ���� �߻�
	uniform_int_distribution<mt19937::result_type> uniform_dist(1, size);

	for (auto i = 0; i < size; ++i)
		S.push_back(uniform_dist(rand));

	sort(S.begin(), S.end());

	//�˻� �ð� ���� ���� :���� �ð��� ����
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();

	bool search_result = binary_search(N, S);

	//�˻� �ð� ���� ���� :���� �ð��� ����
	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	//�� �ð��� ���̸� microseconds�� ĳ�����Ͽ� ����
	auto diff = chrono::duration_cast<chrono::microseconds>(end - begin);
	cout << "���� �˻� ���� �ð�" << diff.count() << endl;

	if (search_result)
		cout << "���Ҹ� ã�ҽ��ϴ�." << endl;
	else
		cout << "���Ҹ� ã�� ���߽��ϴ�." << endl;
}

int main()
{
	run_small_search_test();

	run_large_search_test(100000, 36543);
	run_large_search_test(1000000, 36543);
	run_large_search_test(10000000, 36543);

	return 0;
}