#include <iostream>
#include <queue>
#include <vector>
using namespace std;

//중앙값을 기준으로 작은 값들은 최대 힙으로 들어가고 큰 값들은 최소 힙으로 들어간다.
//사이즈 비교를 하는 이유는 중앙값을 기준으로 두 힙의 크기가 균등하게 유지되어야 하기 때문이다.
class median
{
private:
	//최대 힙과 최소 힙을 선언한다.
	priority_queue<int> MaxHeap;
	//힙을 이루는 자료구조는 vector이고 greater<int> functor를 전달하여 최소 힙을 구성한다.
	priority_queue<int,vector<int> ,greater<int>> MinHeap;

public:
	//두 힙이 서로 크기가 다를 때
	//먼저 MinHeap의 크기가 클 경우 data가 get()보다 클 때는
	//MinHeap의 top이 get()의 리턴값이므로 일단 data가 MinHeap의 top보다는 크다.
	//따라서 MinHeap의 top을 MaxHeap으로 옮기고 data를 MinHeap으로 push하는 것이다.

	//반대로 MaxHeap이 더 클 때는 마찬가지로 MaxHeap의 top이 get()을 통해 리턴되므로
	//data가 get()보다 작을 경우 MaxHeap의 top을 MinHeap으로 옮겨주고 MaxHeap으로 data
	//를 push한다.
	void insert(int data)
	{
		//최초의 원소는 최대 힙으로 들어간다.
		if (MaxHeap.size() == 0)
		{
			MaxHeap.push(data);
			return;
		}
		//최대 힙과 최소 힙의 크기가 같은 경우
		if (MaxHeap.size() == MinHeap.size())
		{
			//중앙값보다 같거나 작다면 최대 힙에 들어간다.
			if (data <= get())
			{
				MaxHeap.push(data);
			}
			//중앙값보다 크다면 최소 힙으로 들어간다.
			else
			{
				MinHeap.push(data);
			}
			return;
		}
		//최대 힙보다 최소 힙의 크기가 큰 경우
		if (MaxHeap.size() < MinHeap.size())
		{
			//중앙값보다 클 경우에는 최소 힙의 탑을 최대 힙으로 넣는다.(최대 힙의 모든 원소보다 크므로 top으로 삽입 된다)
			//그리고 나서 최소 힙의 top을 pop하고 새 원소를 삽입한다.(top이 될지 아닌지는 새 원소의 크기에 따라 다름)
			if (data > get())
			{
				MaxHeap.push(MinHeap.top());
				MinHeap.pop();
				MinHeap.push(data);
			}
			//만약 중앙값보다 작다면 최대 힙으로 넣는다.
			else
			{
				MaxHeap.push(data);
			}
			return;
		}
		//MaxHeap이 크기가 더 큰 경우
		//중앙값보다 새 원소가 더 작은 경우
		if (data < get())
		{
			//최소 힙에 최대 힙의 top을 넣는다.
			//그리고 최대 힙의 top을 pop한다.
			//새 원소는 최대 힙으로 들어간다.
			MinHeap.push(MaxHeap.top());
			MaxHeap.pop();
			MaxHeap.push(data);
		}
		//MaxHeap의 크기가 더 크고 중앙값보다 새 원소가 큰 경우
		//최소 힙에다가 넣는다.
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
		//서로 크기가 큰 경우는 힙의 top이 중앙값이다.
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
	cout << "1 삽입 후 중앙값" << med.get() << endl;

	med.insert(5);
	cout << "5 삽입 후 중앙값" << med.get() << endl;

	med.insert(2);
	cout << "2 삽입 후 중앙값" << med.get() << endl;

	med.insert(10);
	cout << "10 삽입 후 중앙값" << med.get() << endl;

	med.insert(40);
	cout << "40 삽입 후 중앙값" << med.get() << endl;

	//Max Heap - 2(top),1
	//Min Heap - 5(top),10,40
	//최종 상태인 위에서 중앙값은 MinHeap이 MaxHeap보다 크므로 MinHeap의 Top이 나온다.
	// 1 2 5 10 40
	//	  (m)
	return 0;
}
