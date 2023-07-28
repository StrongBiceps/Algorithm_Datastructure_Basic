#include <iostream>
#include <queue>
#include <vector>
using namespace std;

//�߾Ӱ��� �������� ���� ������ �ִ� ������ ���� ū ������ �ּ� ������ ����.
//������ �񱳸� �ϴ� ������ �߾Ӱ��� �������� �� ���� ũ�Ⱑ �յ��ϰ� �����Ǿ�� �ϱ� �����̴�.
class median
{
private:
	//�ִ� ���� �ּ� ���� �����Ѵ�.
	priority_queue<int> MaxHeap;
	//���� �̷�� �ڷᱸ���� vector�̰� greater<int> functor�� �����Ͽ� �ּ� ���� �����Ѵ�.
	priority_queue<int,vector<int> ,greater<int>> MinHeap;

public:
	void insert(int data)
	{
		//������ ���Ҵ� �ִ� ������ ����.
		if (MaxHeap.size() == 0)
		{
			MaxHeap.push(data);
			return;
		}
		//�ִ� ���� �ּ� ���� ũ�Ⱑ ���� ���
		if (MaxHeap.size() == MinHeap.size())
		{
			//�߾Ӱ����� ���ų� �۴ٸ� �ִ� ���� ����.
			if (data <= get())
			{
				MaxHeap.push(data);
			}
			//�߾Ӱ����� ũ�ٸ� �ּ� ������ ����.
			else
			{
				MinHeap.push(data);
			}
			return;
		}
		//�ִ� ������ �ּ� ���� ũ�Ⱑ ū ���
		if (MaxHeap.size() < MinHeap.size())
		{
			//�߾Ӱ����� Ŭ ��쿡�� �ּ� ���� ž�� �ִ� ������ �ִ´�.(�ִ� ���� ��� ���Һ��� ũ�Ƿ� top���� ���� �ȴ�)
			//�׸��� ���� �ּ� ���� top�� pop�ϰ� �� ���Ҹ� �����Ѵ�.(top�� ���� �ƴ����� �� ������ ũ�⿡ ���� �ٸ�)
			if (data > get())
			{
				MaxHeap.push(MinHeap.top());
				MinHeap.pop();
				MinHeap.push(data);
			}
			//���� �߾Ӱ����� �۴ٸ� �ִ� ������ �ִ´�.
			else
			{
				MaxHeap.push(data);
			}
			return;
		}
		//MaxHeap�� ũ�Ⱑ �� ū ���
		//�߾Ӱ����� �� ���Ұ� �� ���� ���
		if (data < get())
		{
			//�ּ� ���� �ִ� ���� top�� �ִ´�.
			//�׸��� �ִ� ���� top�� pop�Ѵ�.
			//�� ���Ҵ� �ִ� ������ ����.
			MinHeap.push(MaxHeap.top());
			MaxHeap.pop();
			MaxHeap.push(data);
		}
		//MaxHeap�� ũ�Ⱑ �� ũ�� �߾Ӱ����� �� ���Ұ� ū ���
		//�ּ� �����ٰ� �ִ´�.
		else
		{
			MinHeap.push(data);
		}
		return;
	}
	double get()
	{
		if (MaxHeap.size() == MinHeap.size())
		{
			return (MaxHeap.top() + MinHeap.top()) / 2.0;
		}
		//���� ũ�Ⱑ ū ���� ���� top�� �߾Ӱ��̴�.
		if (MaxHeap.size() < MinHeap.size())
		{
			return MinHeap.top();
		}
		return MaxHeap.top();
	}
};

int main()
{
	median med;

	med.insert(1);
	cout << "1 ���� �� �߾Ӱ�" << med.get() << endl;

	med.insert(5);
	cout << "5 ���� �� �߾Ӱ�" << med.get() << endl;

	med.insert(2);
	cout << "2 ���� �� �߾Ӱ�" << med.get() << endl;

	med.insert(10);
	cout << "10 ���� �� �߾Ӱ�" << med.get() << endl;

	med.insert(40);
	cout << "40 ���� �� �߾Ӱ�" << med.get() << endl;

	//Max Heap - 2(top),1
	//Min Heap - 5(top),10,40
	//���� ������ ������ �߾Ӱ��� MinHeap�� MaxHeap���� ũ�Ƿ� MinHeap�� Top�� ���´�.
	// 1 2 5 10 40
	//	  (m)
	return 0;
}