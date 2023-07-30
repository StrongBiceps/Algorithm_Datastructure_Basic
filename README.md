# 2023.07.26 

# N - ary Tree
<n항 트리를 이용한 file_system 구현>
리눅스 운영체제의 디렉토리 계층 구조를 n항 트리를 이용하여 구현했다.

1.기본적인 N-항 트리를 구성한다. 이 트리의 노드는 디렉토리 또는 파일의 이름, 그리고 이것이 파일인지 디렉토리인지를 분간하는 플래그 멤버로 갖는다.
2.현재 디렉토리를 저장할 데이터 멤버를 추가한다.
3.단일 디렉토리 루트로 트리를 초기화한다.
4.경로명을 인자로 받는 디렉토리/파일 검색 함수를 추가한다. 상대 경로와 절대 경로 모두를 지원한다.
5.현재 디렉토리를 변경하는 함수를 추가한다.

인터페이스와 함수의 구현을 분리하고 함수를 캡슐화하기 위해 public section에 인터페이스 메소드를 정의하고 내부에서 impl 메소드를 호출한다.
따라서 사용자는 impl 메소드에는 접근할 수 없다.

# Median Algorithm

<최대 힙과 최소 힙을 이용한 중앙값 알고리즘>

최대 힙과 최소 힙을 캠슐화한 median 클래스로 입력된 원소들의 중앙값을 구하는 알고리즘

1.중앙값을 기준으로 작은 값들은 최대 힙으로 들어가고 큰 값들은 최소 힙으로 들어간다.
사이즈 비교를 하는 이유는 중앙값을 기준으로 두 힙의 크기가 균등하게 유지되어야 하기 때문이다.
2.각 Heap의 top값을 더한 후 2로 나눈 값이 입력된 원소들의 중앙값이 된다.

# Data list Merge Algorithm

<힙을 이용한 데이터 리스트 병합>

1.각각의 리스트는 이미 정렬되어 있기 때문에, 각 리스트의 최소 원소는 맨 앞에 위치한다. 이들 원소로부터 최솟값을 빠르게 선택하기 위해
힙을 사용한다.
2.힙에서 최소 원소를 가져온 후 이를 제거하고, 최소 원소가 있던 리스트에서 그 다음으로 작은 원소를 선택해 힙에 추가한다.
3.힙의 노드는 이 원소를 어느 리스트에서 가져왔는지, 또한 해당 리스트에서 몇 번째 원소인지를 저장해야 한다.

이 알고리즘의 시간복잡도는 리스트가 k개 있다면 힙의 크기는 k가 되고 모든 힙 연산의 시간복잡도는 log k가 된다. 힙을 구성하는 데는
O(log k)가 된다. 그런 다음 각 원소에 대해 힙 연산을 수행해야 한다. 전체 원소 갯수는 N*k개이다. 그러므로 전체 시간복잡도는
N*klog k이다.

# Hash_Map (modulo operation)

<모듈로 연산을 이용하여 해시 맵 구성>

이 코드는 해시 맵의 작동 원리를 간단하게 공부할 수 있는 예제코드이다.

단순하게 해시 함수를 모듈로 연산으로 사용하여 해시 맵을 구성한다. 이 방식은 간단하지만 해시 값의 중복이 일어날 수 있다.
룩업 상황에서 모듈로 연산을 통해서 구한 index로 접근하기 때문에 빠르고 간단하다.

아직 충돌에 대해서는 깊게 생각하지 않은 해시 맵이다.

# Hash_Table (chaining)

<체이닝을 이용한 해시 테이블>

이번 해시 테이블은 체이닝을 이용해서 충돌을 어느정도 해결한 예제코드이다.

하지만 이번 방법도 충돌을 해결하는 효과적인 방법은 아니다.

이번에 사용할 체이닝 기법은 vector에 list를 넣어서 해시 값이 같더라도 중복해서 값을 저장할 수 있도록 한다.

모든 키가 같은 해시 값을 가질 경우에 같은 리스트에 모든 원소가 저장되기 때문에 리스트에서 값을 룩업할 때 상당히 느릴 수 있다.

# Hash_Table (cukoo hashing)

