#include <iostream>

template<typename T>
class Cir_list
{
private:
	class Cir_list_node
	{
	public: //private으로 선언 시 외부 클래스에서 사용할 수 없으므로 public 선언
		T* Data;
		Cir_list_node* next;
		Cir_list_node* prev;

		~Cir_list_node()
		{
			delete Data;
		}
	};
public:
	using node = Cir_list_node;
	using node_ptr = node*;

private:
	node_ptr head;
	size_t n;
public:
	Cir_list() : n(0)
	{
		head = new node{ NULL,NULL,NULL };
		head->next = head;
		head->prev = head;
	}
	size_t Size() const
	{
		return n;
	}
	void insert(T value)
	{
		//head->prev 노드(맨 마지막 노드)가 dummy로 잠시 바뀌고, 
		//dummy와 head 사이에 new_node를 삽입하고 연결한 뒤
		//new_node를 head로 바꾼다.즉 가장 처음에 아무 노드도 없을 때
		//head는 자기 자신을 가리킨다. 이 head가 가장 마지막 노드인
		//dummy노드이다. dummy와 head 사이에 new_node를 삽입하기 때문에
		//가장 마지막 노드는 바뀌지 않는다.
		//또한 head와 dummy 사이에 삽입하기 때문에 head의 next는 바뀌지 않고 prev만 바꿔주면 된다.
		auto new_node = new node{ new T(value),NULL,NULL };
		++n;
		auto dummy = head->prev;
		dummy->next = new_node;
		new_node->prev = dummy;
		if (head == dummy)
		{
			dummy->prev = new_node;
			new_node->next = dummy;
			head = new_node;
			return;
		}
		new_node->next = head;
		head->prev = new_node;
		head = new_node;
	}
	void erase(const T& value)
	{
		//head가 dummy라면 아무 작업도 하지 않고 함수를 종료한다.
		auto cur = head;
		auto dummy = head->prev;

		//dummy == value인 상황도 생각해야 한다. 여기에는 없지만 코딩은 단순할 것이다.

		while (cur != dummy)
		{
			if (*(cur->Data) == value)
			{
				cur->prev->next = cur->next;
				cur->next->prev = cur->prev;
				if (head == cur)
				{
					head = head->next;
				}
				delete cur;
				n--;
				return;
			}
			cur = cur->next;
		}
	}
	//Iterator Pattern
	class Cir_list_it
	{
	private:
		node_ptr ptr;
	public:
		Cir_list_it(node_ptr p) :ptr(p) {}

		T& operator*()
		{
			return *(ptr->Data);
		}
		node_ptr get()
		{
			return ptr;
		}
		Cir_list_it& operator++()
		{
			ptr = ptr->next;
			return *this;
		}
		Cir_list_it operator++(int)
		{
			Cir_list_it it = *this;
			++(*this);
			return it;
		}
		Cir_list_it& operator--()
		{
			ptr = ptr->prev;
			return *this;
		}
		Cir_list_it& operator--(int)
		{
			Cir_list_it it = *this;
			--(*this);
			return it;
		}

		//friend로 선언해야 클래스 외부에서 호출할 수 있다.
		//범위 기반 반복문에서 호출한다.
		// == 는 이항 연산자이기 때문에 매개변수가 2개 필요하다. 따라서 멤버 함수로 만들 수 없다.
		//이 코드는 전역 함수를 friend 함수로 만들고 클래스 내부에 선언하여 Inline 최적화한 것이다. 즉, 이 함수는 멤버함수가 아니다.
		friend bool operator==(const Cir_list_it& it1, const Cir_list_it& it2)
		{
			return it1.ptr == it2.ptr;
		}
		friend bool operator!=(const Cir_list_it& it1, const Cir_list_it& it2)
		{
			return it1.ptr != it2.ptr;
		}
	};

