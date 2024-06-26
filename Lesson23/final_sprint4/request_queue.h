#pragma once
#include "search_server.h"
#include "document.h"
#include <deque>
#include <vector>
#include <string>

class RequestQueue {
public:
    RequestQueue(const SearchServer& search_server);
    // сделаем "обёртки" для всех методов поиска, чтобы сохранять результаты для нашей статистики
    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate);
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
    const SearchServer& search_server_;
    int minutes_;
    int empty_results_;
    
    void AddRequest(int result);
};

template <typename DocumentPredicate>
std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
    // напишите реализацию
    const std::vector<Document> result_find = search_server_.FindTopDocuments(raw_query, document_predicate);
    AddRequest(static_cast<int> (result_find.size()));
    return result_find;
}