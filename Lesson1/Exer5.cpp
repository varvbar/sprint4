#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

template <typename It>
auto MakeSet(It range_begin, It range_end) {
    return set(range_begin, range_end);
}
template <typename It>
auto MakeVector(It range_begin, It range_end){
    return vector(range_begin, range_end);
}

template <typename Container>
auto EraseAndPrint(Container& container, int position, int lhs, int rhs){
    container.erase(container.begin() + position);
    PrintRange(container.begin(), container.end());
    
    container.erase(container.begin() + lhs, container.begin() + rhs);
    PrintRange(container.begin(), container.end());
}

int main() {
    vector<string> langs = {"Python"s, "Java"s, "C#"s, "Ruby"s, "C++"s};
    EraseAndPrint(langs, 0, 0, 2);
    return 0;
}