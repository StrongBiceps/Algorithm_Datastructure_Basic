#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

enum class city : int
{
	MOSCOW,
	LONDON,
	SEOUL,
	DUBAI,
	SYDNEY
};

ostream& operator<<(ostream& os, const city c)
{
	switch (c)
	{
	case city::LONDON:
		os << "����";
		return os;
	case city::MOSCOW:
		os << "��ũ��";
		return os;
	case city::SEOUL:
		os << "����";
		return os;
	case city::DUBAI:
		os << "�ι���";
		return os;
	case city::SYDNEY:
		os << "�õ��";
	default:
		return os;
	}
}

class graph
{
private:
	vector < vector<pair<int, int>>> data;
public:
	graph(int n)
	{
		//data�� �� �濡 pair<int,int>�� ������ �� �ִ� ���͸� ���� �־���.
		data = vector<vector<pair<int, int>>>(n, vector<pair<int, int>>());
	}
	void addEdge(const city& c1, const city& c2, int dis)
	{
		auto n1 = static_cast<int>(c1);
		auto n2 = static_cast<int>(c2);
		data[n1].push_back(pair<int, int>(n2, dis));
		data[n2].push_back(pair<int, int>(n1, dis));
	}
	//remove_if�� �����͸� �ڷ� ������ �������� ���� �ƴ϶� �����Ͱ� �״�� �����ִ�. erase�� �������� �ʰ�
	//printall�Լ��� ȣ���ϰ� �Ǹ� �������� ���� �����Ͱ� ��µȴ�. ���� erase�� �ڷ� ������ �����͸� ������ �Ѵ�.
	void removeEdge(const city& c1, const city& c2)
	{
		auto n1 = static_cast<int>(c1);
		auto n2 = static_cast<int>(c2);
		auto it_remove = remove_if(data[n1].begin(), data[n1].end(), [&](const auto& pair) {
			return pair.first == n2;
			});
		data[n1].erase(it_remove, data[n1].end());

		auto it_remove2 = remove_if(data[n2].begin(), data[n2].end(), [&](const auto& pair) {
			return pair.first == n1;
			});

		data[n2].erase(it_remove2, data[n2].end());
	}
	void printall()
	{
		for (register int i = 0; i < data.size(); ++i)
		{
			for (register int j = 0; j < data[i].size(); ++j)
			{
				cout << convert_to_string(i) << ":" << convert_to_string(data[i][j].first) << " " << data[i][j].second << endl;
			}
			if (data[i].size() != 0)
				cout << data[i].size() << endl;
		}
	}
	string convert_to_string(int ifirst)
	{
		switch (ifirst)
		{
		case 0:
			return "MOSCOW";
		case 1:
			return "LONDON";
		case 2:
			return"SEOUL";
		case 3:
			return "DUBAI";
		case 4:
			return "SYDNEY";
		default:
			return"";
		}
	}
};

int main()
{
	graph g(5);
	g.addEdge(city::LONDON, city::DUBAI, 10);
	g.addEdge(city::LONDON, city::SYDNEY, 20);
	g.printall();

	cout << "after deletion" << endl;
	g.removeEdge(city::LONDON, city::DUBAI);
	g.printall();
	return 0;
}