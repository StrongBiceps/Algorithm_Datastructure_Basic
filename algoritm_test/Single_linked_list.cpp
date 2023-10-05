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
		//first를 선언하는 이유는 원래의 head를 first에 저장해 놓고 head를 옮긴 후 
		//원래의 head를 해체하려는 이유다. head를 직접 다루게 되면 head=head->next;
		//를 해놓고 delete head하면 의미가 없기 때문이다.
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
		Single_list_it& operator++() //선행 증가
		{
			ptr = ptr->next;
			return *this;
		}
		Single_list_it operator++(int)//후행 증가
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
		//아래 함수들은 ==와 != 연산자 오버로딩 함수들을 외부 함수로 선언하지 않고 iterator클래스의 멤버 함수로 선언했다.
		//위 함수와 똑같이 잘 작동한다.
		//bool operator==(/*const Single_list_it& it1,*/ const Single_list_it& it2)
		//{
		//	/*return it1.ptr == it2.ptr;*/
		//	return this->ptr == it2.ptr;
		//}
		//bool operator!=(/*const Single_list_it& it1,*/ const Single_list_it& it2)
		//{
		//	/*return it1.ptr != it2.ptr;*/
		//	return this->ptr == it2.ptr;
		//}
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
	//other 리스트 원소 순서 그대로 가져온다고 생각해라. 따라서 other.begin()을 head에 넣고 각각 다음 원소로 이동하면서
	//삽입하면 될 것이다.
	Single_list(const Single_list& other) :Single_list()
	{
		if (other.head)
		{
			head = new node{ NULL, NULL };

			auto cur = head;
			auto it = other.begin();
			while (true)
			{
				//head는 바뀌지 않고 계속 뒤로 삽입한다.(push_back과 같은 동작)
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
		//rebegin()과 rend()는 임시 객체라서 &&를 사용하거나 auto만 사용한다.
		//일반 참조는 사용할 수 없다.
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
