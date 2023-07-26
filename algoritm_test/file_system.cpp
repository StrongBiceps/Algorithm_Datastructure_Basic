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
	node_ptr cwd; //현재 디렉토리를 저장할 변수
public:
	file_system()
	{
		root = new node{ "/",true,{} };
		cwd = root;//처음에는 루트를 현재 디렉토리로 설정
	}
	node_ptr find(const string& path)
	{
		if (path[0] == '/') //절대경로 -> root로부터 시작된 path를 의미한다.
		{
			return find_impl(root, path.substr(1));//path의 인덱스 1부터 마지막까지 파싱해서 전달
		}
		else
		{
			return find_impl(cwd, path); //상대 경로는 현재 디렉토리에서부터 찾는다.
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
			cout << path << "경로가 존재하지 않습니다." << endl;
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
			cout << path << "현재 디렉토리를 " << cwd->name << "로 이동합니다." << endl;
			return true;
		}
		cout << path << "경로를 찾을 수 없습니다." << cwd->name << "로 이동합니다." << endl;
		return false;
	}
private:
	node_ptr find_impl(node_ptr directory, const string& path)
	{
		if (path.empty())
		{
			return directory;
		}
		//find는 찾고자 하는 문자의 시작 인덱스를 반환
		//만약 찾지 못했으면 find는 -1을 리턴
		auto sep = path.find('/');
		//path.substr(0,sep)는 '/'이전까지를 의미한다.
		//npos는 -1의 정수값으로 정의되어 있다. 먼저 sep와 npos의 비교 코드 ==
		//가 실행되고 결과가 current_path로 저장된다.
		//첫 번째 '/'이전 까지가 current_path고 이후가 rest_path이다. 즉 한 번의 재귀에서
		//한 단위의 디렉토리를 넘어간다. / -> /
		string current_path = sep == string::npos ? path : path.substr(0, sep);
		//substr(sep)를 해버리면 '/'부터 파싱되므로 substr(sep+1)로 한다.
		string rest_path = sep == string::npos ? "" : path.substr(sep + 1);

		//begin에서 end범위 안에서 람다 식을 만족하는 것을 찾는다.
		auto found = find_if(directory->children.begin(), directory->children.end(), [&](const node_ptr& child) {
			return child->name == current_path;
			});

		if (found != directory->children.end())
		{
			return find_impl(*found, rest_path);
		}
		//위의 어떤 코드에도 걸리지 않았다면 해당 경로는 없거나 잘못된 경로이므로 NULL 리턴
		return NULL;
	}
	bool add_impl(node_ptr directory, const string& path, bool is_dir)
	{
		//해당 directory가 is_dir이 false라면 파일이다.
		if (!directory->is_dir)
		{
			cout << directory->name << "은 파일입니다." << endl;
			return false;
		}

		auto sep = path.find('/');

		//path에 '/'가 없는 경우
		if (sep == string::npos)
		{
			auto found = find_if(directory->children.begin(), directory->children.end(), [&](const node_ptr& child) {
				return child->name == path;
				});

			if (found != directory->children.end())
			{
				cout << directory->name << "에 이미 " << path << " 이름의 파일/디렉토리가 있습니다." << endl;
				return false;
			}

			//해당 path가 존재하지 않는다면 디렉토리에 해당 파일/디렉토리를 추가한다.
			directory->children.push_back(new node{ path,is_dir,{} });
			return true;
		}
		
		//path에 '/'가 있는 경우,즉 디렉토리 이름을 포함하고 있는 경우.
		string next_dir = path.substr(0, sep);
		auto found = find_if(directory->children.begin(), directory->children.end(), [&](const node_ptr& child) {
			return child->name == next_dir && child->is_dir;
			});

		if (found != directory->children.end())
		{
			return add_impl(*found, path.substr(sep + 1), is_dir);
		}

		//현재 디렉토리에 찾는 이름이 없는 경우
		cout << directory->name << "에 " << next_dir << "이름의 디렉토리가 없습니다." << endl;

		return false;
	}
};

int main()
{
	file_system fs;
	//아래 add들은 모두 root의 자식으로 들어간다.
	fs.add("usr", true);	// '/'에 usr 디렉토리 추가
	fs.add("etc", true);	// '/'에 etc 디렉토리 추가
	fs.add("var", true);	// '/'에 var 디렉토리 추가
	fs.add("tmp_file", false);	//'/'에 tmp_file 파일 추가

	cout << "\"/\"의 파일/디렉토리 목록:" << endl;
	fs.show_path("/"); // '/'의 파일/디렉토리 목록 출력 root의 children을 모두 출력

	cout << endl;
	fs.change_dir("usr");
	//아래 add들은 usr의 자식으로 들어간다.
	fs.add("gilbut", true);
	fs.add("gilbut/Downloads", true);
	fs.add("gilbut/Downloads/newFile.cpp", false);

	cout << "현재 디렉토리에서 usr의 파일/디렉토리 목록: " << endl;
	fs.show_path("usr"); // 현재 디렉토리는 usr인데 usr안에 usr이 없으므로 show_path의 find에서 NULL을 반환한다.
	//따라서 제대로 출력할 수 없다.

	// /usr은 절대경로이므로 root에서부터 찾는다 usr은 root의 자식이므로 출력이 제대로 가능하다.
	cout << "\"/usr\"의 파일 디렉토리 목록:" << endl;
	fs.show_path("/usr");


	cout << "\"/usr/gilbut/Downloads\"의 파일/디렉토리 목록" << endl;
	fs.show_path("/usr/gilbut/Downloads");
	//fs.show_path("/Downloads"); 이 코드는 불가능하다./Downloads는 root의 자식이 아니기 때문이다. 
	//따라서 root부터 찾는 절대경로 특성상 찾을 수 없다고 나온다.
	return 0;
}