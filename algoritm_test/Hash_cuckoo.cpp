#include <iostream>
#include <vector>
using namespace std;

class hash_map
{
private:
	vector<int> data1;
	vector<int> data2;
	int size;

	void insert_impl(int key, int cnt, int table)
	{
		if (cnt >= size)
		{
			cout << key << "삽입 시 순환 발생! 재해싱이 필요합니다." << endl;
			return; 
		}

		if (table == 1)
		{
			int hash = hash1(key);
			if (data1[hash] == -1)
			{
				cout << table << "번 테이블에" << key << " 삽입" << endl;
				data1[hash] = key;
			}
			else
			{
				int old = data1[hash];
				data1[hash] = key;
				cout << table << "번 테이블에" << key << "삽입: 기존의" << old << "이동 -> ";
				insert_impl(old, cnt + 1, 2);
			}
		}
		else
		{
			int hash = hash2(key);
			if (data2[hash] == -1)
			{
				cout << table << "번 테이블에" << key << " 삽입" << endl;
				data2[hash] = key;
			}
			else
			{
				int old = data2[hash];
				data2[hash] = key;
				cout << table << "번 테이블에" << key << "삽입: 기존의" << old << "이동 -> ";
				insert_impl(old, cnt + 1, 1);
			}
		}
	}
public:
	hash_map(int n) :size(n)
	{
		data1 = vector<int>(size, -1);
		data2 = vector<int>(size, -1);
	}
	int hash1(int key) const
	{
		return key % size;
	}
	int hash2(int key) const
	{
		return (key / size) % size;
	}
	vector<int>::iterator lookup(int key)
	{
		auto hash_value1 = hash1(key);

		if (data1[hash_value1] == key)
		{
			cout << "1번 테이블에서 " << key << "를 찾았습니다." << endl;
			return data1.begin() + hash_value1;
		}

		auto hash_value2 = hash2(key);
	
		if (data2[hash_value2] == key)
		{
			cout << "2번 테이블에서 " << key << "를 찾았습니다." << endl;
			return data2.begin() + hash_value2;
		}

		//값을 찾지 못했을 때는 end()를 반환한다.
		cout << "값을 찾지 못했습니다." << endl;
		return data2.end();
	}
	void erase(int key)
	{
		auto position = lookup(key);
		//값을 찾았다면 position은 end()가 아니다.
		if (position != data2.end())
		{
			*position = -1;
			cout << key << "에 해당하는 원소를 삭제했습니다." << endl;
		}
		else
		{
			cout << key << "키를 찾지 못했습니다." << endl;
		}
	}
	//삽입 인터페이스
	//내부 구현은 impl메소드로 캡슐화했다.
	//삽입 함수는 재귀적으로 동작해야 하기 때문에 실제 삽입 구현 함수를 따로 만든다.
	//삽입 함수에서는 순환 여부를 검사해야 한다. 그러나 방문한 위치의 모든 값을
	//기억하는 것은 부담이 클 수 있다. 그러므로 여기서는 단순히 재귀 호출 횟수가 몇 회
	//이상이면 순환으로 간주한다. 이때 재귀 호출 횟수는 해시 테이블 크기와 같게 설정할 것이며,
	//이러한 방식의 구현은 좋은 성능을 보여준다.
	void insert(int key)
	{
		insert_impl(key, 0, 1);
	}
	//모든 데이터를 출력하는 print메소드를 구현한다.
	void print()
	{
		cout << "Index: ";
		for (register int i = 0; i < size; ++i)
		{
			cout << i << '\t';
		}
		cout << endl;

		cout << "Data1: ";
		for (const auto& i : data1)
		{
			cout << i << '\t';
		}
		cout << endl;

		cout << "Data2: ";
		for (const auto& i : data2)
		{
			cout << i << '\t';
		}
		cout << endl;
	}
};
int main()
{
	hash_map map(7);

	map.print();
	cout << endl;

	map.insert(10);
	map.insert(20);
	map.insert(30);
	cout << endl;

	map.insert(104);
	map.insert(2);
	map.insert(70);
	map.insert(9);
	map.insert(90);
	map.insert(2);
	map.insert(7);
	cout << endl;

	map.print();
	cout << endl;

	map.insert(14); //순환 발생
	return 0;
}