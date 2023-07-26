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
		//������ n���� ���Ҹ� -1�� �ʱ�ȭ�Ѵ�.
		data = vector<int>(n, -1);
	}
	void insert(uint value)
	{
		int n = data.size();
		//modulo operation�� �̿��Ͽ� �ؽ� ���̺��� ����.
		data[value % n] = value;
		cout << value << "�� �����߽��ϴ�." << endl;
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
			cout << value << "�� �����߽��ϴ�." << endl;
		}
	}
};

int main()
{
	hash_map map(7);

	//��� ����� ����ϴ� ���� �Լ��� �����Ѵ�.
	auto print = [&](int value) {
		if (map.find(value))
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
	print(25);

	map.insert(100);
	print(100);
	print(2);

	map.erase(25);
	print(25);
	return 0;
}