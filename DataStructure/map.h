//
// Created by jerry on 2024/7/31.
//

#ifndef MAP_H
#define MAP_H
#include "RBTree.h"
//map is based on the RBTree
namespace mycode {
    template <class K,class V,class Compare = std::less<K>>
    class map {
    public:
        typedef pair<K,V> PairKV;
        struct MapKOfT {
            const K& operator()(const PairKV& kv){ return kv.first; }
        };
        typedef RBTree<K,pair<K,V>,MapKOfT,Compare> _rb_Tree;
        typedef typename _rb_Tree::iterator iterator;
        typedef typename _rb_Tree::const_iterator const_iterator;

        bool insert(const pair<K,V>& kv) { return _rbt.insert(kv); }
        size_t size() const { return _rbt.size(); }
        iterator begin() { return _rbt.begin(); }
        iterator end() { return _rbt.end(); }
        const_iterator begin() const { return _rbt.begin(); }
        const_iterator end() const { return _rbt.end(); }
    private:
        RBTree<K,pair<K,V>,MapKOfT,Compare> _rbt;
    };
}
#endif //MAP_H
