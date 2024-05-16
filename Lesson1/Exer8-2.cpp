#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <sstream>
#include <vector>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
    auto it = range_begin;
    bool is_first = true;
    while (range_end != it) {
        if (!is_first) {
            cout << " ";
        }
        is_first = false;
        cout << *it;
        ++it;
    }
    cout << endl;
}

template <typename RandomIt>
void FortElem(RandomIt range_begin, RandomIt range_end) {
    for (auto i = 0; i < range_end - range_begin; ++i) {
        bool forted = true;
        for (auto j = range_begin; j < range_end - (i + 1); ++j) {
            if (*(j + 1) < *j) {
                forted = false;
                swap(*j, *(j + 1));
            }
        }
        if (forted) {
            break;
        }
    }   
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    auto it = range_begin + (range_end - range_begin) / 2;
    vector first(range_begin, it);
    vector second(it, range_end);
    FortElem(first.begin(), first.end());
    FortElem(second.begin(), second.end());
    merge(first.begin(), first.end(), second.begin(), second.end(), range_begin, [] (const auto& left, const auto& right) {
        return left < right;
    });

}

int main() {
    vector<int> test_vector(10);
    // iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
    // Заполняет диапазон последовательно возрастающими значениями
    iota(test_vector.begin(), test_vector.end(), 1);

    // shuffle   -> https://ru.cppreference.com/w/cpp/algorithm/random_shuffle
    // Перемешивает элементы в случайном порядке
    random_device rd;
    mt19937 g(rd());
    shuffle(test_vector.begin(), test_vector.end(), g);
    
    // Выводим вектор до сортировки
    PrintRange(test_vector.begin(), test_vector.end());
    // Сортируем вектор с помощью сортировки слиянием
    MergeSort(test_vector.begin(), test_vector.end());
    // Выводим результат
    PrintRange(test_vector.begin(), test_vector.end());
    return 0;
}