#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

template <typename Type>
class Stack {
public:
    void Push(const Type& element) {
        // напишите реализацию
        elements_.push_back(element);
    }
    void Pop() {
        // напишите реализацию
        elements_.pop_back();
    }
    const Type& Peek() const {
        // напишите реализацию
        return elements_.back();
    }
    Type& Peek() {
        // напишите реализацию
        return elements_[elements_.size()-1];
    }
    void Print() const {
        // напишите реализацию
        PrintRange(elements_.begin(), elements_.end());
    }
    uint64_t Size() const {
        // напишите реализацию
        return elements_.size();
    }
    bool IsEmpty() const {
        // напишите реализацию
        return elements_.empty();
    }

private:
    vector<Type> elements_;
};

template <typename Type>
class StackMin {
public:
    void Push(const Type& element) {
    // напишите реализацию метода
        if(elements_.IsEmpty()){
            elements_.Push(element);
            header_.push_back({element, element});
            return;
        }

        elements_.Push(element);
        if(element < PeekMin()){
            header_.push_back({element, element});
        }
        else{
            header_.push_back({element, PeekMin()});
        }
    }
    void Pop() {
    // напишите реализацию метода
        elements_.Pop();
        header_.pop_back();
    }
    const Type& Peek() const {
        return elements_.Peek();
    }
    Type& Peek() {
        return elements_.Peek();
    }
    void Print() const {
        elements_.Print();
    }
    uint64_t Size() const {
        return elements_.Size();
    }
    bool IsEmpty() const {
        return elements_.IsEmpty();
    }
    const Type& PeekMin() const {
    // напишите реализацию метода
        return header_.back().second;
    }
    Type& PeekMin() {
    // напишите реализацию метода
        return header_.back().second;
    }
private:
    Stack<Type> elements_;
    // возможно, здесь вам понадобится что-то изменить
    vector <pair<Type, Type>> header_;
};

template <typename Type>
class SortedSack {
public:
    void Push(const Type& element) {
        // напишите реализацию метода
        if(elements_.IsEmpty() || elements_.Peek() >= element){
            elements_.Push(element);
            return;
        }
        
        Type temp_var = elements_.Peek();
        elements_.Pop();
        Push(element);
        Push(temp_var);
    }
    void Pop() {
        // напишите реализацию метода
        if(elements_.IsEmpty()) {
            return;
        }
        elements_.Pop();
    }
    const Type& Peek() const {
        return elements_.Peek();
    }
    Type& Peek() {
        return elements_.Peek();
    }
    void Print() const {
        elements_.Print();
    }
    uint64_t Size() const {
        return elements_.Size();
    }
    bool IsEmpty() const {
        return elements_.IsEmpty();
    }
private:
    Stack<Type> elements_;
};

int main() {
    SortedSack<int> sack;
    vector<int> values(5);
    // заполняем вектор для тестирования нашего класса
    iota(values.begin(), values.end(), 1);
    // перемешиваем значения
    random_device rd;
    mt19937 g(rd());
    shuffle(values.begin(), values.end(), g);

    // заполняем класс и проверяем, что сортировка сохраняется после каждой вставки
    for (int i = 0; i < 5; ++i) {
        cout << "Вставляемый элемент = "s << values[i] << endl;
        sack.Push(values[i]);
        sack.Print();
    }
}