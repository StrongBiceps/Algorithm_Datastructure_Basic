#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

/* 1번째 원소를 출력하기 까지의 cout 출력
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
* 1     <-(1번째 원소)
* 
* 시퀀스를 부분 시퀀스로 분할한 후 중앙값의 중앙값을 피벗으로 삼아서 partition을 통해 분할한 뒤
* 찾는 원소가 피벗보다 작다면 왼쪽을 다시 분할하고, 크다면
* 오른쪽을 다시 분할하면서 값을 찾는다.
* 이진 탐색과 유사한 측면이 보인다.
*/
template <typename T>
T quickselect_pos(std::vector<T>& data, size_t start, size_t end, size_t k);

template <typename T>
size_t sort_and_get_median(std::vector<T>& data, size_t start, size_t end) {
    //sort(data.begin(),data.end()) -> data.end()이전까지 정렬
    //따라서 data.begin()+end까지 정렬하려면 1을 더해야 함.
    std::sort(data.begin() + start, data.begin() + end + 1);
    return (start + end) / 2;
}

template <typename T>
size_t choose_pivot(std::vector<T>& data, size_t start, size_t end) {
    // 데이터 셋의 크기가 5 이하라면 그냥 정렬해서 중간값을 찾는다.
    if (end - start < 5) {
        return sort_and_get_median(data, start, end);
    }

    size_t current = start;
    for (size_t i = start; i <= end; i += 5) {
        // 데이터 셋을 크기가 5 인 그룹으로 쪼개서 각 그룹의 중간값을 찾는다.
        size_t med_pos = sort_and_get_median(data, i, std::min(i + 4, end));

        // 각 그룹의 중간값을 맨 앞으로 가져온다.
        //quickselect_pos를 이용하여 중간값을 쉽게 계산하기 위함이다.
        //quickselect_pos함수가 데이터를 구간 형태로 받으므로, 중간값들이 한 군데에 모여 있어야 한다.
        //또한 quickselect가 아닌 quickselect_pos를 사용하는 이유는 choose_pivot함수가 피벗의 값이 아니라
        //피벗의 위치를 리턴해야 하기 때문이다.
        std::iter_swap(data.begin() + current, data.begin() + med_pos);
        current++;
    }

    return quickselect_pos(data, start, current - 1, (current + start - 1) / 2);
}

template <typename T>
size_t partition(std::vector<T>& data, size_t start, size_t end,
    size_t pivot_pos) {
    // 우리의 파티션 알고리즘은 피벗이 맨 마지막에 있다고 가정하므로, 고른 피벗을
    // 맨 뒤로 옮긴다.
    std::iter_swap(data.begin() + end, data.begin() + pivot_pos);

    const auto& pivot = data[end];
    size_t current_small_loc = start;  // 검은색 지시자

    // i 가 빨간색 지시자 역할을 한다.
    //피벗과 계속 비교한다. 피벗보다 크면 교환을 하지 않는다. 하지만 피벗이 더 크면 
    //피벗보다 작은 값은 왼쪽으로 보내기 위해서 지금까지 지나쳐왔던 원소(인덱스가 current_small_loc인)
    //와 교환한다. 따라서 data[current_small_loc]은 피벗보다 크므로 큰 원소는 오른쪽으로 정렬된다.
    //또 교환 후에는 current_small_loc를 하나 증가시켜 다음 원소를 가리키게 한다.(data[current_small_loc]은 swap으로 인해 이제 피벗보다 작으므로)
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

    // 피벗을 하나 고른다.
    size_t pivot_pos = choose_pivot(data, start, end);
    // 파티션 후 피벗의 위치를 받는다.
    pivot_pos = partition(data, start, end, pivot_pos);

    if (pivot_pos == k) {  // 빙고!
        return pivot_pos;
    }
    else if (pivot_pos < k) {  // 찾고자 하는 원소는 피벗 오른쪽에 있다.
        return quickselect_pos(data, pivot_pos + 1, end, k);
    }
    else {  // 찾고자 하는 원소는 피벗 왼쪽에 있다.
        return quickselect_pos(data, start, pivot_pos - 1, k);
    }
}

template <typename T>
T quickselect(std::vector<T>& data, size_t start, size_t end, size_t k) {
    if (start == end) {
        return data[start];
    }

    // 피벗을 하나 고른다.
    size_t pivot_pos = choose_pivot(data, start, end);

    // 파티션 후 피벗의 위치를 받는다.
    pivot_pos = partition(data, start, end, pivot_pos);

    if (pivot_pos == k) {  // 빙고!
        return data[pivot_pos];
    }
    else if (pivot_pos < k) {  // 찾고자 하는 원소는 피벗 오른쪽에 있다.
        return quickselect(data, pivot_pos + 1, end, k);
    }
    else {  // 찾고자 하는 원소는 피벗 왼쪽에 있다.
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