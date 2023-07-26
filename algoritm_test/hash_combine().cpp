#include <boost/functional/hash.hpp>

struct car
{
	std::string model;
	std::string brand;
	int buildyear;
};

//model과 brand는 각각 키이고, 내부 hash함수를 거쳐 해시 값을 계산한 다음
//연산을 거쳐 seed와 결합 후 seed에 적용한다. 각각의 해시 값이 서로 결합되어
//하나의 해시 값으로 seed에 적용된다. 따라서 사용자 정의 해시 함수인 carhasher에서는
//결합된 해시 값이 출력된다.
struct carhasher
{
	size_t operator()(const car& vehicle) const
	{
		size_t seed = 0;
		boost::hash_combine(seed, vehicle.model);
		boost::hash_combine(seed, vehicle.brand);
		return seed;
	}
};

//두 객체의 동등성 비교를 수행하기 위한 비교자이다.
struct carcomparator
{
	bool operator()(const car& vehicle1, const car& vehicle2) const
	{
		return (vehicle1.model == vehicle2.model) && (vehicle1.brand == vehicle2.brand);
	}
};

//사용자 정의 자료형을 저장한 모습이다.
std::unordered_set<car, carhasher, carcomparator> carSet;
std::unordered_map<car, std::string, carhasher, carcomparator> carDescriptionMap;