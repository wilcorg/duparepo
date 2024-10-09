#ifndef BIMAPITERATOR_HPP
#define BIMAPITERATOR_HPP

#include <iterator>
#include <map>

template<typename Key, typename Value>
class BiMapIterator
{
public:
    using value_type = std::pair<Key, Value>;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    explicit BiMapIterator(typename std::map<Key, Value*>::iterator it) : it_(it), pair_() {}

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

    BiMapIterator& operator++()
    {
        ++it_;
        return *this;
    }

    BiMapIterator operator++(int)
    {
        BiMapIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    BiMapIterator& operator--()
    {
        --it_;
        return *this;
    }

    BiMapIterator operator--(int)
    {
        BiMapIterator tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const BiMapIterator& other) const
    {
        return it_ == other.it_;
    }

    bool operator!=(const BiMapIterator& other) const
    {
        return it_ != other.it_;
    }

private:
    typename std::map<Key, Value*>::iterator it_;
    mutable std::pair<Key, Value> pair_;
};

#endif // BIMAPITERATOR_HPP