#include <iostream>

template<typename T>
class Single_list
{
private:
	class Single_list_node
	{
	public:
		T* Data;
		Single_list_node* next;
		~Single_list_node()
		{
			delete Data;
		}
	};
public:
	using node = Single_list_node;
	using node_ptr = node*;
private:
	node_ptr head;
	size_t n;
public:
	void push_front(T val)
	{
		auto new_node = new node{ new T(val), NULL };

		if (head != NULL)
		{
			new_node->next = head;
		}
		head = new_node;

		++n;
	}
	void pop_front()
	{
		//first�� �����ϴ� ������ ������ head�� first�� ������ ���� head�� �ű� �� 
		//������ head�� ��ü�Ϸ��� ������. head�� ���� �ٷ�� �Ǹ� head=head->next;
		//�� �س��� delete head�ϸ� �ǹ̰� ���� �����̴�.
		auto first = head;
		if (head)
		{
			head = head->next;
			delete first;
		}
		--n;
	}

	class Single_list_it
	{
	private:
		node_ptr ptr;
	public:
		Single_list_it(node_ptr p) :ptr(p) {}
		T& operator*()
		{
			return *(ptr->Data);
		}
		node_ptr& Get()
		{
			return ptr;
		}
		Single_list_it& operator++() //���� ����
		{
			ptr = ptr->next;
			return *this;
		}
		Single_list_it operator++(int)//���� ����
		{
			Single_list_it it_temp = *this;
			++(*this);
			return it_temp;
		}
		friend bool operator==(const Single_list_it& it1, const Single_list_it& it2)
		{
			return it1.ptr == it2.ptr;
		}
		friend bool operator!=(const Single_list_it& it1, const Single_list_it& it2)
		{
			return it1.ptr != it2.ptr;
		}
	};

	Single_list_it begin()
	{
		return Single_list_it(head);
	}
	Single_list_it begin() const
	{
		return Single_list_it(head);
	}
	Single_list_it end()
	{
		return Single_list_it(NULL);
	}
	Single_list_it end() const
	{
		return Single_list_it(NULL);
	}

	Single_list()
	{
		head = NULL;
		n = 0;
	}
	Single_list(const Single_list& other) :Single_list()
	{
		if (other.head)
		{
			head = new node{ NULL, NULL };

			auto cur = head;
			auto it = other.begin();
			while (true)
			{
				//head�� �ٲ��� �ʰ� ��� �ڷ� �����Ѵ�.(push_back�� ���� ����)
				cur->Data = new T(*it);
				++n;
				/*
				auto temp = it;
				++temp;
				if (temp == other.end())
				{
					break;
				}
				cur->next = new node{ 0,NULL };
				cur = cur->next;
				it = temp;*/
				++it;
				if (it == other.end())
				{
					break;
				}
				cur->next = new node{ NULL,NULL };
				cur = cur->next;
			}
		}
	}
	Single_list(const std::initializer_list<int>& ilist) :Single_list()
	{
		//rebegin()�� rend()�� �ӽ� ��ü�� &&�� ����ϰų� auto�� ����Ѵ�.
		//�Ϲ� ������ ����� �� ����.
		for (auto&& it = rbegin(ilist); it != rend(ilist); ++it)
		{
			push_front(*it);
		}
	}
	Single_list(Single_list&& other) noexcept :Single_list()
	{
		if (other.head != NULL)
		{
			head = other.head;
			other.head = NULL;
		}
	}
	~Single_list()
	{
		if (head != NULL)
		{
			while (n != 0)
			{
				pop_front();
			}
		}
		delete head;
	}
	void printall()
	{
		for (auto& i : *this)
		{
			std::cout << i << " " << std::endl;
		}
	}
};

int main()
{
	std::cout << "initializer list result" << std::endl;
	Single_list<int> s1({ 1,2,3 });
	s1.printall();

	std::cout << std::endl;

	std::cout << "move semantics result" << std::endl;
	Single_list<int>* dynamic_temp = new Single_list<int>({ 10,20,30 });
	Single_list<int> RS(std::move(*dynamic_temp));
	delete dynamic_temp;
	RS.printall();

	std::cout << "copy constructor result" << std::endl;
	Single_list<int> Copy_temp(s1);
	Copy_temp.printall();

	std::cout << "other function result" << std::endl;

	Single_list<int> other;
	other.push_front(100);
	other.push_front(200);
	other.push_front(300);
	other.pop_front();
	other.printall();
	return 0;
}