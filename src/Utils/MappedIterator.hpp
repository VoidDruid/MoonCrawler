#pragma once

#include <iterator>
#include <functional>
#include <memory>
#include <optional>

namespace MoonCrawler {
template <class Collection, typename ResultType>
class MappedIterator  {
    using CollectionIterator = typename Collection::iterator;
    using FunctionType = std::function<ResultType(typename CollectionIterator::value_type)>;

public:
    MappedIterator(Collection& collection, const FunctionType& function) :
        m_Iterator(collection.begin()), m_End(collection.end()), m_Function(std::move(function))
    {}

    std::optional<ResultType> next() {
        if (m_Iterator == m_End) {
            return std::nullopt;
        }

        ResultType value = m_Function(*m_Iterator);
        std::advance(m_Iterator, 1);
        return std::make_optional(value);
    }

private:
    CollectionIterator m_Iterator;
    CollectionIterator m_End;
    FunctionType m_Function;
};
}
