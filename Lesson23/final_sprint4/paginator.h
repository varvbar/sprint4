#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "document.h"

template <typename Iterators>
class IteratorRange
{
public:
    IteratorRange() = default;
    IteratorRange(const Iterators begin, const Iterators end, const std::size_t page_size)
        :begin_(begin), end_(end), page_size_(page_size)
    {
    }
    Iterators begin()const {
                return begin_;
            }
    Iterators end()const {
                return end_;
            }
    std::size_t size()const {
                return page_size_;
            }
private:
    Iterators begin_,end_;
    std::size_t page_size_;
};

template <typename Iterator>
std::ostream& operator<< (std::ostream& out, const IteratorRange<Iterator>& iterator_range){
    for(auto i = iterator_range.begin(); i != iterator_range.end(); ++i){
        out << *i;
    }
    return out;
}

template <typename Iterator>
class Paginator
{
public:
    Paginator (const Iterator begin_doc, const Iterator end_doc, const std::size_t page_size)
    {
        std::size_t document_size = distance(begin_doc, end_doc);
        
        auto page_begin = begin_doc;
        auto page_end = page_begin + page_size;

        while (document_size >= page_size){
            pages_.push_back({page_begin, page_end, page_size});
            advance(page_begin, page_size);
            page_end = page_begin + page_size;
            document_size = distance(page_begin, end_doc);
        }
        
        if(distance(page_begin, end_doc) > 0){
            std::size_t dist = distance(page_begin, end_doc);
            pages_.push_back({page_begin, end_doc, dist});
        }
    } 
    auto begin()const {
            return pages_.begin();
        }
    auto end()const {
            return pages_.end();
        }
    std::size_t size()const {
            return pages_.size();
        }
private:
    std::vector<IteratorRange<Iterator>> pages_;
};

template <typename Container>
auto Paginate(const Container& c, std::size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}