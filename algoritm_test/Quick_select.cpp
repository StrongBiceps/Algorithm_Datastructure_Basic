#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

/* 1��° ���Ҹ� ����ϱ� ������ cout ���
* 2 7 3
* 2 3 7
* 
* 2 44 7 3 45 1 2 1 5 45 5 1 3
* 2 3 1 2 1 1 3 45 5 45 5 7 44
* 
* 2 1
* 1 2
* 
* 1 2 1 2 3 1
* 1 1 1 2 3 1
* 
* 1 1
* 1 1
* 1     <-(1��° ����)
* 
* �������� �κ� �������� ������ �� �߾Ӱ��� �߾Ӱ��� �ǹ����� ��Ƽ� partition�� ���� ������ ��
* ã�� ���Ұ� �ǹ����� �۴ٸ� ������ �ٽ� �����ϰ�, ũ�ٸ�
* �������� �ٽ� �����ϸ鼭 ���� ã�´�.
* ���� Ž���� ������ ������ ���δ�.
* 
*  �߰������� ������ ���Ƴ��� ����
* 
*  �߰������� ������ ���Ƴ��� �� quickselect_pos�� ������ ���Ƴ��� ��ŭ�� index�� �����Ѵ�.
   quickselect_pos���� �߾Ӱ����� �߾Ӱ��� index�� return�Ѵ�. ���� �߾Ӱ��� �߾Ӱ��� quickselect_pos����
   ���ϱ� ���ؼ� ������ ���� ���Ƴ��� ȣ���ϴ� ���̴�.

   �׷��� ���� ���� ȣ������ quickselect�� pivot�� �߾Ӱ��� �߾Ӱ����� �������� partition�� ȣ���Ͽ� 
   �߾Ӱ��� �߾Ӱ��� �������� �������� �����Ѵ�. 

   ������ �Ϻ��� ���� �ʾƵ� k�� �����ϸ� n��° ���� ��Ȯ�� ������ ����
   �ǹ��� �������� ������ �߱� ������ �ǹ� ������ ������ �ǹ����� �۰� �������� �ǹ����� ũ�Ƿ�
   ���� �ǹ��� ��ġ�� index�� ��Ȯ�� n��° ��ġ�̴�. ���� �̷��� ������ �������� �ʾƵ� n��° ���Ҹ�
   ���� �� �ִ�.

   quickselect �˰����� o(N)�ð� ���⵵�� ������. ���� quickselect�� ������� �ʰ� k��° ���Ҹ� ã�´ٸ�
   �������� �����ϰ� ã�ƾ� �Ѵ�. �׷��� ���� ���� �˰����� o(n log n)�� �ð� ���⵵�� ������. ����
   k��° ���Ҹ� ã�� ���� �����ٴ� ������ �ִ� ���̴�.
*/
template <typename T>
T quickselect_pos(std::vector<T>& data, size_t start, size_t end, size_t k);

template <typename T>
size_t sort_and_get_median(std::vector<T>& data, size_t start, size_t end) {
    //sort(data.begin(),data.end()) -> data.end()�������� ����
    //���� data.begin()+end���� �����Ϸ��� 1�� ���ؾ� ��.
    std::sort(data.begin() + start, data.begin() + end + 1);
    return (start + end) / 2;
}

template <typename T>
size_t choose_pivot(std::vector<T>& data, size_t start, size_t end) {
    // ������ ���� ũ�Ⱑ 5 ���϶�� �׳� �����ؼ� �߰����� ã�´�.
    if (end - start < 5) {
        return sort_and_get_median(data, start, end);
    }

    size_t current = start;
    for (size_t i = start; i <= end; i += 5) {
        // ������ ���� ũ�Ⱑ 5 �� �׷����� �ɰ��� �� �׷��� �߰����� ã�´�.
        size_t med_pos = sort_and_get_median(data, i, std::min(i + 4, end));

        // �� �׷��� �߰����� �� ������ �����´�.
        //quickselect_pos�� �̿��Ͽ� �߰����� ���� ����ϱ� �����̴�.
        //quickselect_pos�Լ��� �����͸� ���� ���·� �����Ƿ�, �߰������� �� ������ �� �־�� �Ѵ�.
        //���� quickselect�� �ƴ� quickselect_pos�� ����ϴ� ������ choose_pivot�Լ��� �ǹ��� ���� �ƴ϶�
        //�ǹ��� ��ġ�� �����ؾ� �ϱ� �����̴�.

        std::iter_swap(data.begin() + current, data.begin() + med_pos);
        current++;
    }

    return quickselect_pos(data, start, current - 1, (current + start - 1) / 2);
}

