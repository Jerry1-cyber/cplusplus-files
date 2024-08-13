//
// Created by jerry on 2024/8/12.
//

#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H
#include "Harsh.h"
using std::forward;

namespace mycode {
    template <class K,class harsh = std::hash<K>>
    class unordered_set {
    public:
        struct SetKeyOfT {
            K&& operator()(K&& key){ return std::forward<K>(key);}
        };
        typedef typename Harsh_bucket::HarshTable<K,const K,SetKeyOfT,harsh>::iterator iterator;
        typedef typename Harsh_bucket::HarshTable<K,const K,SetKeyOfT,harsh>::const_iterator const_iterator;
        pair<iterator,bool> insert(K&& key) { return _hb.insert(std::forward<K>(key)); }
        bool erase(K&& key) { return _hb.erase(std::forward<K>(key)); }
        iterator find(K&& key) { return _hb.find(std::forward<K>(key)); }
        iterator begin() { return _hb.begin(); }
        iterator end() { return _hb.end(); }
        const_iterator begin() const { return _hb.begin(); }
        const_iterator end() const { return _hb.end(); }

    private:
        Harsh_bucket::HarshTable<K,K,SetKeyOfT,harsh> _hb;
    };
}
#endif //UNORDERED_SET_H
