#include <iostream>
using namespace std;

void reverse_user_version(char* _cArr);

int main()
{
	/*
	*char pChar[7]�� const ���� ���� �� �ִ�. ���� �ּҸ� �����ϴ� ���� �ƴϱ� �����̴�.
	* �� rabbit�� const�ν� ���� ���ڸ� ������ �� ����. ������ pChar�� �����ϴ� ���� �����̱� ������
	* ���� �޸� ������ �����ϴ� ���� �ƴϴ�.
	*
	* �׷��� char*pChar = "rabbit"�� ��Ⱑ �ٸ���. "rabbit"�� �����ϴ� ���� �ƴ� �ּҸ� �����ϴ� ���̱� ������
	* pChar�� "rabbit"�� �޸� ������ �����ϰ� �ȴ�. �׷��� pChar�� ���� �������̱� ������ "rabbit"�� ���� ���ڸ�
	* ������ �� �ִ�. ���� ������� �浹 ������ ���� ������ �� ���� ���̴�.
	*
	* ���� ������ ��� ���� ������ ������ �浹�ϴ� �Ͱ� ���� ������.
	*/
	char pChar[7] = "rabbit";
	//char* pChar = "rabbit";
	reverse_user_version(pChar);
	cout << pChar << endl;
	return 0;
}

void reverse_user_version(char* _cArr)
{
	int ilast_Index = strlen(_cArr) - 1;

	for (register int i = 0; i < ilast_Index / 2 - 1; ++i)
	{
		char cTemp = _cArr[i];
		_cArr[i] = _cArr[ilast_Index - i];
		_cArr[ilast_Index - i] = cTemp;
	}
}
