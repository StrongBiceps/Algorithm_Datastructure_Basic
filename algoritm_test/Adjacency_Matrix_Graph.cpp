#include <iostream>
#include <vector>
using namespace std;

enum class city :int
{
	MOSCOW,
	LONDON,
	SEOUL,
	SEATTLE,
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
	case city::SEATTLE:
		os << "�þ�Ʋ";
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
	vector<vector<int>> data;
public:
	graph(int n)
	{
		//vector<int>�� ������ �� �ִ� ���� n���� �̸� Ȯ���Ѵ�.
		data.reserve(n);
		//data�� �� ������ ����� n���� ���Ҹ� ������ �� �ִ� vector�̴�.
		vector<int> row(n);
		fill(row.begin(), row.end(), -1);

		for (register int i = 0; i < n; ++i)
		{
			//data�� �� ������ ���͸� �־����Ƿ� n*n����� �ϼ��ȴ�.
			data.push_back(row);
		}
	}
	void addEdge(const city& c1, const city& c2, const int dis)
	{
		auto n1 = static_cast<int>(c1);
		auto n2 = static_cast<int>(c2);
		data[n1][n2] = dis;
		data[n2][n1] = dis;
	}
	void removeEdge(const city& c1, const city& c2)
	{
		auto n1 = static_cast<int>(c1);
		auto n2 = static_cast<int>(c2);
		data[n1][n2] = -1;
		data[n2][n1] = -1;
	}
};

int main()
{
	//6*6 ���� ����� ����
	graph g(6);

	//city::LONDON�� ����̱� ������ addEdge�Լ����� const city& c1 ������ ���� �� �ִ�.
	//���� ����� R value �����ε� �� �� �ֱ� ������ const city&& c1�� �����ϴ�.
	g.addEdge(city::LONDON, city::MOSCOW, 2500);
	g.addEdge(city::LONDON, city::SEOUL, 9000);
	g.addEdge(city::LONDON, city::SEATTLE, 10000);

	return 0;
}