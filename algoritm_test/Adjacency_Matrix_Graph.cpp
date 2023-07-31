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
		os << "런던";
		return os;
	case city::MOSCOW:
		os << "모스크바";
		return os;
	case city::SEOUL:
		os << "서울";
		return os;
	case city::SEATTLE:
		os << "시애틀";
		return os;
	case city::DUBAI:
		os << "두바이";
		return os;
	case city::SYDNEY:
		os << "시드니";
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
		//vector<int>를 저장할 수 있는 공간 n개를 미리 확보한다.
		data.reserve(n);
		//data의 각 공간에 저장될 n개의 원소를 저장할 수 있는 vector이다.
		vector<int> row(n);
		fill(row.begin(), row.end(), -1);

		for (register int i = 0; i < n; ++i)
		{
			//data의 각 공간에 벡터를 넣었으므로 n*n행렬이 완성된다.
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
	//6*6 인접 행렬의 생성
	graph g(6);

	//city::LONDON은 상수이기 때문에 addEdge함수에서 const city& c1 참조로 받을 수 있다.
	//또한 상수는 R value 참조로도 들어갈 수 있기 때문에 const city&& c1도 가능하다.
	g.addEdge(city::LONDON, city::MOSCOW, 2500);
	g.addEdge(city::LONDON, city::SEOUL, 9000);
	g.addEdge(city::LONDON, city::SEATTLE, 10000);

	return 0;
}