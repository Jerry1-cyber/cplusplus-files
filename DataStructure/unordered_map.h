//
// Created by jerry on 2024/8/6.
//

#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H


#include "Harsh.h"

namespace mycode {
    template <class K>
    struct HarshTrans {
        size_t operator()(const K& key) const {
           return (size_t)key;
        }
    };

    template <class K,class V,class harsh = hash<K>>
    class unordered_map {
    public:
        struct MapKeyOfT
        {
            K&& operator()(pair<K, V>&& kv)
            {
                return std::forward<K>(kv.first);
            }
        };
        typedef typename Harsh_bucket::HarshTable<K,pair<const K,V>,MapKeyOfT,harsh>::iterator iterator;
        typedef typename Harsh_bucket::HarshTable<K,pair<const K,V>,MapKeyOfT,harsh>::const_iterator const_iterator;
        pair<iterator,bool> insert(pair<K,V>&& kv) { return _hb.insert(std::forward<pair<K,V>>(kv)); }//这里由于用了右值引用得加上forward
        bool erase(K&& key) { return _hb.erase(std::forward<K>(key)); }
        iterator find(K&& key) { return _hb.find(std::forward<K>(key)); }
        iterator begin() { return _hb.begin(); }
        iterator end() { return _hb.end(); }
        const_iterator begin() const { return _hb.begin(); }
        const_iterator end() const { return _hb.end(); }
        V& operator[](K&& key) {
            pair<iterator,bool> ret = _hb.insert(make_pair(key,V()));
            return ret.first->second;
        }

    private:
        Harsh_bucket::HarshTable<K,pair<const K,V>,MapKeyOfT,harsh> _hb;
    };
}




#endif //UNORDERED_MAP_H