열린 주소 지정(open addressing) 방식은 체이닝처럼 리스트에 원소를 저장하는 것이 아니라 해시 테이블 내부에 저장하는 방식이다.
그러므로 해시 테이블의 크기가 반드시 데이터 개수보다 커야 한다. 열린 주소 지정 방식의 핵심은 특정 해시 값에 해당하는 위치가
이미 사용되고 있다면 테이블의 다른 비어 있는 위치를 탐색하는 것이다. 

비어 있는 위치를 탐색하는 방법은 여러 가지가 있을 수 있다.

선형 탐색 - hash(x)에 해당하는 셀이 이미 채워져 있다면, hash(x+1)위치의 셀을 확인한다. hash(x+1)도 사용중이라면, hash(x+2)를 확인한다.
이 방식은 바로 다음 인덱스를 검사하고 저장하므로 데이터가 군집화(clustering)되는 경우가 발생한다. 데이터가 뭉쳐서 저장되면, 비어있는 셀을
확인하는 작업이 느려지게 된다. 주변의 모든 셀들을 검사해야 하기 때문이다.

이차함수 탐색 - hash(x)가 사용중이라면 hash(x+1^2)으로 이동하고, 마찬가지로 사용중이라면 hash(x+2^2)로 이동하여 검사한다.
하지만 원소 위치가 기존에 저장된 원소들에 의해 영향을 받는 다는 문제가 있다. 이차함수 탐색도 마찬가지로 클러스터링이 존재할 수 있다. 물론
선형 탐색보다는 확률이 줄어들지만 가능성이 있다. 또한 해시 테이블이 커지면 점프 거리가 증가하면서 속도가 느려질 수 있다.

위 방식들은 최악의 상황에 O(1)을 보장하지 못하지만 다음의 방법은 최악의 상황에서 구현만 제대로 한다면 O(1)을 만족한다.
완벽한 해싱 기법 중 하나인 뻐꾸기(cuckoo)해싱이 있다.

뻐꾸기 해싱은 크기가 같은 두 개의 해시 테이블을 사용하고, 각각의 해시 테이블은 서로 다른 해시 함수를 가진다. 모든 원소는 두 해시 테이블 중 하나에 있을
수 있고, 그 위치는 해당 해시 테이블의 해시 함수에 의해 결정된다.

룩업의 경우, 특정 원소가 존재하는지를 알기 위해 저장 가능한 위치 두 군데만 확인해보면 된다. 그러므로 룩업 연산의 시간 복잡도는 항상 O(1)이다.

그러나 삽입 연산은 좀 더 오래 걸릴 수 있다. 먼저 A가 비어있는 지 검사하고, 비어있다면 삽입하면 된다. 하지만 A의 위치가 사용중이라면 B를 검사한다. B가 사용중이라면
B의 원소를 A로 옮기고 B에 해당 키를 저장한다. 그러면 A로 옮겨진 키는 다시 비어있는 공간을 찾아야 하므로 시간이 걸릴 수 있다.(재귀적)

이 경우에서 순환(무한 루프)에 빠질 수 있는데, 이럴 경우에는 재해싱을 수행해야 한다. 원활한 사용을 위해서는 부하율이 0.5보다 작게끔 구성해야 한다. 즉 해시 테이블
크기보다 원소 갯수가 절반보다 적어야 한다.

# std::unordered_set,std::unordered_map

unordered_set은 키만을 저장할 수 있고, unordered_map은 키와 값을 함께 저장할 수 있다.
두 컨테이너 모두 체이닝을 사용하는 해시 테이블 형태로 구현되어 있다. 해시 테이블의 각 행은 키 또는 키와 값의 쌍을 저장하는 벡터이다. 여기서 각
행을 버킷이라고 부른다. 즉, 키로부터 해시 값을 구하면 이에 해당하는 버킷에 접근할 수 있다. 각 버킷은 하나의 리스트를 가진다.

기본적으로 이들 컨테이너는 최대 1의 부하율을 가진다. 해시 테이블 크기보다 원소 개수가 많아지게 되면 곧바로 해시 테이블 크기를 키우고, 해시 함수를 변경하는
재해싱이 일어난다. 그 결과 부하율은 1보다 작아지게 된다. 사용자가 강제로 rehash()를 호출하여 재해싱을 할 수 있다. max_load_factor(float)함수를 사용하여
기본값이 1로 되어 있는 부하율 최대 한계치를 변경할 수도 있다. 부하율이 지정된 최대 한계치를 넘어가면 재해싱이 발생한다.

