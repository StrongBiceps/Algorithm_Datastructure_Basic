#include <iostream>

template<typename T>
class Cir_list
{
private:
	class Cir_list_node
	{
	public: //private���� ���� �� �ܺ� Ŭ�������� ����� �� �����Ƿ� public ����
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
		//head->prev ���(�� ������ ���)�� dummy�� ��� �ٲ��, 
		//dummy�� head ���̿� new_node�� �����ϰ� ������ ��
		//new_node�� head�� �ٲ۴�.�� ���� ó���� �ƹ� ��嵵 ���� ��
		//head�� �ڱ� �ڽ��� ����Ų��. �� head�� ���� ������ �����
		//dummy����̴�. dummy�� head ���̿� new_node�� �����ϱ� ������
		//���� ������ ���� �ٲ��� �ʴ´�.
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
		//head�� dummy��� �ƹ� �۾��� ���� �ʰ� �Լ��� �����Ѵ�.
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
		}
	}
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

		//friend�� �����ؾ� Ŭ���� �ܺο��� ȣ���� �� �ִ�.
		//���� ��� �ݺ������� ȣ���Ѵ�.
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
		other.n = 0; //other�� head�� �������ְ� �ڽ��� head �����͸�
		//��ü�����Ƿ� �ڽ��� ���ҵ鿡 ������ ����� ����. ���� �̵��� head��
		//�������� ��ü�� other�� ��� ���ҿ� ������ �� �ִ�.

		//move(other)���� other�� head�� NULL�� ������ ������
		//main���� delete�� other�� �Ҹ��ڸ� ȣ���� �� other�� head�� �̵��� ��ü�� head��
		//���� �޸𸮸� �����ϰ� �����Ƿ� other�� �ڽ��� head�� ��ü�ع����� �� ��ü������
		//head�� ������ ���� ����. ���� head�� NULL�� ���ְ�, ������ ������ ���ҵ���
		//head�� �����ʰ� ���ÿ� ��� ������ ���̳� �ٸ� ����(head���� ��� ������ �� �ֱ� ����)
		//���� other�� head�� delete�ϸ� �ȴ�. �׷��� �Ʒ����� ������ �Ҹ��ڿ��� size���� �ݺ�
		//���� �ٷ� �������� head�� delete�� �� �ְ� n�� 0���� �ʱ�ȭ���ش�. n�� 0���� �������� 
		//������ other�� head�� NULL�̱� ������ erase�� ������ �� ����. ���� ���ѷ����� ������
		//�ȴ�.
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

	std::cout << "��� ���: " << std::endl;
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

	//*�����ڰ� ���� �����̱� ������ ���� �ٲٸ� ���� �����͵� ����ȴ�.
	//*it1 = 100;
	//std::cout << "C1 after tuning :" << *it1 << std::endl;

	//std::cout << "equal test: " << (it1 == it2) << std::endl;
	return 0;
}