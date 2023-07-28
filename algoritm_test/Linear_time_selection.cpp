#include <iostream>
#include <vector>
using namespace std;
/*
피봇 값을 기준으로 오른쪽에는 pivot보다 큰 원소들이, 왼쪽에는 pivot보다 작거나 같은 원소들이 위치한다.
while문을 벗어났을 때 L과 R이 만나는 지점을 기준으로 오른쪽은 pivot보다 커야 한다.
그러나 pivot이 right_iter보다 클 경우에는 해당 위치로 피벗이 들어가야 한다는 소리이다.
right_iter부터는 무조건 피벗보다 큰 값들이 들어가야 한다. 피벗의 초기 위치에 관계 없이 적용된다.
다음과 같은 상황이 예이다.
1 5 3 4 2
L p     R
  p     LR

1 4 3 5 2
L     p R
	  p LR

	  피벗이 5라고 하면 피벗이 어디에 위치해 있든 LR보다 피벗이 크면 잘못된 위치에 피벗이 존재하는 것이다.
	  따라서 교환해준다.
*/
//퀵 정렬에서 피벗 위치 반복자를 인자로 받는 형태의 분할 함수를 정의한다.

//여기서 전달되는 iterator pivot은 원본 벡터의 반복자가 아니라 M 벡터의 반복자이다. 하지만 참조하는 원소의 값은
//같기 때문에 상관이 없다. 여기서 pivot의 값
template<typename T>
auto partition_using_given_pivot(typename vector<T>::iterator begin, typename vector<T>::iterator end, typename vector<T>::iterator pivot)
{
	//피벗 위치는 함수 인자로 주어지므로
	//벡터의 시작과 마지막 원소를 가리키는 반복자를 정의한다.
	auto left_iter = begin;
	auto right_iter = end;

	while (true)
	{
		//벡터의 첫 번째 원소부터 시작하여 피벗보다 큰 원소를 찾는다.
		while (*left_iter < *pivot && left_iter != right_iter)
		{
			++left_iter;
		}

		//벡터의 마지막 원소부터 시작하여 역순으로 피벗보다 작은 원소를 찾는다.
		while (*right_iter >= *pivot && left_iter != right_iter)
		{
			--right_iter;
		}

		//left_iter와 right_iter가 같다면 교환할 원소가 없다는 것을 뜻한다.
		//그렇지 않으면 left_iter와 right_iter가 가리키는 원소를 교환한다.
		if (left_iter == right_iter)
			break;
		else
			iter_swap(left_iter, right_iter);
	}

	if (*pivot > *right_iter)
		iter_swap(pivot, right_iter);

	return right_iter;
}