unordered_map과 unordered_set은 중복 키를 허용하지 않는다. 만약 중복된 값을 저장하고 싶다면 unorered_multiset또는 unordered_multimap을 사용해야 한다.
이 두 컨테이너의 삽입 함수는 주어진 주어진 키가 이미 존재하는지를 검사하지 않는다. 또한 이들 컨테이너는 특정 키에 해당하는 모든 값을 얻을 수 있는 기능도
지원한다.

STL은 c++에서 지원하는 모든 기본 데이터 타입에 대한 해시 함수를 제공한다. 따라서 앞서 언급했던 컨테이너에서 사용자 정의 클래스 또는 구조체를 키 타입으로 사용하
려면 std네임스페이스 안에서 해시 함수를 구현해야 한다. 그러나 해시 함수를 만드는 것은 그다지 좋은 생각이 아니다. 해시 함수는 고도의 수학적 능력을 요구하기 때문이다.

# 사용자 정의 자료형을 담은 unordered_map,set

사용자 정의 자료형을 unordered_map과 set에 저장하려면 해당 객체를 비교할 수 있는 비교자가 필요하다. 두 자료구조는 std::hash와 std::equal_to를 사용하여 해시 함수의 기능과 동등성 비교를 수행한다. 기본 자료형은 해시 함수와 동등성 비교가 잘 작동하지만 사용자 정의 자료형은 해시 함수와 동등성 비교를 직접 정의해야 한다.
equal_to 함수를 사용자 정의 자료형으로 템플릿 특수화하여 비교자로 전달한다.

동등성 검사는 set과 map에서 중요한 역할을 한다.

해시 테이블에서 원하는 요소를 찾을 때에도 동등성 검사가 필요하다. 또한 중복 방지를 위해서
동등성 검사를 사용한다.

또한 사용자 정의 해시 함수가 필요하다. 사용자 정의 해시 함수는 boost::hash_combine()을 사용하면 된다. 이 함수는 여러 개의 키에 대한 해시 값을 결합하는 데에 사용된다. 즉 사용자 정의 객체는 여러 개의 멤버 변수를 가질 수 있다. 이 멤버 변수들 각각이 키에 해당하고, 이에 대응하는 해시 값을 combine을 이용하여 하나로 결합한다. 따라서 객체에 대한 해시 값이 하나로 결합된다.

