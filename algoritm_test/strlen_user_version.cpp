#include <iostream>
using namespace std;

void strlen_user_version(const char* _cArr);

int main()
{
	const char* pChar = "rabbit tiger";
	strlen_user_version(pChar);
	return 0;
}

void strlen_user_version(const char* _cArr)
{
	int iIndex = 0;

	while (true)
	{
		if (_cArr[iIndex] != '\0')
			++iIndex;
		else
			break;
	}
	cout << iIndex << endl;
}
