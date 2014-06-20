#include "sort.h"

using namespace std;

template <class T>
bool merge(vector<T> &array, vector<T> &buffer, size_t l, size_t r, size_t m) {
    if (l == r)
        return true;
    for (unsigned int i = l; i <= m; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    for (unsigned int i = m + 1; i <= r; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    cout.flush();
    size_t count_l = l,count_r = m + 1;
    int i = 0;
    while (count_l <= m && count_r <= r) {
        while (array[count_l] <= array[count_r] && count_l <= m)
            buffer[i++] = array[count_l++];
        while (array[count_r] <= array[count_l] && count_r <= r)
            buffer[i++] = array[count_r++];
    }
    if (count_r > r && count_l <= m) {
        while (count_l <= m)
            buffer[i++] = array[count_l++];
    }
    for (int j = 0; j < i; j++)
        array[j + l] = buffer[j];
    return true;
}

template <class T>
void merge_sort (vector<T> &array, vector<T> &buffer, size_t l, size_t r, my::threadpool &thpool,
                 unsigned int priority, std::shared_ptr<my::Data<bool>> result) {
    if (r == l) {
        thpool.add<bool>(priority, result, merge<T>, array, l, r, r);
        return;
    }
    size_t m = (r + l) / 2;
    std::shared_ptr<my::Data<bool>> left(new my::Data<bool>()), right(new my::Data<bool>());
    merge_sort(array, l, m, thpool, priority + 1, left);
    merge_sort(array, m + 1, r, thpool, priority + 1, right);
//    left->get(); right->get();
//    thpool.add<bool>(priority, result, merge<T>, array, l, r, m);
    merge<T>(array, l, r, m);
}

template <class T>
void sort (vector<T> &array) {
    my::threadpool thpool;
    std::shared_ptr<my::Data<bool>> result(new my::Data<bool>());
    vector<T> buffer;
    buffer.resize(array.size());
    merge_sort(array, buffer, 0, array.size() - 1, thpool, 1, result);
    result->get();
}