	using it = Cir_list_it;
	it begin()
	{
		return it(head);
	}
	it begin() const
	{
		return it(head);
	}
	it end()
	{
		return it(head->prev);
	}
	it end() const
	{
		return it(head->prev);
	}
	Cir_list(const Cir_list<T>& other) :Cir_list()
	{
		for (const auto i : other)
		{
			insert(i);
		}
	}
	Cir_list(Cir_list<T>&& other) noexcept :Cir_list()
	{
		head = other.head;
		other.head = NULL;
		n = other.n;
		other.n = 0; //other는 head를 이전해주고 자신의 head 포인터를
		//해체했으므로 자신의 원소들에 접근할 방법이 없다. 또한 이동된 head로
		//이전받은 객체는 other의 모든 원소에 접근할 수 있다.

		//move(other)에서 other의 head를 NULL로 해주지 않으면
		//main에서 delete가 other의 소멸자를 호출할 때 other의 head와 이동된 객체의 head가
		//같은 메모리를 참조하고 있으므로 other가 자신의 head를 해체해버리면 이 객체에서는
		//head에 접근할 수가 없다. 따라서 head를 NULL로 해주고, 어차피 나머지 원소들은
		//head가 이전됨과 동시에 모두 이전된 것이나 다름 없다(head에서 모두 접근할 수 있기 때문)
		//따라서 other는 head만 delete하면 된다. 그래서 아래에서 정의한 소멸자에서 size에서 반복
		//문을 바로 빠져나와 head만 delete할 수 있게 n을 0으로 초기화해준다. n을 0으로 설정하지 
		//않으면 other의 head는 NULL이기 때문에 erase를 실행할 수 없다. 따라서 무한루프에 빠지게
		//된다.
	}
	Cir_list(const std::initializer_list<T>& il) :Cir_list()
	{
		for (const auto& i : il)
		{
			insert(i);
		}
	}
	~Cir_list()
	{
		if (head != NULL)
		{
			while (Size())
			{
				erase(*(head->Data));
			}
		}
		delete head;
	}
	void printall()
	{
		for (auto& i : *this)
		{
			std::cout << i << " ";
		}
	}
};

class Playlist
{
public:
	Cir_list<int> list;

	void insert(int song)
	{
		list.insert(song);
	}
	void erase(int song)
	{
		list.erase(song);
	}
	void loopOnce()
	{
		list.printall();
	}
};

int main()
{
	std::cout << "wrapper class result" << std::endl;
	Playlist p1;
	p1.insert(1);
	p1.insert(2);

	std::cout << "재생 목록: " << std::endl;
	p1.loopOnce();
	std::cout << std::endl;

	Cir_list<int>* iter_dynamic = new Cir_list<int>();

	iter_dynamic->insert(10);
	iter_dynamic->insert(20);
	iter_dynamic->insert(30);

	//move semantics : use std::move = L-value to R-value reference
	Cir_list<int> C1(std::move(*iter_dynamic));
	std::cout << "move semantics test" << std::endl;
	delete iter_dynamic;
	C1.printall();
	/*
	Cir_list<int>::Cir_list_it it1 = C1.begin();
	Cir_list<int>::Cir_list_it it2 = C1.end();
	std::cout << "C1 : size :" << C1.Size() << std::endl;
	std::cout << "C1 : head :" << *it1 << std::endl;
	std::cout << "C1 : head->next :" << *(++it1) << std::endl;
	//initializer list constructor*/
	//Cir_list<int> C3({10, 20, 30, 40});

	//*연산자가 참조 리턴이기 때문에 값을 바꾸면 원래 데이터도 변경된다.
	//*it1 = 100;
	//std::cout << "C1 after tuning :" << *it1 << std::endl;

	//std::cout << "equal test: " << (it1 == it2) << std::endl;
	return 0;
}

