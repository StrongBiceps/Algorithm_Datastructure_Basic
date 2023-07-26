#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

using uint = unsigned int;

class hash_map
{
private:
	vector<list<int>> data;
public:
	hash_map(size_t n)
	{
		//벡터의 크기 때문에 오버헤드가 발생하지 않도록 미리 크기를 조절한다.
		data.resize(n);
	}
	void insert(uint value)
	{
		//컴파일러의 경고 메시지 - size_t에서 int로 변환하면서 데이터가 손실될 수 있습니다.
		//따라서 int로 캐스팅한다.
		int n = static_cast<int>(data.size());
		data[value % n].push_back(value);
		cout << value << "를 삽입했습니다." << endl;
	}
	//std::find를 통해서 value를 찾아야 하므로 modulo 코드보다는 룩업 작업이 느리다.
	bool find_hash(uint value)
	{
		int n = static_cast<int>(data.size());
		auto& entries = data[value % n];
		return find(entries.begin(), entries.end(), value) != entries.end();
	}
	void erase(uint value)
	{
		int n = static_cast<int>(data.size());
		auto& entries = data[value % n];
		auto iter = find(entries.begin(), entries.end(), value);

		if (iter != entries.end())
		{
			entries.erase(iter);
			cout << value << "를 삭제했습니다." << endl;
		}
	}
};

int main()
{
	hash_map map(7);

	//출력을 위한 람다 함수
	auto print = [&](int value) {
		if (map.find_hash(value))
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

	map.insert(100);
	map.insert(55);
	
	print(100);
	print(2);

	map.erase(2);
	print(2);
	return 0;
}