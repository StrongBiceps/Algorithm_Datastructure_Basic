#include <iostream>
#include <vector>
using namespace std;

/*
* ���� ���� ����� ��
������ 5 1 6 4 3 7

left_half = 5 1 6 -> left_half = 5 -> 5 ����
			 right_half = 1 6 -> left_half = 1 ->1����
			 return merge(1,5,6) right_half = 6->6����
								 return merge(1 6)
right_half = 4 3 7 -> left_half = 4 -> 4����
			  right_half = 3 7 ->left_half = 3 -> 3����
			  return merge(347)  right_half = 7 -> 7 ����
								 return merge(3 7)

���������� �� ���� ���ĵ� ���Ͱ� merge�Լ��� ����.
���� return 1 3 4 5 6 7*/

template<typename T>
vector<T> merge(vector<T>& arr1, vector<T>& arr2)
{
	vector<T> merged;

	auto iter1 = arr1.begin();
	auto iter2 = arr2.begin();

	//�� ������ ���ҵ��� ���ϸ� ���� �ͺ��� merged�� push
	while (iter1 != arr1.end() && iter2 != arr2.end())
	{
		if (*iter1 < *iter2)
		{
			merged.emplace_back(*iter1);
			++iter1;
		}
		//�� ���Ұ� ���ٸ� ��� ���Ϳ��� �̾Ƶ� ��� ����. ������ 
		//arr2���� �̴´�.
		else
		{
			merged.emplace_back(*iter2);
			++iter2;
		}
	}
	
	//�� ������ ���Ұ� �����ִ� �� �ִٸ� ���� ���ҵ��� merged�� push
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
		//begin���� begin()+mid �ٷ� �� ���ұ��� �����Ѵ�.
		auto left_half = merge_sort<T>(vector<T>(arr.begin(), arr.begin() + mid));
		//begin()+mid���� end()�ٷ� ������ �����Ѵ�.
		auto right_half = merge_sort<T>(vector<T>(arr.begin() + mid, arr.end()));

		return merge<T>(left_half, right_half);
	}
	return arr;
}

//���Ϳ� ���Ե� ��� �����͸� ����ϴ� �Լ��� �ۼ��Ѵ�.
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

	cout << "���ĵ��� ���� �Է� ����" << endl;
	print_vector<int>(S1);
	print_vector<float>(S2);
	print_vector<double>(S3);
	print_vector<char>(C);

	auto sorted_S1 = merge_sort<int>(S1);
	auto sorted_S2 = merge_sort<float>(S2);
	auto sorted_S3 = merge_sort<double>(S3);
	auto sorted_C = merge_sort<char>(C);

	cout << "���� ���Ŀ� ���� ���ĵ� ����" << endl;
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