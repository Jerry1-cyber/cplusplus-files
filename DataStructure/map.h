//
// Created by jerry on 2024/7/31.
//

#ifndef MAP_H
#define MAP_H
#include <unordered_map>

#include "RBTree.h"
//map is based on the RBTree
//but the main question is that we can't find a fit constractor to make iterator to fit const_iterator

namespace mycode {
    template <class K,class V,class Compare = std::less<K>>
    class map {
    public:
        explicit map() = default;
        typedef pair<K,V> PairKV;
        struct MapKOfT {
            const K& operator()(const PairKV& kv){ return kv.first; }
        };
        typedef RBTree<K,pair<K,V>,MapKOfT,Compare> _rb_Tree;
        typedef typename _rb_Tree::iterator iterator;
        typedef typename _rb_Tree::iterator const_iterator;

        bool insert(const pair<K,V>& kv) { return _rbt.insert(kv); }
        bool insert(const std::initializer_list<pair<K,V>>& il) { return _rbt.insert(il); }
        std::size_t size() const { return _rbt.size(); }
        iterator begin() { return _rbt.begin(); }
        iterator end() { return _rbt.end(); }
        const_iterator begin() const { return _rbt.begin(); }
        const_iterator end() const { return _rbt.end(); }
    private:
        RBTree<K,pair<K,V>,MapKOfT,Compare> _rbt;
    };

}
#endif //MAP_H
