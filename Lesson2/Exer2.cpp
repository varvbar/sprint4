#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void PrintSpacesPositions(string& str) {
    // напишите реализацию
    
    for(auto it = find(str.begin(), str.end(), ' '); it != str.end();){
         cout << distance(str.begin(),it) << endl;
         it = find(next(it), str.end(), ' ');
    }
}

int main() {
    string str = "He said: one and one and one is three"s;
    PrintSpacesPositions(str);
    return 0;
}