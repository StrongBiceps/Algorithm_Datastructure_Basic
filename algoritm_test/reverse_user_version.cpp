#include <iostream>
using namespace std;

void reverse_user_version(char* _cArr);

int main()
{
	/*
	*char pChar[7]은 const 값을 넣을 수 있다. 같은 주소를 참조하는 것이 아니기 때문이다.
	* 즉 rabbit은 const로써 내부 문자를 변경할 수 없다. 하지만 pChar에 대입하는 것은 복사이기 때문에
	* 같은 메모리 공간을 참조하는 것이 아니다.
	*
	* 그러나 char*pChar = "rabbit"은 얘기가 다르다. "rabbit"을 복사하는 것이 아닌 주소를 대입하는 것이기 때문에
	* pChar는 "rabbit"의 메모리 공간을 참조하게 된다. 그러나 pChar은 가변 포인터이기 때문에 "rabbit"의 내부 문자를
	* 변경할 수 있다. 따라서 상수성의 충돌 때문에 서로 대입할 수 없는 것이다.
	*
	* 가변 참조와 상수 참조 사이의 대입이 충돌하는 것과 같은 이유다.
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
