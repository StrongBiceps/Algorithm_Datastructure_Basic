#include <iostream>
#include <vector>
using namespace std;
/*
�Ǻ� ���� �������� �����ʿ��� pivot���� ū ���ҵ���, ���ʿ��� pivot���� �۰ų� ���� ���ҵ��� ��ġ�Ѵ�.
while���� ����� �� L�� R�� ������ ������ �������� �������� pivot���� Ŀ�� �Ѵ�.
�׷��� pivot�� right_iter���� Ŭ ��쿡�� �ش� ��ġ�� �ǹ��� ���� �Ѵٴ� �Ҹ��̴�.
right_iter���ʹ� ������ �ǹ����� ū ������ ���� �Ѵ�. �ǹ��� �ʱ� ��ġ�� ���� ���� ����ȴ�.
������ ���� ��Ȳ�� ���̴�.
1 5 3 4 2
L p     R
  p     LR

1 4 3 5 2
L     p R
	  p LR

	  �ǹ��� 5��� �ϸ� �ǹ��� ��� ��ġ�� �ֵ� LR���� �ǹ��� ũ�� �߸��� ��ġ�� �ǹ��� �����ϴ� ���̴�.
	  ���� ��ȯ���ش�.
*/
//�� ���Ŀ��� �ǹ� ��ġ �ݺ��ڸ� ���ڷ� �޴� ������ ���� �Լ��� �����Ѵ�.

