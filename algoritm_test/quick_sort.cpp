#include <iostream>
#include <vector>
using namespace std;

/*
*퀵 정렬 재귀의 예

[5 1 6 4 3 7]

quick_sort(5 1 6 4 3 7)
->partition(5 1 6 4 3 7)
  5 1 6 4 3 7
  p L       R
    1 6 4 3 7
      L   R
결과 5 1 3 4 6 7
	     R
-> quick_sort(5 1 3 4) -> partition(5 1 3 4)
						  5 1 3 4
						  p L   R
						  5 1 3 4(L==R)
						  결과 4 1 3 5(R)
						  ->quick_sort(4 1 3) -> partition(4 1 3)
												 4 1 3
												 P L R
												 4 1 3(L==R)
												 결과 3 1 4(R)
												 ->quick_sort(3 1) -> partition(3 1)
																	  3 1(L==R)
																	  P 
																	  결과 1 3
												   quick_sort(4) -> 결과 4
						    quick_sort(5) -> 결과 5
   quick_sort(6 7) -> partition(6 7)
					  6 7(L==R)
					  P 
					  결과 6 7(R)
					  ->quick_sort(6) -> 결과 6
					    quick_sort(7) -> 결과 7

모든 재귀가 끝나서 최종 결과는 1 3 4 5 6 7
부분 배열들을 병합하는 것이 아니라 부분 배열 안에서 반복자를 통해
원소들의 위치를 교환한다. 따라서 quick_sort는 return값을 가지지 않고
모든 재귀가 종료되었을 시에는 시퀀스가 정렬된 상태로 있다.
*/

//분할 동작을 위한 partition 함수를 다음과 같이 작성한다.
//반복자는 값에 의한 복사를 해도 반복자 내부에는 원소를 가리키는 포인터가 있기 때문에
//주소에 의한 호출과 같은 효과가 있다.
template<typename T>
auto partition(typename vector<T>::iterator begin, typename vector<T>::iterator end)
{
	//세 개의 반복자를 생성한다.
	//하나는 피벗을 가리키고, 나머지 둘은 벡터의 시작과 마지막 원소를 가리킨다.
	auto pivot_val = *begin;
	auto left_iter = begin + 1;
	auto right_iter = end;

	//피벗을 중심으로 피벗보다 작거나 같은 원소들은 피벗의 왼쪽으로 이동시키고,
	//피벗보다 큰 원소들은 피벗의 오른쪽으로 이동시킨다.
	//left와 right가 같아지면 while을 벗어나는 이유는 피벗을 중심으로 
	//왼쪽은 이미 피벗보다 작고 오른쪽은 피벗보다 크다는 의미이다. 따라서 다른 연산을 할 필요가 없다.
	// 예를 들어 5 1 2 6 7 의 시퀀스가 있다고 하고 피벗이 5라고 한다면, left_iter와 right_iter는 6에서 만날 것이다.
	//즉 만난 지점 앞이 피벗이 위치할 공간인 것이다. 5를 삽입하면 1 2 5 6 7이 된다. 즉 두 반복자가 만난 지점을 중심으로
	//왼쪽은 피벗보다 작고 만난 지점을 포함한 오른쪽은 피벗보다 큰 것이다.
	while (true)
	{
		//벡터의 첫 번째 원소부터 시작하여 피벗보다 큰 원소를 찾는다.
		while (*left_iter <= pivot_val && distance(left_iter, right_iter) > 0)
			++left_iter;

		//벡터의 마지막 원소부터 시작하여 역순으로 피벗보다 작은 원소를 찾는다.
		while (*right_iter > pivot_val && distance(left_iter, right_iter) > 0)
			--right_iter;

		//만약 left_iter와 right_iter가 같다면, 교환할 원소가 없음을 의미한다.
		//그렇지 않으면 left_iter와 right_iter가 가리키는 원소를 서로 교환한다.
		if (left_iter == right_iter)
		{
			break;
		}
		else
		{
			iter_swap(left_iter, right_iter);
		}
	}

	//피벗을 중심으로 왼쪽과 오른쪽이 크기에 맞게 배치되었다면, right_iter와 pivot을 비교한다.
	//만약 right_iter가 더 작다면 피봇과 위치를 바꿔야 왼쪽과 오른쪽에 각각 크기에 맞는 원소가 배치되게 된다.
	if (pivot_val > *right_iter)
	{
		iter_swap(begin, right_iter);
	}

	return right_iter;
}

template<typename T>
void quick_sort(typename vector<T>::iterator begin, typename vector<T>::iterator last)
{
	//만약 벡터에 하나 이상의 원소가 있다면 분할 작업을 수행한다.
	if (distance(begin, last) >= 1)
	{
		auto partition_iter = partition<T>(begin, last);

		//분할 작업에 의해 생성된 벡터를 재귀적으로 정렬
		quick_sort<T>(begin, partition_iter - 1);
		quick_sort<T>(partition_iter, last);
	}
}

template<typename T>
void print_vector(vector<T> arr)
{
	for (const auto& i : arr)
	{
		cout << i << " ";
	}
	cout << endl;
}

void run_quick_sort_test()
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

	//arr.end()는 맨 마지막 원소 다음을 가리키므로 end()-1을 전달한다.
	quick_sort<int>(S1.begin(), S1.end() - 1);
	quick_sort<float>(S2.begin(), S2.end() - 1);
	quick_sort<double>(S3.begin(), S3.end() - 1);
	quick_sort<char>(C.begin(), C.end() - 1);

	cout << "퀵 정렬에 의해 정렬된 벡터" << endl;
	print_vector<int>(S1);
	print_vector<float>(S2);
	print_vector<double>(S3);
	print_vector<char>(C);
	cout << endl;

	vector<int> temp{5, 4, 3, 2, 1};
	quick_sort<int>(temp.begin(), temp.end() - 1);
	print_vector<int>(temp);

}

int main()
{
	run_quick_sort_test();

	return 0;
}
