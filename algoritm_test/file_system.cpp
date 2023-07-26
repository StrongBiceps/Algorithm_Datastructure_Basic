#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class file_system
{
private:
	class node
	{
	public:
		string name;
		bool is_dir;
		vector<node*> children;
	};
public:
	using node_ptr = node*;
private:
	node_ptr root;
	node_ptr cwd; //���� ���丮�� ������ ����
public:
	file_system()
	{
		root = new node{ "/",true,{} };
		cwd = root;//ó������ ��Ʈ�� ���� ���丮�� ����
	}
	node_ptr find(const string& path)
	{
		if (path[0] == '/') //������ -> root�κ��� ���۵� path�� �ǹ��Ѵ�.
		{
			return find_impl(root, path.substr(1));//path�� �ε��� 1���� ���������� �Ľ��ؼ� ����
		}
		else
		{
			return find_impl(cwd, path); //��� ��δ� ���� ���丮�������� ã�´�.
		}
	}
	bool add(const string& path, bool is_dir)
	{
		if (path[0] == '/')
		{
			return add_impl(root, path.substr(1), is_dir);
		}
		else
		{
			return add_impl(cwd, path, is_dir);
		}
	}
	void show_path(const string& path)
	{
		auto found = find(path);

		if (!found)
		{
			cout << path << "��ΰ� �������� �ʽ��ϴ�." << endl;
			return;
		}

		if (found->is_dir)
		{
			for (auto child : found->children)
			{
				cout << (child->is_dir ? "d" : "-") << child->name << endl;
			}
		}
		else
		{
			cout << "-" << found->name << endl;
		}
	}
	bool change_dir(const string& path)
	{
		auto found = find(path);
		if (found && found->is_dir)
		{
			cwd = found;
			cout << path << "���� ���丮�� " << cwd->name << "�� �̵��մϴ�." << endl;
			return true;
		}
		cout << path << "��θ� ã�� �� �����ϴ�." << cwd->name << "�� �̵��մϴ�." << endl;
		return false;
	}
private:
	node_ptr find_impl(node_ptr directory, const string& path)
	{
		if (path.empty())
		{
			return directory;
		}
		//find�� ã���� �ϴ� ������ ���� �ε����� ��ȯ
		//���� ã�� �������� find�� -1�� ����
		auto sep = path.find('/');
		//path.substr(0,sep)�� '/'���������� �ǹ��Ѵ�.
		//npos�� -1�� ���������� ���ǵǾ� �ִ�. ���� sep�� npos�� �� �ڵ� ==
		//�� ����ǰ� ����� current_path�� ����ȴ�.
		//ù ��° '/'���� ������ current_path�� ���İ� rest_path�̴�. �� �� ���� ��Ϳ���
		//�� ������ ���丮�� �Ѿ��. / -> /
		string current_path = sep == string::npos ? path : path.substr(0, sep);
		//substr(sep)�� �ع����� '/'���� �Ľ̵ǹǷ� substr(sep+1)�� �Ѵ�.
		string rest_path = sep == string::npos ? "" : path.substr(sep + 1);

		//begin���� end���� �ȿ��� ���� ���� �����ϴ� ���� ã�´�.
		auto found = find_if(directory->children.begin(), directory->children.end(), [&](const node_ptr& child) {
			return child->name == current_path;
			});

		if (found != directory->children.end())
		{
			return find_impl(*found, rest_path);
		}
		//���� � �ڵ忡�� �ɸ��� �ʾҴٸ� �ش� ��δ� ���ų� �߸��� ����̹Ƿ� NULL ����
		return NULL;
	}
	bool add_impl(node_ptr directory, const string& path, bool is_dir)
	{
		//�ش� directory�� is_dir�� false��� �����̴�.
		if (!directory->is_dir)
		{
			cout << directory->name << "�� �����Դϴ�." << endl;
			return false;
		}

		auto sep = path.find('/');

		//path�� '/'�� ���� ���
		if (sep == string::npos)
		{
			auto found = find_if(directory->children.begin(), directory->children.end(), [&](const node_ptr& child) {
				return child->name == path;
				});

			if (found != directory->children.end())
			{
				cout << directory->name << "�� �̹� " << path << " �̸��� ����/���丮�� �ֽ��ϴ�." << endl;
				return false;
			}

			//�ش� path�� �������� �ʴ´ٸ� ���丮�� �ش� ����/���丮�� �߰��Ѵ�.
			directory->children.push_back(new node{ path,is_dir,{} });
			return true;
		}
		
		//path�� '/'�� �ִ� ���,�� ���丮 �̸��� �����ϰ� �ִ� ���.
		string next_dir = path.substr(0, sep);
		auto found = find_if(directory->children.begin(), directory->children.end(), [&](const node_ptr& child) {
			return child->name == next_dir && child->is_dir;
			});

		if (found != directory->children.end())
		{
			return add_impl(*found, path.substr(sep + 1), is_dir);
		}

		//���� ���丮�� ã�� �̸��� ���� ���
		cout << directory->name << "�� " << next_dir << "�̸��� ���丮�� �����ϴ�." << endl;

		return false;
	}
};

int main()
{
	file_system fs;
	//�Ʒ� add���� ��� root�� �ڽ����� ����.
	fs.add("usr", true);	// '/'�� usr ���丮 �߰�
	fs.add("etc", true);	// '/'�� etc ���丮 �߰�
	fs.add("var", true);	// '/'�� var ���丮 �߰�
	fs.add("tmp_file", false);	//'/'�� tmp_file ���� �߰�

	cout << "\"/\"�� ����/���丮 ���:" << endl;
	fs.show_path("/"); // '/'�� ����/���丮 ��� ��� root�� children�� ��� ���

	cout << endl;
	fs.change_dir("usr");
	//�Ʒ� add���� usr�� �ڽ����� ����.
	fs.add("gilbut", true);
	fs.add("gilbut/Downloads", true);
	fs.add("gilbut/Downloads/newFile.cpp", false);

	cout << "���� ���丮���� usr�� ����/���丮 ���: " << endl;
	fs.show_path("usr"); // ���� ���丮�� usr�ε� usr�ȿ� usr�� �����Ƿ� show_path�� find���� NULL�� ��ȯ�Ѵ�.
	//���� ����� ����� �� ����.

	// /usr�� �������̹Ƿ� root�������� ã�´� usr�� root�� �ڽ��̹Ƿ� ����� ����� �����ϴ�.
	cout << "\"/usr\"�� ���� ���丮 ���:" << endl;
	fs.show_path("/usr");


	cout << "\"/usr/gilbut/Downloads\"�� ����/���丮 ���" << endl;
	fs.show_path("/usr/gilbut/Downloads");
	//fs.show_path("/Downloads"); �� �ڵ�� �Ұ����ϴ�./Downloads�� root�� �ڽ��� �ƴϱ� �����̴�. 
	//���� root���� ã�� ������ Ư���� ã�� �� ���ٰ� ���´�.
	return 0;
}