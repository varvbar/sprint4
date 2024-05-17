#pragma once
#include "search_server.h"
#include "document.h"
#include <deque>
#include <vector>
#include <string>

class RequestQueue {
public:
    RequestQueue(const SearchServer& search_server) 
        :search_server_(search_server)
        , minutes_(0)
        , empty_results_(0)
    {
    }
    // сделаем "обёртки" для всех методов поиска, чтобы сохранять результаты для нашей статистики
    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
        // напишите реализацию
        const std::vector<Document> result_find = search_server_.FindTopDocuments(raw_query, document_predicate);
        AddRequest(static_cast<int> (result_find.size()));
        return result_find;
    }
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);
    std::vector<Document> AddFindRequest(const std::string& raw_query);
    int GetNoResultRequests() const;
private:
    struct QueryResult {
        // определите, что должно быть в структуре (метка времени и значение)
        int time;
        int results;
    };
    std::deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    int minutes_;
    int empty_results_;
    const SearchServer& search_server_;

    void AddRequest(int result){
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
};