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
		//������ ũ�� ������ ������尡 �߻����� �ʵ��� �̸� ũ�⸦ �����Ѵ�.
		data.resize(n);
	}
	void insert(uint value)
	{
		//�����Ϸ��� ��� �޽��� - size_t���� int�� ��ȯ�ϸ鼭 �����Ͱ� �սǵ� �� �ֽ��ϴ�.
		//���� int�� ĳ�����Ѵ�.
		int n = static_cast<int>(data.size());
		data[value % n].push_back(value);
		cout << value << "�� �����߽��ϴ�." << endl;
	}
	//std::find�� ���ؼ� value�� ã�ƾ� �ϹǷ� modulo �ڵ庸�ٴ� ��� �۾��� ������.
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
			cout << value << "�� �����߽��ϴ�." << endl;
		}
	}
};

int main()
{
	hash_map map(7);

	//����� ���� ���� �Լ�
	auto print = [&](int value) {
		if (map.find_hash(value))
		{
			cout << "�ؽ� �ʿ���" << value << "�� ã�ҽ��ϴ�." << endl;
		}
		else
		{
			cout << "�ؽ� �ʿ���" << value << "�� ã�� ���߽��ϴ�." << endl;
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