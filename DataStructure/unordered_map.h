//
// Created by jerry on 2024/8/6.
//

#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H


#include "Harsh.h"
namespace mycode {
    template <class K>
    struct HarshTrans {
        size_t operator()(const K& key) {
            size_t harsh = 0;
            int size = sizeof(key);
            char* ptr = (char*)&key;
            for(int i = 0;i < size;i++) {
                harsh += *ptr;
                ptr++;
            }
            return harsh;
        }
    };

    template <class K,class V,class harsh = HarshTrans<K>>
    class unordered_map {
    public:
        struct MapKeyOfT
        {
            const K& operator()(const pair<K, V>& kv)
            {
                return kv.first;
            }
        };
        typedef typename Harsh_bucket::HarshTable<K,pair<const K,V>,MapKeyOfT,harsh>::iterator iterator;
        typedef typename Harsh_bucket::HarshTable<K,pair<const K,V>,MapKeyOfT,harsh>::const_iterator const_iterator;
        pair<iterator,bool> insert(const pair<K,V>& kv) { return _hb.insert(kv); }
        bool erase(const K& key) { return _hb.erase(key); }
        iterator find(const K& key) { return _hb.find(key); }
        iterator begin() { return _hb.begin(); }
        iterator end() { return _hb.end(); }
        const_iterator begin() const { return _hb.begin(); }
        const_iterator end() const { return _hb.end(); }
        V& operator[](const K& key) {
            pair<iterator,bool> ret = _hb.insert(make_pair(key,V()));
            return ret.first->second;
        }

    private:
        Harsh_bucket::HarshTable<K,pair<const K,V>,MapKeyOfT,harsh> _hb;
    };
}




#endif //UNORDERED_MAP_H
