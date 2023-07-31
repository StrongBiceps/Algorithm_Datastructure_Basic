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
			//�迭�� �� á�� �� �迭�� ������ ���Ұ� ���ο� ���Һ��� ũ�ٸ� ���� �ʴ´�.
			if (newscore <= entries[Maxentries - 1].Getscore())
				return;
			else
			{
				//�׸��� ���� �� �� �ٷ� �� ���Һ��� ���� ������ �����Ѵ�.
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
		//�迭�� �� ���� �ʾҴٸ� �ϴ� �迭�� ũ�⸦ �ϳ� �ø���.
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
	���⼭ �� �ڵ尡 �ȵǴ� ������ GameEntry& e�� const�� ����Ǿ� �ִ�. �� e�� ���θ� ������ �� ����.
	������ Getscore���� ��ȯ�ϴ� ���� ���� ���� (cosnt�� ���� ���� �� �����ϰ� �ִ� �������� ���� ������ �� �ִ�)
	�̴�. ���� const���� e�� ������ newscore�� �־����Ƿ� newscore�� ���� �ٲ�� e�� ���� �ٲ�� �ȴ�.
	���� ��Ī�� �ȵǴ� ���̴�. �׷��� ������ �����̴�. const�� ���ְų� Getscore���� ���� ���� ��ȯ�� �ϸ� �ذ�ȴ�.*/
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