template<class T>
inline void hash_combine(std::size_t seed,const T& value);
seed는 해시 값을 담을 변수로, 일반적으로 다른 해시 값을 초기값으로 사용한다.
value는 결합하고자 하는 해시 값을 의미한다.
즉 value의 해시 값을 결합하여 seed로 전달한다.
template <class T>
inline void hash_combine(std::size_t& seed, const T& value) {
    seed ^= boost::hash<T>()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
boost::hash_combine 함수를 사용하면 여러 해시 값을 단일 해시 값으로 결합하여 새로운 해시 값을 생성할 수 있으며, 이를 사용하여 복합적인 키를 만들 수 있다.

해시 함수로 MD5,SHA-1.SHA-256 같은 복잡한 암호화 함수도 사용할 수 있다. 이들 알고리즘은 매우 복잡하며 파일 같은 다양한 종류의 데이터를 입력으로 받을 수 있다.
암호화 함수를 사용할 경우, 해시 값으로부터 원본 데이터를 알아내는 역해싱(reverse hashing)이 매우 어렵기 때문에 보안 시스템에서 사용되기도 한다.

# 2023.7.27

# Binary Search

주어진 시퀀스가 정렬되어 있을 때 원소를 검색하는 효과적인 방법중 하나인 이진 검색이다.

1.전체 시퀀스 범위를 range로 설정합니다.
2.현재 range의 가운데 원소를 M이라고 하고, M과 N을 비교한다.
3.만약 M=N이면, 시퀀스에서 N을 찾은 것이므로 검색을 중단한다.
4.그렇지 않으면 아래 두 규칙에 따라 range를 수정한다.
5.만약 range에 한 개보다 많은 원소가 남아 있다면 2단계로 넘어간다.
6.그렇지 않으면 주어진 시퀀스에 N이 존재하지 않는 것이며, 검색을 종료한다.

# Merge_sort

많은 원소로 구성된 전체 집합을 작은 크기의 부분집합으로 나눠 각각을 정렬하고, 정렬된 부분집합을 오름차순 또는 내림차순 순서를 유지하면서 합치는 방식이다.

# Quick_sort

병합 정렬이 대용량의 데이터를 정렬하는 것이 목적이라면, 퀵 정렬은 평균 실행 시간을 줄이는 것이 목적이다. 퀵 정렬의 기본 아이디어는 병합 정렬과 같다. 즉 원본
입력 배열을 작은 크기의 부분 배열로 나누고, 각 부분 배열을 정렬한 후, 그 결과를 합쳐서 전체 정렬된 배열을 생성한다. 다만 퀵 정렬의 핵심 연산은 병합이 아니라
분할이다.
퀵 정렬은 반복자를 이용하여 시퀀스 원소의 위치를 교환하는 작업을 수행하기 때문에 병합 작업이 필요 없다.

# Linear time selection

부분 문제를 2개가 아닌 여러 개로 분할하는 방법이다.
다음은 분할 연산의 순서이다.

1.입력 벡터 V가 주어지면 여기서 i번째로 작은 원소를 찾으려고 한다.
2.입력 벡터 V를 V1,V2,V3,V4,V(n/5) 로 분할한다. 각각의 부분 벡터 Vi는 다섯 개의 원소를 가지고 있고 마지막 V(n/5)는 다섯 개 이하의 원소를 가질 수 있다.
3.각각의 Vi를 정렬한다.
4.각각의 Vi에서 중앙값 mi를 구하고, 이를 모아서 집합 M을 생성한다.
5.집합 M에서 중앙값 q를 찾는다.
6.q를 피벗으로 삼아 전체 벡터 V를 L과 R의 두 벡터로 분할한다.
7.이러한 방식으로 분할하면 부분 벡터 L은 q보다 작은 원소만을 가지고, 부분 벡터 R은 q보다 큰 원소만을 포함하게 된다. 이 때 L에 (k-1)개의 원소가
있다고 한다.
만약 i = k이면 q는 V의 i번째 원소이다.
만약 i<k이면, V=L로 설정하고 1단계로 이동한다.
만약 i>k이면, V=R로 설정하고 1단계로 이동한다.

# 2023 07 28

# Quickselect (linear time search algorithm 보완)

이전에 작성했던 linear time selection 코드는 제대로 적용이 되지 않는 문제가 있어
더 보완된 코드를 작성한다. 
linear time selection 코드와 마찬가지로 부분 시퀀스로 분할하여 각 시퀀스의 중앙값을 구한 후
중앙값들의 중앙값을 구하여 피벗으로 삼는다. 그 후 전체 시퀀스를 해당 피벗을 중심으로 
partition함수로 분할한다. 결과로, 왼쪽에는 피벗보다 같거나 작은 원소들이 위치하고 오른쪽은 피벗보다 큰 원소들이 위치한다. 그리고 피벗의 위치를 리턴한다. 피벗의 위치와 k를 비교한 후 크기에 따라 오른쪽이나 왼쪽 시퀀스를 다시 분할하면서 k번째 값을 찾는다. 이번 아이디어는 퀵 정렬을 사용하지 않았고 partition을 이용하여 효과적인 선택이 가능하다. (아이디어는 퀵 정렬에서 가져왔다)

# STL Divide & conquer function

c++표준 라이브러리 함수중에 분할 정복 패러다임 알고리즘을 구현할 때 사용할 수 있는 유용한 함수들의 정리이다.

# Mersenne twister & random_device

메르센 트위스터와 random_device로 시드를 랜덤하게 초기화한 후 난수를 생성하는 코드이다.
난수를 이용하여 야구 게임과 롯또 숫자 생성기를 만들었다.

# 2023.07.30

# Circle_list

원형 연결 리스트의 구현이다. 복사 생성자, 이동 생성자, initializer_list를 이용한 생성자를 정의했고, 반복자인 iterator클래스를 내부에 정의했다.
노드들의 구조가 원형으로 연결되어 있어 마지막 노드와 head노드가 next,prev 포인터로 연결되어 있다.

# Single linked list

단일 연결 리스트의 구현이다. 리스트의 앞쪽에서만 push,pop이 가능하며 반복자와 이동, 복사 생성자를 정의했다.
