#include <iostream>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
    // set<int>::const_iterator — тип итераторов для константного множества целых чисел
    auto lower = numbers.lower_bound(border);
    
    if(lower == numbers.begin()) {
        return lower;
    }
    if(lower == numbers.end()) {
        return prev(lower);
    }

    auto it = prev(lower);
    if(*lower == border){
         return lower;
    }
    else if((border - *it) > (*lower - border)) {
        return lower;
    }
    else return it;

}

int main() {
    set<int> numbers = {1, 4, 6};
    cout << *FindNearestElement(numbers, 0) << " " << *FindNearestElement(numbers, 3) << " "
         << *FindNearestElement(numbers, 5) << " " << *FindNearestElement(numbers, 6) << " "
         << *FindNearestElement(numbers, 100) << endl;
    set<int> empty_set;
    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
    return 0;
}