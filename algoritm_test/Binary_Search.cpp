#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;

//선형 검색 함수를 추가한다.
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
		//현재 검색 범위의 중간 원소를 mid element에 저장
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

		//현재 검색 범위에 하나의 원소만 남아 있다면 false를 반환
		if (range_length == 1)
		{
			return false;
		}
	}
}

//이진 검색의 성능을 평가하기 위해 추가적으로 두 개의 테스트 함수를 만든다.
void run_small_search_test()
{
	auto N = 2;
	vector<int> S{1, 3, 2, 4, 5, 7, 9, 8, 6};

	sort(S.begin(), S.end());

	if (linear_search(N, S))
		cout << "선형 검색으로 원소를 찾았습니다." << endl;
	else
		cout << "선형 검색으로 원소를 찾지 못했습니다." << endl;

	if (binary_search(N, S))
		cout << "이진 검색으로 원소를 찾았습니다" << endl;
	else
		cout << "이진 검색으로 원소를 찾지 못했습니다." << endl;
}

void run_large_search_test(int size, int N)
{
	vector<int> S;
	random_device rd;
	mt19937 rand(rd());

	//[1,size] 범위에서 정수 난수 발생
	uniform_int_distribution<mt19937::result_type> uniform_dist(1, size);

	for (auto i = 0; i < size; ++i)
		S.push_back(uniform_dist(rand));

	sort(S.begin(), S.end());

	//검색 시간 측정 시작 :현재 시간을 기준
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();

	bool search_result = binary_search(N, S);

	//검색 시간 측정 종료 :현재 시간을 기준
	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	//두 시간의 차이를 microseconds로 캐스팅하여 저장
	auto diff = chrono::duration_cast<chrono::microseconds>(end - begin);
	cout << "이진 검색 수행 시간" << diff.count() << endl;

	if (search_result)
		cout << "원소를 찾았습니다." << endl;
	else
		cout << "원소를 찾지 못했습니다." << endl;
}

int main()
{
	run_small_search_test();

	run_large_search_test(100000, 36543);
	run_large_search_test(1000000, 36543);
	run_large_search_test(10000000, 36543);

	return 0;
}