template <typename T>
size_t partition(std::vector<T>& data, size_t start, size_t end,
    size_t pivot_pos) {
    // �츮�� ��Ƽ�� �˰����� �ǹ��� �� �������� �ִٰ� �����ϹǷ�, �� �ǹ���
    // �� �ڷ� �ű��.
    std::iter_swap(data.begin() + end, data.begin() + pivot_pos);

    const auto& pivot = data[end];
    size_t current_small_loc = start;  // ������ ������

    // i �� ������ ������ ������ �Ѵ�.
    //�ǹ��� ��� ���Ѵ�. �ǹ����� ũ�� ��ȯ�� ���� �ʴ´�. ������ �ǹ��� �� ũ�� 
    //�ǹ����� ���� ���� �������� ������ ���ؼ� ���ݱ��� �����ĿԴ� ����(�ε����� current_small_loc��)
    //�� ��ȯ�Ѵ�. ���� data[current_small_loc]�� �ǹ����� ũ�Ƿ� ū ���Ҵ� ���������� ���ĵȴ�.
    //�� ��ȯ �Ŀ��� current_small_loc�� �ϳ� �������� ���� ���Ҹ� ����Ű�� �Ѵ�.(data[current_small_loc]�� swap���� ���� ���� �ǹ����� �����Ƿ�)
    cout << endl;
    for (size_t i = start; i <= end; ++i)
    {
        cout << data[i] << " ";
    }
    cout << endl;
    for (size_t i = start; i <= end; i++) {
        if (data[i] <= pivot) {
            std::swap(data[current_small_loc++], data[i]);
        }
    }
     for (size_t i = start; i <= end; ++i)
    {
        cout << data[i] << " ";
    }
     cout << endl;
    return current_small_loc - 1;
}

template <typename T>
T quickselect_pos(std::vector<T>& data, size_t start, size_t end, size_t k) {
    if (start == end) {
        return start;
    }

    // �ǹ��� �ϳ� ����.
    size_t pivot_pos = choose_pivot(data, start, end);
    // ��Ƽ�� �� �ǹ��� ��ġ�� �޴´�.
    pivot_pos = partition(data, start, end, pivot_pos);

    if (pivot_pos == k) {  // ����!
        return pivot_pos;
    }
    else if (pivot_pos < k) {  // ã���� �ϴ� ���Ҵ� �ǹ� �����ʿ� �ִ�.
        return quickselect_pos(data, pivot_pos + 1, end, k);
    }
    else {  // ã���� �ϴ� ���Ҵ� �ǹ� ���ʿ� �ִ�.
        return quickselect_pos(data, start, pivot_pos - 1, k);
    }
}

template <typename T>
T quickselect(std::vector<T>& data, size_t start, size_t end, size_t k) {
    if (start == end) {
        return data[start];
    }

    // �ǹ��� �ϳ� ����.
    size_t pivot_pos = choose_pivot(data, start, end);

    // ��Ƽ�� �� �ǹ��� ��ġ�� �޴´�.
    pivot_pos = partition(data, start, end, pivot_pos);

    if (pivot_pos == k) {  // ����!
        return data[pivot_pos];
    }
    else if (pivot_pos < k) {  // ã���� �ϴ� ���Ҵ� �ǹ� �����ʿ� �ִ�.
        return quickselect(data, pivot_pos + 1, end, k);
    }
    else {  // ã���� �ϴ� ���Ҵ� �ǹ� ���ʿ� �ִ�.
        return quickselect(data, start, pivot_pos - 1, k);
    }
}

int main() {
    vector<int> S1{45, 1, 3, 1, 2, 3, 45, 5, 1, 2, 44, 5, 7};

    for (register int i = 0; i < 13; ++i)
    {
        cout << quickselect(S1, 0, 12, i) << " ";
    }

    return 0;
}