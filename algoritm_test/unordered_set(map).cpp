#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

//unordered_set 출력 함수
void print(const unordered_set<int>& container)
{
	for (const auto& element : container)
	{
		cout << element << " ";
	}
	cout << endl;
}
void print(const unordered_map<int,int>& container)
{
	for (const auto& element : container)
	{
		cout << element.first << " -> "<<element.second<<" ";
	}
	cout << endl;
}

void find(const unordered_set<int>& container, const int element)
{
	if (container.find(element) == container.end())
	{
		cout<<element << "검색 실패" << endl;
	}
	else
	{
		cout << element << "검색 성공" << endl;
	}
}

void find(const unordered_map<int, int>& container, const int element)
{
	//element가 key(it->first)이고 it->second가 해시 값이다.
	auto it = container.find(element);
	if (it == container.end())
	{
		cout << element << "검색: 실패" << endl;
	}
	else
	{
		cout << element << "검색: 성공, 값 = " << it->second << endl;
	}
}

int main()
{
	cout << "*** std::unordered_set 예제 ***" << endl;
	unordered_set<int> set1 = { 1,2,3,4,5 };

	cout << "set1 초깃값: ";
	print(set1);

	set1.insert(2);
	cout << "2 삽입: ";
	print(set1);

	set1.insert(10);
	set1.insert(300);
	cout << "10,300 삽입: ";
	print(set1);

	find(set1, 4);
	find(set1, 100);

	set1.erase(2);
	cout << "2 삭제: ";
	print(set1);

	find(set1, 2);

	cout << "*** std::unordered_map 예제 ***" << endl;
	unordered_map<int, int> squareMap;

	squareMap.insert({ 2,4 });
	//unordered_map의 []연산자는 참조를 반환하며, 만약 해당 키가 없다면 해당 위치에 기본값( 0 )을 추가하여 반환
	squareMap[3] = 9;
	cout << "2,3의 제곱 삽입: ";
	print(squareMap);

	squareMap[20] = 400;
	squareMap[30] = 900;
	cout << "20,30의 제곱 삽입";
	print(squareMap);

	find(squareMap, 10);
	find(squareMap, 20);

	cout << "squareMap[3] = " << squareMap[3] << endl;
	//square[100]은 없으므로 기본값인 0을 추가하여 반환한다.
	cout << "suqareMap[100] = " << squareMap[100] << endl;
	print(squareMap);

	return 0;
}