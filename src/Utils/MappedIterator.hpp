#pragma once

#include <iterator>
#include <functional>
#include <memory>
#include <optional>

namespace MoonCrawler {
template <class Collection, typename ResultType>
class MappedIterator  {
    using CollectionIterator = typename Collection::iterator;
    using FunctionType = std::function<std::optional<ResultType>(typename CollectionIterator::value_type)>;

public:
    MappedIterator(Collection& collection, const FunctionType& function) :
        m_Iterator(collection.begin()), m_End(collection.end()), m_Function(std::move(function)), m_Collection(collection)
    {
        findNext();
    }

    void findNext() {
        bool isFound = false;

        while (!isFound && m_Iterator != m_End) {
            std::optional<ResultType> value = m_Function(*m_Iterator);

            if (value) {
                m_nextValue = *value;
                isFound = true;
                std::advance(m_Iterator, 1);
            }
            else {
                m_Iterator = m_Collection.erase(m_Iterator);
            }
        }

        m_hasValue = isFound;

        if (!m_hasValue) {
            m_nextValue = std::nullopt;
        }
    }

    ResultType next() {
        auto next_v = *m_nextValue;
        findNext();
        return next_v;
    }

    inline bool hasValue() {
        return m_hasValue;
    }
private:
    Collection& m_Collection;
    CollectionIterator m_Iterator;
    CollectionIterator m_End;
    FunctionType m_Function;

    bool m_hasValue;
    std::optional<ResultType> m_nextValue;
};
}
