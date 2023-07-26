#include <iostream>
#include <vector>
using namespace std;

using uint = unsigned int;

class hash_map
{
private:
	vector<int> data;
public:
	hash_map(size_t n)
	{
		//벡터의 n개의 원소를 -1로 초기화한다.
		data = vector<int>(n, -1);
	}
	void insert(uint value)
	{
		int n = data.size();
		//modulo operation을 이용하여 해시 테이블을 구성.
		data[value % n] = value;
		cout << value << "를 삽입했습니다." << endl;
	}
	bool find(uint value)
	{
		int n = data.size();
		return (data[value % n] == value);
	}
	void erase(uint value)
	{
		int n = data.size();
		if (data[value % n] == value)
		{
			data[value % n] = -1;
			cout << value << "를 삭제했습니다." << endl;
		}
	}
};

int main()
{
	hash_map map(7);

	//룩업 결과를 출력하는 람다 함수를 정의한다.
	auto print = [&](int value) {
		if (map.find(value))
		{
			cout << "해시 맵에서" << value << "를 찾았습니다." << endl;
		}
		else
		{
			cout << "해시 맵에서" << value << "를 찾지 못했습니다." << endl;
		}
	};

	map.insert(2);
	map.insert(25);
	map.insert(10);
	print(25);

	map.insert(100);
	print(100);
	print(2);

	map.erase(25);
	print(25);
	return 0;
}