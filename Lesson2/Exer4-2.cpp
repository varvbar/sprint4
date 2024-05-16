#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
    // напишите реализацию
    string finder = {prefix};
  
    auto first_it = lower_bound(range_begin, range_end, finder);
    ++finder[0];
    auto last_it = lower_bound(first_it, range_end, finder);

    //auto [lower, upper] = equal_range(range_begin, range_end, prefix);

    return {first_it, last_it};
}

int main() {
    const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};
    const auto m_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    const auto p_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    cout << (p_result.first - begin(sorted_strings)) << " " << (p_result.second - begin(sorted_strings)) << endl;
    const auto z_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    cout << (z_result.first - begin(sorted_strings)) << " " << (z_result.second - begin(sorted_strings)) << endl;
    return 0;
}