template <typename T>
auto partition(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator end)
{
	auto pivot_val = *begin;
	auto left_iter = begin + 1;
	auto right_iter = end;

	while (true)
	{
		while (*left_iter <= pivot_val && left_iter != right_iter)
			left_iter++;
		while (*right_iter > pivot_val && left_iter != right_iter)
			right_iter--;


		if (left_iter == right_iter)
			break;
		else
			std::iter_swap(left_iter, right_iter);
	}

	if (pivot_val > *right_iter)
		std::iter_swap(begin, right_iter);

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

//두 반복자 사이의 중간 값을 찾는 함수를 정의한다.
template<typename T>
auto find_median(typename vector<T>::iterator begin, typename vector<T>::iterator last)
{
	//정렬을 진행한다.
	quick_sort<T>(begin, last);

	//가운데(median) 원소 반복자를 반환
	return begin + (distance(begin, last) / 2);
}

//vector<T>& arr이라고 한다면 L Value만을 매개변수로 받을 수 있다.
//하지만 merge_sort가 R value 임시 객체를 리턴하기 때문에
//print_vector<int>(merge_sort<int>(S1)); 이 코드에서 문제가 발생한다.
template<typename T>
void print_vector(vector<T> arr)
{
	for (const auto& i : arr)
	{
		cout << i << " ";
	}
	cout << endl;
}


//선형 시간 검색 알고리즘을 구현한다.
template<typename T>
typename vector<T>::iterator linear_time_select(typename vector<T>::iterator begin, typename vector<T>::iterator last, size_t i)
{
	auto size = distance(begin, last);

	//i는 몇 번째로 순서의 수 인지를 의미하는 것이므로 1부터다. 또한 size보다 클 수는 없다. 지금의 경우는
	//12번째까지 가능하다.
	if (size > 0 && i < size)
	{
		//다섯 개 원소로 구분하여 만들 부분 벡터 Vi의 개수 계산
		//13개가 있으면 최소 부분 벡터가 3개 있어야 하므로 4를 더해서 나눈 값이 3이 나오도록 한다.
		//11개가 있을 때에도 최소 3개가 필요하므로 4를 더해줘야 3의 값이 나온다.
		auto num_Vi = (size + 4) / 5;
		size_t j = 0;

		//각각의 Vi에서 중앙값을 찾아 벡터 M에 저장
		vector<T> M;

		for (; j < size / 5; ++j)
		{
			auto b = begin + (j * 5);
			auto l = begin + (j * 5) + 5;

			auto median = find_median<T>(b, l);
			M.push_back(*median);
		}

		//5개 원소씩 부분 벡터로 나누고 남은 원소의 중앙값을 추출한다.
		if (j * 5 < size)
		{
			auto b = begin + (j * 5);
			auto l = begin + (j * 5) + (size % 5);

			auto median = find_median<T>(b, l);
			M.push_back(*median);
		}

		/// Vi의 중앙값으로 구성된 벡터 M에서 다시 중앙값 q를 찾음
		auto median_of_medians = (M.size() == 1) ? M.begin() : linear_time_select<T>(M.begin(), M.end() - 1, M.size() / 2);

		//분할 연산을 적용하고 피벗 위치 q의 위치 k를 찾음
		auto partition_iter = partition_using_given_pivot<T>(begin, last, median_of_medians);

		//만약 partition_iter가 가리키는 값이 찾고 있는 i번째 값이더라도 distance는 i번째보다 1이 작기 때문에
		//1을 더해서 맞는지 확인하는 것이다.
		auto k = distance(begin, partition_iter) + 1;

		//i < k라면 일단 partition_iter 이전 값들은 median_of_medians보다 작다는 것이다.
		//따라서 i번째를 찾고 있지만 k가 더 크므로 partition_iter보다 더 작은 값을 찾아야 한다는  것이다.
		//따라서 partition_iter -1의 값은 medians_of_medians보다 작으므로 다시 해당 범위부터 찾는 것이다.
		//마찬가지로 만약 k가 더 작다면 partition_iter보다 같거나 큰 값을 찾아야 한다는 뜻이다. 그럼 partition_iter보다 
		//큰 범위를 다시 찾으면 된다.
		if (i == k)
		{
			return partition_iter;
		}
		else if (i < k)
			return linear_time_select<T>(begin, partition_iter - 1, i);
		else if (i > k)
			return linear_time_select<T>(partition_iter + 1, last, i - k);
	}
	else
		//원래는 begin을 리턴하는 것이 책에 있는 코드인데, 생각을 해보면 partition_iter
		//return begin
		return last;
}

//병합 정렬 구현 함수를 추가한다. 이 함수는 선형 시간 선택 알고리즘에 의해 선택된 i번째 원소가 정확한지를 확인하기 위한 용도로 사용한다.
template<typename T>
vector<T> merge(vector<T>& arr1, vector<T>& arr2)
{
	vector<T> merged;
	auto iter1 = arr1.begin();
	auto iter2 = arr2.begin();

	while (iter1 != arr1.end() && iter2 != arr2.end())
	{
		if (*iter1 < *iter2)
		{
			merged.emplace_back(*iter1);
			++iter1;
		}
		else
		{
			merged.emplace_back(*iter2);
			++iter2;
		}
	}

	if (iter1 != arr1.end())
	{
		for (; iter1 != arr1.end(); ++iter1)
		{
			merged.emplace_back(*iter1);
		}
	}
	else
	{
		for (; iter2 != arr2.end(); ++iter2)
		{
			merged.emplace_back(*iter2);
		}
	}

	return merged;
}

template<typename T>
vector<T> merge_sort(vector<T> arr)
{
	if (arr.size() > 1)
	{
		auto mid = size_t(arr.size() / 2);
		auto left_half = merge_sort(vector<T>(arr.begin(), arr.begin() + mid));
		auto right_half = merge_sort(vector<T>(arr.begin() + mid, arr.end()));

		return merge<T>(left_half, right_half);
	}
	return arr;
}

void run_linear_select_test()
{

	vector<int> S1{45, 1, 3, 1, 2, 3, 45, 5, 1, 2, 44, 5, 7};
	cout << "입력 벡터: " << endl;
	print_vector<int>(S1);

	cout << "정렬된 벡터: " << endl;
	print_vector<int>(merge_sort<int>(S1));

	cout << "원본 벡터: " << endl;
	print_vector<int>(S1);
	cout << "3번째 원소: " << *linear_time_select<int>(S1.begin(), S1.end() - 1, 4);
	cout << endl;
	cout << "5번째 원소: " << *linear_time_select<int>(S1.begin(), S1.end() - 1, 5);
	cout << endl;
	cout << "11번째 원소: " << *linear_time_select<int>(S1.begin(), S1.end() - 1, 11);
	cout << endl;

	//vector<int> S2{1, 2, 3, 4,5,6,7,8,9,10};
	//cout << *linear_time_select<int>(S2.begin(), S2.end() - 1, );
}

int main()
{
	run_linear_select_test();

	return 0;
}