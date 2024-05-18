#include <vector>
#include <string>

#include "request_queue.h"
#include "search_server.h"

    // сделаем "обёртки" для всех методов поиска, чтобы сохранять результаты для нашей статистики
RequestQueue::RequestQueue(const SearchServer& search_server) 
        :search_server_(search_server)
        , minutes_(0)
        , empty_results_(0)
    {
    }
std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status) {
    // напишите реализацию
    const std::vector<Document> result_find = search_server_.FindTopDocuments(raw_query, status);
    AddRequest(static_cast<int> (result_find.size()));
    return result_find;
}
std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query) {
    // напишите реализацию
    const std::vector<Document> result_find = search_server_.FindTopDocuments(raw_query);
    AddRequest(static_cast<int> (result_find.size()));
    return result_find;
}
int RequestQueue::GetNoResultRequests() const { 
    // напишите реализацию
    return empty_results_;
}

void RequestQueue::AddRequest(int result){
    ++minutes_;
    while(!requests_.empty() && ((minutes_ - requests_.front().time) >= min_in_day_)){
        if(requests_.front().results == 0 && empty_results_ > 0){
            --empty_results_;
        }
        requests_.pop_front();
    }

    requests_.push_back({minutes_, result});
    if(result == 0){
        ++empty_results_;
    }
}