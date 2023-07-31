#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//push_heap���� ���ڴ� > �� ����ϸ� �ּ� ���� �ǰ� 
//< �� ����ϸ� �ִ� ���� �ȴ�.
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

//����Ʈ�� ���ĵǾ� ���� �ʴٰ� �����غ���.
//�׸��� �� ����Ʈ�� index 0 �� ���ҵ��� �̾Ƽ� heap�� �����Ѵ�.
//�׷��� �� �߿��� ���� ���� ���� result�� �� �ڷ� ���� �ȴ�.
//������ �� ���� ����Ʈ�߿��� ���� ���� ���� �ƴϹǷ� ���� ���ҵ� �߿�
//�ش� ����Ʈ���� ���� ���Ұ� �����Ѵ�. ���� �� ���� ���Ұ� �տ� �ְ� �Ǵ�
//���ĵ��� ���� ���°� �Ǵ� ���̴�. ���� �� ����Ʈ�� ������ ���·� ������ 
//�����ؾ� �Ѵ�.
vector<int> MergeList::merge(const vector<vector<int>>& input)
{
	//push_heap���� ����� functor�� ���� �Լ��� ��ü
	//�ܺο��� ����ϴ� ������ ���� ������ ĸ�Ĵ� �״�� �д�.
	auto comparator = [](const node& left, const node& right) {
		if (left.data == right.data)
		{
			//���� ���ٸ� vector<vector<int>> input���� ù ��° �ε����� ���� ���� �۴ٰ� ����Ѵ�.
			// input[0][2] input[1][1]�� data�� ���ٰ� �Ѵٸ� input[0][2]�� ���� ������ ��޵ȴ�.
			//���⼭ �ٷ�� �ڷᱸ���� �ּ� ���̴�. ���� listposition�� ���� ���� ���� �������� ���Ѵ�.
			//�� data�� ���� ���� ���� �ּ� ���� root�� ��ġ�ϰ� data�� ���ٸ� �� �� listposition�� ���� ���� 
			//���� ��ġ��Ų��.
			return left.listposition > right.listposition;
		}
		return left.data < right.data;
	};

	//��带 �ڷ������� ���� ���� ����
	vector<node> heap;

	for (register int i = 0; i < input.size(); ++i)
	{
		//�� ����Ʈ���� �ּ� ���ҵ��� heap�� push
		//�� ����Ʈ���� �ּ� ���ҵ��� ����Ʈ �������� i�� �ǰ� dataposition�� 
		//�� ����Ʈ���� �ּ��̹Ƿ� index 0�� ��ġ�Ѵ�.
		heap.push_back({ input[i][0],i,0 });
		//���� �ּ� ������ ����� ���� push_heap���� vector�� ����
		push_heap(heap.begin(), heap.end(),comparator);
	}
	cout << heap.front().data << endl;
	vector<int> result;
	while (!heap.empty())
	{
		//heap�� �ּ� ���Ҹ� heap�� ���� ������ ���ҿ� ��ü
		pop_heap(heap.begin(), heap.end(), comparator);
		//���� heap�� ������ ��尡 ���� ���� ���� �ȴ�.
		auto min = heap.back();
		//������ ��带 �����Ѵ�.
		heap.pop_back();

		//������ ������ vector�� �ڷ� �ִ´�. ���� ���� ���� ���� vector�� �� �ڿ� �����Ѵ�.
		result.push_back(min.data);
		int nextIndex = min.dataposition + 1;
		//nextIndex�� min�� ���� list���� min ���� �ε����� �ǹ��Ѵ�.
		//���� �ش� index�� out of range���� Ȯ���ϱ� ���� �ش� ����Ʈ�� ũ��� ���Ѵ�.
		if (nextIndex < input[min.listposition].size())
		{
			heap.push_back({ input[min.listposition][nextIndex],min.listposition,nextIndex });
			//�� ���� �ε����� ���Ҹ� ���� �߰������Ƿ� ���� �ٽ� �����Ѵ�.
			push_heap(heap.begin(), heap.end(), comparator);

			//��� �۾��� ������ ���� �ݺ������� �Ѿ�� �Ǹ� heap���� ���� ���� ���Ұ� �ٽ� ����ȴ�.
			//������ �� ���Ҵ� �ٸ� listposition�� �����̹Ƿ� �� �ݺ����� ���� ����Ʈ���� ����� ���� ������
			//�� ����Ʈ�� �����ư��� ���Ҹ� �����ϰ� �ȴ�. �ݺ��� ����Ǵ� ���� nextIndex�� size�� �Ѵ� ������
			//�� ���̴�. �׷��� �ش� ����Ʈ���� �� �̻� ������ ���Ұ� ���� ���̴�. �׷��鼭 heap�� push�Ǵ� ���ҵ���
			//�پ��鼭 heap�� ������� �� ���� �ݺ��ϴ� �����Ѵ�.
		}
	}
	//������ ���� ����� ������ vector�� �����Ѵ�.
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