//���⼭ ���޵Ǵ� iterator pivot�� ���� ������ �ݺ��ڰ� �ƴ϶� M ������ �ݺ����̴�. ������ �����ϴ� ������ ����
//���� ������ ����� ����. ���⼭ pivot�� ��
template<typename T>
auto partition_using_given_pivot(typename vector<T>::iterator begin, typename vector<T>::iterator end, typename vector<T>::iterator pivot)
{
	//�ǹ� ��ġ�� �Լ� ���ڷ� �־����Ƿ�
	//������ ���۰� ������ ���Ҹ� ����Ű�� �ݺ��ڸ� �����Ѵ�.
	auto left_iter = begin;
	auto right_iter = end;

	while (true)
	{
		//������ ù ��° ���Һ��� �����Ͽ� �ǹ����� ū ���Ҹ� ã�´�.
		while (*left_iter < *pivot && left_iter != right_iter)
		{
			++left_iter;
		}

		//������ ������ ���Һ��� �����Ͽ� �������� �ǹ����� ���� ���Ҹ� ã�´�.
		while (*right_iter >= *pivot && left_iter != right_iter)
		{
			--right_iter;
		}

		//left_iter�� right_iter�� ���ٸ� ��ȯ�� ���Ұ� ���ٴ� ���� ���Ѵ�.
		//�׷��� ������ left_iter�� right_iter�� ����Ű�� ���Ҹ� ��ȯ�Ѵ�.
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
	//���� ���Ϳ� �ϳ� �̻��� ���Ұ� �ִٸ� ���� �۾��� �����Ѵ�.
	if (distance(begin, last) >= 1)
	{
		auto partition_iter = partition<T>(begin, last);

		//���� �۾��� ���� ������ ���͸� ��������� ����
		quick_sort<T>(begin, partition_iter - 1);
		quick_sort<T>(partition_iter, last);
	}
}

//�� �ݺ��� ������ �߰� ���� ã�� �Լ��� �����Ѵ�.
template<typename T>
auto find_median(typename vector<T>::iterator begin, typename vector<T>::iterator last)
{
	//������ �����Ѵ�.
	quick_sort<T>(begin, last);

	//���(median) ���� �ݺ��ڸ� ��ȯ
	return begin + (distance(begin, last) / 2);
}

//vector<T>& arr�̶�� �Ѵٸ� L Value���� �Ű������� ���� �� �ִ�.
//������ merge_sort�� R value �ӽ� ��ü�� �����ϱ� ������
//print_vector<int>(merge_sort<int>(S1)); �� �ڵ忡�� ������ �߻��Ѵ�.
template<typename T>
void print_vector(vector<T> arr)
{
	for (const auto& i : arr)
	{
		cout << i << " ";
	}
	cout << endl;
}


//���� �ð� �˻� �˰����� �����Ѵ�.
template<typename T>
typename vector<T>::iterator linear_time_select(typename vector<T>::iterator begin, typename vector<T>::iterator last, size_t i)
{
	auto size = distance(begin, last);

	//i�� �� ��°�� ������ �� ������ �ǹ��ϴ� ���̹Ƿ� 1���ʹ�. ���� size���� Ŭ ���� ����. ������ ����
	//12��°���� �����ϴ�.
	if (size > 0 && i < size)
	{
		//�ټ� �� ���ҷ� �����Ͽ� ���� �κ� ���� Vi�� ���� ���
		//13���� ������ �ּ� �κ� ���Ͱ� 3�� �־�� �ϹǷ� 4�� ���ؼ� ���� ���� 3�� �������� �Ѵ�.
		//11���� ���� ������ �ּ� 3���� �ʿ��ϹǷ� 4�� ������� 3�� ���� ���´�.
		auto num_Vi = (size + 4) / 5;
		size_t j = 0;

		//������ Vi���� �߾Ӱ��� ã�� ���� M�� ����
		vector<T> M;

		for (; j < size / 5; ++j)
		{
			auto b = begin + (j * 5);
			auto l = begin + (j * 5) + 5;

			auto median = find_median<T>(b, l);
			M.push_back(*median);
		}

		//5�� ���Ҿ� �κ� ���ͷ� ������ ���� ������ �߾Ӱ��� �����Ѵ�.
		if (j * 5 < size)
		{
			auto b = begin + (j * 5);
			auto l = begin + (j * 5) + (size % 5);

			auto median = find_median<T>(b, l);
			M.push_back(*median);
		}

		/// Vi�� �߾Ӱ����� ������ ���� M���� �ٽ� �߾Ӱ� q�� ã��
		auto median_of_medians = (M.size() == 1) ? M.begin() : linear_time_select<T>(M.begin(), M.end() - 1, M.size() / 2);

		//���� ������ �����ϰ� �ǹ� ��ġ q�� ��ġ k�� ã��
		auto partition_iter = partition_using_given_pivot<T>(begin, last, median_of_medians);

		//���� partition_iter�� ����Ű�� ���� ã�� �ִ� i��° ���̴��� distance�� i��°���� 1�� �۱� ������
		//1�� ���ؼ� �´��� Ȯ���ϴ� ���̴�.
		auto k = distance(begin, partition_iter) + 1;

		//i < k��� �ϴ� partition_iter ���� ������ median_of_medians���� �۴ٴ� ���̴�.
		//���� i��°�� ã�� ������ k�� �� ũ�Ƿ� partition_iter���� �� ���� ���� ã�ƾ� �Ѵٴ�  ���̴�.
		//���� partition_iter -1�� ���� medians_of_medians���� �����Ƿ� �ٽ� �ش� �������� ã�� ���̴�.
		//���������� ���� k�� �� �۴ٸ� partition_iter���� ���ų� ū ���� ã�ƾ� �Ѵٴ� ���̴�. �׷� partition_iter���� 
		//ū ������ �ٽ� ã���� �ȴ�.
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
		//������ begin�� �����ϴ� ���� å�� �ִ� �ڵ��ε�, ������ �غ��� partition_iter
		//return begin
		return last;
}

//���� ���� ���� �Լ��� �߰��Ѵ�. �� �Լ��� ���� �ð� ���� �˰��� ���� ���õ� i��° ���Ұ� ��Ȯ������ Ȯ���ϱ� ���� �뵵�� ����Ѵ�.
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
	cout << "�Է� ����: " << endl;
	print_vector<int>(S1);

	cout << "���ĵ� ����: " << endl;
	print_vector<int>(merge_sort<int>(S1));

	cout << "���� ����: " << endl;
	print_vector<int>(S1);
	cout << "3��° ����: " << *linear_time_select<int>(S1.begin(), S1.end() - 1, 4);
	cout << endl;
	cout << "5��° ����: " << *linear_time_select<int>(S1.begin(), S1.end() - 1, 5);
	cout << endl;
	cout << "11��° ����: " << *linear_time_select<int>(S1.begin(), S1.end() - 1, 11);
	cout << endl;

	//vector<int> S2{1, 2, 3, 4,5,6,7,8,9,10};
	//cout << *linear_time_select<int>(S2.begin(), S2.end() - 1, );
}

int main()
{
	run_linear_select_test();

	return 0;
}