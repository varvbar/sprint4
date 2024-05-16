#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Lang {
    string name;
    int age;
};


int main() {
   vector<Lang> langs = {{"Python"s, 29}, {"Java"s, 24}, {"C#"s, 20}, {"Ruby"s, 25}, {"C++"s, 37}};
   // Выведите первый язык, начинающийся на J, используя алгоритм find_if
    auto it = find_if(langs.begin(), langs.end(), 
                    [](const Lang& words) {
                        if(words.name[0] == 'J'){
                            return true;
                        }
                        else {
                            return false;
                        }
                    });

   cout << it->name << ", "s << it->age << endl;
}