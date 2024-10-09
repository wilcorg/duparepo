#ifndef BIMAP_HPP
#define BIMAP_HPP

#include <bimap/BiMapIterator.hpp>
#include <bimap/ConstBiMapIterator.hpp>

#include <iostream>

template<typename Key, typename Value>
class BiMap
{
public:
    using iterator = BiMapIterator<Key, Value>;
    using const_iterator = ConstBiMapIterator<Key, Value>;

    BiMap() = default;
    ~BiMap() = default;

    bool exists(const std::pair<Key, Value>& pair) const;

    void insert(const std::pair<Key, Value>& pair);
    void remove(const std::pair<Key, Value>& pair);

    Value& atKey(const Key& key) const;
    Key& atValue(const Value& value) const;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

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

template<typename Key, typename Value>
typename BiMap<Key, Value>::iterator BiMap<Key, Value>::begin()
{
    return iterator(key_valuePtr_.begin());
}

template<typename Key, typename Value>
typename BiMap<Key, Value>::iterator BiMap<Key, Value>::end()
{
    return iterator(key_valuePtr_.end());
}

template<typename Key, typename Value>
typename BiMap<Key, Value>::const_iterator BiMap<Key, Value>::begin() const
{
    return iterator(key_valuePtr_.begin());
}

template<typename Key, typename Value>
typename BiMap<Key, Value>::const_iterator BiMap<Key, Value>::end() const
{
    return iterator(key_valuePtr_.end());
}

template<typename Key, typename Value>
typename BiMap<Key, Value>::const_iterator BiMap<Key, Value>::cbegin() const
{
    return const_iterator(key_valuePtr_.begin());
}

template<typename Key, typename Value>
typename BiMap<Key, Value>::const_iterator BiMap<Key, Value>::cend() const
{
    return const_iterator(key_valuePtr_.end());
}
#endif  // BIMAP_HPP
