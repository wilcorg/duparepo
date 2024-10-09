#ifndef CONSTBIMAPITERATOR_HPP
#define CONSTBIMAPITERATOR_HPP

#include <iterator>
#include <map>

template<typename Key, typename Value>
class ConstBiMapIterator
{
public:
    using value_type = const std::pair<Key, Value>;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    explicit ConstBiMapIterator(typename std::map<Key, Value*>::iterator it) : it_(it), pair_() {}

    reference operator*() const
    {
        pair_ = std::pair<Key, Value>(it_->first, *(it_->second));
        return pair_;
    }

    pointer operator->() const
    {
        pair_ = std::pair<Key, Value>(it_->first, *(it_->second));
        return &pair_;
    }

    ConstBiMapIterator& operator++()
    {
        ++it_;
        return *this;
    }

    ConstBiMapIterator operator++(int)
    {
        ConstBiMapIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    ConstBiMapIterator& operator--()
    {
        --it_;
        return *this;
    }

    ConstBiMapIterator operator--(int)
    {
        ConstBiMapIterator tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const ConstBiMapIterator& other) const
    {
        return it_ == other.it_;
    }

    bool operator!=(const ConstBiMapIterator& other) const
    {
        return it_ != other.it_;
    }

private:
    typename std::map<Key, Value*>::const_iterator it_;
    mutable std::pair<Key, Value> pair_;
};

#endif //CONSTBIMAPITERATOR_HPP