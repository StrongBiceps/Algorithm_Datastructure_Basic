#include <iostream>
#include <vector>
using namespace std;

/*
* 병합 정렬 재귀의 예
시퀀스 5 1 6 4 3 7

left_half = 5 1 6 -> left_half = 5 -> 5 리턴
			 right_half = 1 6 -> left_half = 1 ->1리턴
			 return merge(1,5,6) right_half = 6->6리턴
					     return merge(1 6)
right_half = 4 3 7 -> left_half = 4 -> 4리턴
			  right_half = 3 7 ->left_half = 3 -> 3리턴
			  return merge(347)  right_half = 7 -> 7 리턴
					 return merge(3 7)

최종적으로 두 개의 정렬된 벡터가 merge함수에 들어간다.
최종 return 1 3 4 5 6 7*/

template<typename T>
vector<T> merge(vector<T>& arr1, vector<T>& arr2)
{
	vector<T> merged;

	auto iter1 = arr1.begin();
	auto iter2 = arr2.begin();

	//두 벡터의 원소들을 비교하며 작은 것부터 merged에 push
	while (iter1 != arr1.end() && iter2 != arr2.end())
	{
		if (*iter1 < *iter2)
		{
			merged.emplace_back(*iter1);
			++iter1;
		}
		//두 원소가 같다면 어느 벡터에서 뽑아도 상관 없다. 지금은 
		//arr2에서 뽑는다.
		else
		{
			merged.emplace_back(*iter2);
			++iter2;
		}
	}
	
	//두 벡터중 원소가 남아있는 게 있다면 남은 원소들을 merged에 push
	if (iter1 != arr1.end())
	{
		for (; iter1 != arr1.end(); ++iter1)
			merged.emplace_back(*iter1);
	}
	else
	{
		for (; iter2 != arr2.end(); ++iter2)
			merged.emplace_back(*iter2);
	}

	return merged;
}

template<typename T>
vector<T> merge_sort(vector<T> arr)
{
	if (arr.size() > 1)
	{
		auto mid = size_t(arr.size() / 2);
		//begin부터 begin()+mid 바로 전 원소까지 전달한다.
		auto left_half = merge_sort<T>(vector<T>(arr.begin(), arr.begin() + mid));
		//begin()+mid부터 end()바로 전까지 전달한다.
		auto right_half = merge_sort<T>(vector<T>(arr.begin() + mid, arr.end()));

		return merge<T>(left_half, right_half);
	}
	return arr;
}

//벡터에 포함된 모든 데이터를 출력하는 함수를 작성한다.
template<typename T>
void print_vector(vector<T> arr)
{
	for (const auto& i : arr)
		cout << i << " ";
	cout << endl;
}

void run_merge_sort_test()
{
	vector<int> S1{45, 1, 3, 1, 2, 3, 45, 5, 1, 2, 44, 5, 7};
	vector<float> S2{45.6f, 1.0f, 3.8f, 1.01f, 2.2f, 3.9f, 45.3f, 5.5f, 1.0f, 2.0f, 44.0f, 5.0f, 7.0f};
	vector<double> S3{45.6, 1.0, 3.8, 1.01, 2.2, 3.9, 45.3, 5.5, 1.0, 2.0, 44.0, 5.0, 7.0 };
	vector<char> C{'b', 'z', 'a', 'e', 'f', 't', 'q', 'u', 'y'};

	cout << "정렬되지 않은 입력 벡터" << endl;
	print_vector<int>(S1);
	print_vector<float>(S2);
	print_vector<double>(S3);
	print_vector<char>(C);

	auto sorted_S1 = merge_sort<int>(S1);
	auto sorted_S2 = merge_sort<float>(S2);
	auto sorted_S3 = merge_sort<double>(S3);
	auto sorted_C = merge_sort<char>(C);

	cout << "병합 정렬에 의해 정렬된 벡터" << endl;
	print_vector<int>(sorted_S1);
	print_vector<float>(sorted_S2);
	print_vector<double>(sorted_S3);
	print_vector<char>(sorted_C);
}

int main()
{
	run_merge_sort_test();
	return 0;
}
