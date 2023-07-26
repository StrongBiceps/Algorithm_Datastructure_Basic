#include <boost/functional/hash.hpp>

struct car
{
	std::string model;
	std::string brand;
	int buildyear;
};

//model�� brand�� ���� Ű�̰�, ���� hash�Լ��� ���� �ؽ� ���� ����� ����
//������ ���� seed�� ���� �� seed�� �����Ѵ�. ������ �ؽ� ���� ���� ���յǾ�
//�ϳ��� �ؽ� ������ seed�� ����ȴ�. ���� ����� ���� �ؽ� �Լ��� carhasher������
//���յ� �ؽ� ���� ��µȴ�.
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

//�� ��ü�� ��� �񱳸� �����ϱ� ���� �����̴�.
struct carcomparator
{
	bool operator()(const car& vehicle1, const car& vehicle2) const
	{
		return (vehicle1.model == vehicle2.model) && (vehicle1.brand == vehicle2.brand);
	}
};

//����� ���� �ڷ����� ������ ����̴�.
std::unordered_set<car, carhasher, carcomparator> carSet;
std::unordered_map<car, std::string, carhasher, carcomparator> carDescriptionMap;