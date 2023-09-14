#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//push_heap에서 비교자는 > 를 사용하면 최소 힙이 되고 
//< 를 사용하면 최대 힙이 된다.
class MergeList
{
private:
	class node
	{
	public:
		int data;
		int listposition;
		int dataposition;
	};
public:
	MergeList() = default;
	vector<int> merge(const vector<vector<int>>& input);
};

//리스트가 정렬되어 있지 않다고 생각해보자.
//그리고 각 리스트의 index 0 의 원소들을 뽑아서 heap을 구성한다.
//그러면 그 중에서 가장 작은 값이 result의 맨 뒤로 들어가게 된다.
//하지만 그 값은 리스트중에서 가장 작은 값이 아니므로 남은 원소들 중에
//해당 리스트보다 작은 원소가 존재한다. 따라서 더 작은 원소가 앞에 있게 되는
//정렬되지 못한 상태가 되는 것이다. 따라서 각 리스트를 정렬한 상태로 병합을 
//진행해야 한다.
vector<int> MergeList::merge(const vector<vector<int>>& input)
{
	//push_heap에서 사용할 functor를 람다 함수로 대체
	//외부에서 사용하는 변수가 없기 때문에 캡쳐는 그대로 둔다.
	auto comparator = [](const node& left, const node& right) {
		if (left.data == right.data)
		{
			//값이 같다면 vector<vector<int>> input에서 첫 번째 인덱스가 작은 값을 작다고 취급한다.
			// input[0][2] input[1][1]의 data가 같다고 한다면 input[0][2]가 작은 값으로 취급된다.
			//여기서 다루는 자료구조는 최소 힙이다. 따라서 listposition이 작은 값이 힙의 위쪽으로 향한다.
			//즉 data가 가장 작은 값은 최소 힙의 root에 위치하고 data가 같다면 그 중 listposition이 작은 값을 
			//위로 위치시킨다.
			return left.listposition > right.listposition;
		}
		return left.data > right.data;
	};

	//노드를 자료형으로 갖는 벡터 정의
	vector<node> heap;

	for (register int i = 0; i < input.size(); ++i)
	{
		//각 리스트에서 최소 원소들을 heap에 push
		//각 리스트에서 최소 원소들은 리스트 포지션은 i가 되고 dataposition은 
		//각 리스트에서 최소이므로 index 0에 위치한다.
		heap.push_back({ input[i][0],i,0 });
		//힙을 최소 힙으로 만들기 위해 push_heap으로 vector를 정렬
		push_heap(heap.begin(), heap.end(),comparator);
	}
	cout << heap.front().data << endl;
	vector<int> result;
	while (!heap.empty())
	{
		//heap의 최소 원소를 heap의 가장 마지막 원소와 교체
		pop_heap(heap.begin(), heap.end(), comparator);
		//따라서 heap의 마지막 노드가 가장 작은 값이 된다.
		auto min = heap.back();
		//마지막 노드를 제거한다.
		heap.pop_back();

		//추출한 값들을 vector의 뒤로 넣는다. 따라서 가장 작은 값이 vector의 맨 뒤에 존재한다.
		result.push_back(min.data);
		int nextIndex = min.dataposition + 1;
		//nextIndex는 min이 속한 list에서 min 다음 인덱스를 의미한다.
		//또한 해당 index가 out of range인지 확인하기 위해 해당 리스트의 크기와 비교한다.
		if (nextIndex < input[min.listposition].size())
		{
			heap.push_back({ input[min.listposition][nextIndex],min.listposition,nextIndex });
			//그 다음 인덱스의 원소를 힙에 추가했으므로 힙을 다시 정렬한다.
			push_heap(heap.begin(), heap.end(), comparator);

			//모든 작업이 끝나고 다음 반복문으로 넘어가게 되면 heap에서 가장 작은 원소가 다시 추출된다.
			//하지만 그 원소는 다른 listposition의 원소이므로 매 반복마다 같은 리스트에서 추출될 수도 있지만
			//각 리스트를 번갈아가며 원소를 추출하게 된다. 반복이 진행되다 보면 nextIndex가 size를 넘는 순간이
			//올 것이다. 그러면 해당 리스트에는 더 이상 추출할 원소가 없는 것이다. 그러면서 heap에 push되는 원소들이
			//줄어들면서 heap이 비어있을 때 까지 반복하다 종료한다.
		}
	}
	//병합이 끝난 결과를 저장한 vector를 리턴한다.
	return result;
}

int main()
{
	vector<int> v1 = { 1,3,8,15,105 };
	vector<int> v2 = { 2,3,10,11,16,20,25 };
	vector<int> v3 = { -2,100,1000 };
	vector<int> v4 = { -1,0,14,18 };

	MergeList M;
	auto result = M.merge({ v1,v2,v3,v4 });
	
	for (const auto& i : result)
	{
		cout << i << " ";
	}
	return 0;
}