/*
*****반복자로 원형 순회가 가능하게 한 버전 (위 버전은 반복자로 ++연산이나 --연산을 하다가 dummy를 만나게 되면 액세스 위반
	오류가 남 그러나 아래 버전은 다음 노드나 이전 노드가 더미 노드일 때 더미 노드를 건너 뛰어서 유효한 노드를 반환하게 함)

	#include <iostream>
using namespace std;

template<typename T>
class Cir_list
{
private:
	class Cir_list_node
	{
	public: //private으로 선언 시 외부 클래스에서 사용할 수 없으므로 public 선언
		T* Data;
		Cir_list_node* next;
		Cir_list_node* prev;

		~Cir_list_node()
		{
			delete Data;
		}
	};
public:
	using node = Cir_list_node;
	using node_ptr = node*;

private:
	node_ptr head;
	size_t n;
public:
	Cir_list() : n(0)
	{
		head = new node{ NULL,NULL,NULL };
		head->next = head;
		head->prev = head;
	}
	size_t Size() const
	{
		return n;
	}
	void insert(T value)
	{
		auto new_node = new node{ new T(value),NULL,NULL };
		++n;
		auto dummy = head->prev;
		dummy->next = new_node;
		new_node->prev = dummy;
		if (head == dummy)
		{
			dummy->prev = new_node;
			new_node->next = dummy;
			head = new_node;
			return;
		}
		new_node->next = head;
		head->prev = new_node;
		head = new_node;
	}
	void erase(const T& value)
	{
		//head가 dummy라면 아무 작업도 하지 않고 함수를 종료한다.
		auto cur = head;
		auto dummy = head->prev;

		while (cur != dummy)
		{
			if (*(cur->Data) == value)
			{
				cur->prev->next = cur->next;
				cur->next->prev = cur->prev;
				if (head == cur)
				{
					head = head->next;
				}
				delete cur;
				n--;
				return;
			}
			cur = cur->next;
		}
	}
	//Iterator Pattern
	class Cir_list_it
	{
	private:
		node_ptr ptr;
	public:
		Cir_list_it(node_ptr p) :ptr(p) {}

		T& operator*()
		{
			return *(ptr->Data);
		}
		node_ptr get()
		{
			return ptr;
		}
		Cir_list_it& operator++()
		{
			//다음이 더미 노드라면 헤드를 반환
			if (ptr->next->Data == NULL)
			{
				ptr = ptr->next->next;
				return *this;
			}

			ptr = ptr->next;
			return *this;
		}
		Cir_list_it operator++(int)
		{
			Cir_list_it it = *this;

			//다음이 더미 노드라면 헤드를 반환
			if (*this->ptr->next->Data == NULL)
			{
				ptr = ptr->next->next;

				return it;
			}

			++(*this);
			return it;
		}
		Cir_list_it& operator--()
		{
			//이전이 더미 노드라면 마지막 노드를 반환
			if (ptr->prev->Data == NULL)
			{
				ptr = ptr->prev->prev;
				return *this;
			}

			ptr = ptr->prev;
			return *this;
		}
		Cir_list_it& operator--(int)
		{
			//이전이 더미 노드라면 마지막 노드를 반환
			if (*this->ptr->prev->Data == NULL)
			{
				ptr = ptr->prev->prev;

				return it;
			}

			Cir_list_it it = *this;
			--(*this);
			return it;
		}

		//friend로 선언해야 클래스 외부에서 호출할 수 있다.
		//범위 기반 반복문에서 호출한다.
		friend bool operator==(const Cir_list_it& it1, const Cir_list_it& it2)
		{
			return it1.ptr == it2.ptr;
		}
		friend bool operator!=(const Cir_list_it& it1, const Cir_list_it& it2)
		{
			return it1.ptr != it2.ptr;
		}
	};

	using it = Cir_list_it;
	it begin()
	{
		return it(head);
	}
	it begin() const
	{
		return it(head);
	}
	it end()
	{
		return it(head->prev);
	}
	it end() const
	{
		return it(head->prev);
	}
	Cir_list(const Cir_list<T>& other) :Cir_list()
	{
		for (const auto i : other)
		{
			insert(i);
		}
	}
	Cir_list(Cir_list<T>&& other) noexcept :Cir_list()
	{
		head = other.head;
		other.head = NULL;
		n = other.n;
		other.n = 0; 
	}
	Cir_list(const std::initializer_list<T>& il) :Cir_list()
	{
		for (const auto& i : il)
		{
			insert(i);
		}
	}
	~Cir_list()
	{
		if (head != NULL)
		{
			while (Size())
			{
				erase(*(head->Data));
			}
		}
		delete head;
	}
	void printall()
	{
		for (auto& i : *this)
		{
			std::cout << i << " ";
		}
	}
};

class Playlist
{
public:
	Cir_list<int> list;

	void insert(int song)
	{
		list.insert(song);
	}
	void erase(int song)
	{
		list.erase(song);
	}
	void loopOnce()
	{
		list.printall();
	}
};

int main()
{
	Cir_list<int> C1;
	C1.insert(1);
	C1.insert(2);
	auto temp = C1.begin();
	cout << *temp << endl;
	++temp;
	cout << *temp << endl;
	++temp;
	cout << *temp << endl;
	return 0;
}
