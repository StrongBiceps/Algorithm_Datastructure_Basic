#include<iostream>
#include<vector>
using namespace std;

class GameEntry
{
private:
	string name;
	int score;
public:
	GameEntry(const string& n = "", int s = 0) :name(n), score(s) {}
	string& Getname()
	{
		return name;
	}
	int& Getscore()
	{
		return score;
	}
};

class Scores
{
private:
	int Maxentries;
	int Numentries;
	GameEntry* entries;
public:
	Scores(int MaxEnt = 3)
	{
		Maxentries = MaxEnt;
		entries = new GameEntry[Maxentries];
		Numentries = 0;
	}
	~Scores()
	{
		delete[] entries;
	}
	void Add(GameEntry& e)
	{
		int newscore = e.Getscore();
		if (Numentries == Maxentries)
		{
			//배열이 꽉 찼을 때 배열의 마지막 원소가 새로운 원소보다 크다면 넣지 않는다.
			if (newscore <= entries[Maxentries - 1].Getscore())
				return;
			else
			{
				//그리고 나서 맨 뒤 바로 앞 원소부터 삽입 정렬을 수행한다.
				int i = Maxentries - 2;
				while (i >= 0 && newscore > entries[i].Getscore())
				{
					entries[i + 1] = entries[i];
					--i;
				}
				entries[i + 1] = e;
				return;
			}
		}
		//배열이 꽉 차지 않았다면 일단 배열의 크기를 하나 늘린다.
		else
			++Numentries;

		int i = Numentries - 2;

		while (i >= 0 && newscore > entries[i].Getscore())
		{
			entries[i + 1] = entries[i];
			--i;
		}
		entries[i + 1] = e;
	}
	GameEntry remove(int i)
	{
		if ((i < 0) || (i >= Numentries))
		{
			cout << "index out of bounds" << endl;
		}
		GameEntry e = entries[i];
		for (register int j = i + 1; j < Numentries; ++j)
		{
			entries[j - 1] = entries[j];
		}
		--Numentries;
		return e;
	}
	void printALL()
	{
		for (register int i = 0; i < Numentries; ++i)
		{
			cout << entries[i].Getscore() << " ";
		}
	}
	/*
	void Add(const GameEntry& e)
	{
		int newscore = e.Getscore();
	}
	여기서 이 코드가 안되는 이유는 GameEntry& e는 const로 선언되어 있다. 즉 e의 내부를 변경할 수 없다.
	하지만 Getscore에서 반환하는 값은 가변 참조 (cosnt가 붙지 않은 즉 참조하고 있는 데이터의 값을 변경할 수 있는)
	이다. 따라서 const형인 e의 참조를 newscore에 넣었으므로 newscore가 값이 바뀌면 e의 값도 바뀌게 된다.
	따라서 매칭이 안되는 것이다. 그래서 금지된 문법이다. const를 없애거나 Getscore에서 값에 의한 반환을 하면 해결된다.*/
};

void main()
{
	Scores STemp;
	GameEntry GTemp("kim", 100);
	GameEntry GTemp2("Lee", 200);
	GameEntry GTemp3("Park", 300);
	GameEntry GTemp4("Song", 400);

	STemp.Add(GTemp);
	STemp.Add(GTemp2);
	STemp.Add(GTemp3);
	STemp.printALL();
	cout << endl;
	STemp.Add(GTemp4);
	STemp.printALL();

}