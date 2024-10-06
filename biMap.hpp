#ifndef BIMAP_HPP
#define BIMAP_HPP

#include <map>
#include <iterator>

template<typename Key, typename Value>
class BiMap {
public:
    BiMap() = default;

    bool exists(const std::pair<Key, Value>& pair) const;

    void insert(const std::pair<Key, Value>& pair);
    void remove(const std::pair<Key, Value>& pair);

    Value& atKey(const Key& key) const;
    Key& atValue(const Value& value) const;

    // Forward Iterator Declaration
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = std::pair<const Key&, const Value&>;
        using pointer = value_type*;
        using reference = value_type&;

        iterator(typename std::map<Key, Value*>::iterator it) : it_(it)
            , current_ {std::cref(it_->first), std::cref(*(it_->second))} {}

        // Dereference operator
        reference operator*() const {
            // current_ = std::make_pair(std::cref(it_->first), std::cref(*(it_->second)));
            return current_;
        }

        pointer operator->() const {
            return &(operator*());
        }

        // Pre-increment
        iterator& operator++() {
            ++it_;
            return *this;
        }

        // Post-increment
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        // Equality
        bool operator==(const iterator& other) const {
            return it_ == other.it_;
        }

        // Inequality
        bool operator!=(const iterator& other) const {
            return it_ != other.it_;
        }

    private:
        typename std::map<Key, Value*>::iterator it_;
        mutable value_type current_;
    };

    iterator begin() {
        return iterator(key_valuePtr_.begin());
    }

    iterator end() {
        return iterator(key_valuePtr_.end());
    }

private:
    bool existsKey_(const Key& key) const;
    bool existsValue_(const Value& value) const;

    void insert_(const std::pair<Key, Value>& pair);
    void remove_(const std::pair<Key, Value>& pair);

    std::map<Value, Key*> value_keyPtr_;
    std::map<Key, Value*> key_valuePtr_;
};

/*
 * Template implementation
 */

template<typename Key, typename Value>
bool BiMap<Key, Value>::exists(const std::pair<Key, Value>& pair) const
{
    return value_keyPtr_.contains(pair.second) || key_valuePtr_.contains(pair.first);
}

template<typename Key, typename Value>
void BiMap<Key, Value>::insert(const std::pair<Key, Value>& pair)
{
    if (not exists(pair)) {
        insert_(pair);
    } else {
        std::cerr << "bimap: attempt to insert duplicate pair" << std::endl;
    }
}

template<typename Key, typename Value>
void BiMap<Key, Value>::remove(const std::pair<Key, Value>& pair)
{
    if (exists(pair)) {
        remove_(pair);
    } else {
        std::cerr << "bimap: attempt to remove non-existing pair" << std::endl;
    }
}

template<typename Key, typename Value>
Value& BiMap<Key, Value>::atKey(const Key& key) const
{
    if (existsKey_(key)) {
        return *key_valuePtr_[key];
    } else {
        throw std::runtime_error("bimap: key not found");
    }
}

template<typename Key, typename Value>
Key& BiMap<Key, Value>::atValue(const Value& value) const
{
    if (existsValue_(value)) {
        return *value_keyPtr_[value];
    } else {
        throw std::runtime_error("bimap: value not found");
    }
}

template<typename Key, typename Value>
bool BiMap<Key, Value>::existsKey_(const Key& key) const
{
    return key_valuePtr_.contains(key);
}

template<typename Key, typename Value>
bool BiMap<Key, Value>::existsValue_(const Value& value) const
{
    return value_keyPtr_.contains(value);
}

template<typename Key, typename Value>
void BiMap<Key, Value>::insert_(const std::pair<Key, Value>& pair)
{
    const auto keyIter = value_keyPtr_.insert({pair.second, nullptr}).first;
    auto* valPtr = const_cast<Value*>(&keyIter->first);
    const auto valIter = key_valuePtr_.insert({pair.first, valPtr}).first;
    auto* keyPtr = const_cast<Key*>(&valIter->first);
    value_keyPtr_[pair.second] = keyPtr;
}

template<typename Key, typename Value>
void BiMap<Key, Value>::remove_(const std::pair<Key, Value>& pair)
{
    key_valuePtr_.erase(pair.first);
    value_keyPtr_.erase(pair.second);
}

#endif  //BIMAP_HPP
