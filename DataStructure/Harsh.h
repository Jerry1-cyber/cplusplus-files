//
// Created by jerry on 2024/8/3.
//

#ifndef HARSH_H
#define HARSH_H
#include <iostream>
#include <vector>
using namespace std;
namespace mycode {
    enum system {
        EXIST,
        DELETE,
        EMPTY,
    };
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
    template <>
    struct HarshTrans<string> {
        size_t operator()(const string& str) {
            size_t harsh = 0;
            for(auto e : str) {
                harsh += (size_t)(e);
            }
            return harsh;
        }
    };
    template <class K,class V>
    struct HarshDataType {
        HarshDataType(const pair<K,V>& kv = pair<K,V>()):\
        _kv(kv)
        {}
        enum system _status = EMPTY;
        pair<K,V> _kv;

    };
    template <class K,class V,class Harsh = HarshTrans<K>>
    class HarshTable {
    public:
        HarshTable() {
            _table.resize(10);
        }
        void resize(int size) {
            if(size > _size) {
                _table.resize(size);
            }
        }
        size_t size() { return _size; }
        bool insert(const pair<K,V>& kv) {
            if(find(kv.first)) return false;
            if((10 * _size) / _table.size() > 7) {
                HarshTable tmp;
                tmp.resize(_table.size() * 2);
                for(auto& e : _table) {
                    if(e._status != EMPTY) tmp.insert(e._kv);
                }
                _table.swap(tmp._table);
            }
            int harsh = _harshtrans(kv.first) % _table.size();
            while(_table[harsh]._status == EXIST) {
                harsh = (harsh+1) % _table.size();
            }
            _size++;
            _table[harsh]._kv = kv;
            _table[harsh]._status = EXIST;
            return true;
        }
        HarshDataType<K,V>* find(const K& val){
            int harsh = _harshtrans(val) % _table.size();
            while(_table[harsh]._status != EMPTY) {
                if(_table[harsh]._kv.first == val && _table[harsh]._status == EXIST)
                    return &_table[harsh];
                harsh = (harsh + 1) % _table.size();
            }
            return nullptr;
        }
        bool erase(const K& key) {
            HarshDataType<K,V>* node = find(key);
            if(node == nullptr) return false;
            else node->_status = DELETE;
            return true;
        }
    private:
        std::vector<HarshDataType<K,V>> _table;
        size_t _size = 0;//这里的size的意思是有效的数据的个数
        Harsh _harshtrans;
    };
}
namespace Harsh_bucket {//拉链法实现哈希桶
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
    template <class K,class V>
    struct HarshDataType {
        HarshDataType(const pair<K,V>& kv = pair<K,V>()):_kv(kv){}
        pair<K,V> _kv;
        HarshDataType<K,V>* _next =  nullptr;
    };
    template <class K,class V,class Harsh = HarshTrans<K>>
    class HarshTable {
    public:
        typedef HarshDataType<K,V>* Ptr;
        typedef HarshDataType<K,V> Node;
        HarshTable(){ _table.resize(10); }
        void insertHelper() {
            HarshTable tmp;
            tmp._table.resize(_table.size() * 2);
            for(auto& e : _table) {
                Ptr cur = e;
                while(cur) {
                    Ptr next = cur->_next;
                    size_t harsh = _harsh(cur->_kv.first) % tmp._table.size();
                    if(tmp._table[harsh] == nullptr) {
                        tmp._table[harsh] = cur;
                        cur->_next = nullptr;
                    }
                    else {
                        cur->_next = tmp._table[harsh];
                        tmp._table[harsh] = cur;
                    }
                    cur = next;
                 }
                 e = nullptr;
            }
            _table.swap(tmp._table);

        }

        bool insert(const pair<K,V>& kv) {
            if(find(kv.first)) return false;

            int harsh = _harsh(kv.first) % _table.size();
            Ptr newnode = new HarshDataType(kv);
            if(_table[harsh] == nullptr) _table[harsh] = newnode;
            else {
                newnode->_next = _table[harsh];
                _table[harsh] = newnode;
            }
            _size++;
            if((_size * 10) / _table.size() >= 10) insertHelper();
            return true;
        }
        ~HarshTable() {
            for(auto& e : _table) {
                Ptr cur = e;
                while(cur) {
                    Ptr next = cur->_next;
                    delete cur;
                    cur = next;
                }
               e = nullptr;
            }
        }
        Ptr find(const K& key) {
            size_t harsh = _harsh(key) % _table.size();
            Ptr cur = _table[harsh];
            while(cur) {
                if(cur->_kv.first == key) return cur;
                cur = cur->_next;
            }
            return nullptr;
        }
        bool erase(const K& key){
            if(find(key) == nullptr) return false;
            size_t harsh = _harsh(key) % _table.size();
            Ptr cur = _table[harsh];
            Ptr prev = nullptr;
            while(cur->_kv.first != key) {
                prev = cur;
                cur = cur->_next;
            }
            if(prev == nullptr) _table[harsh] = cur->_next;
            else prev->_next = cur->_next;
            delete cur;
            return true;
        }
    private:
        vector<HarshDataType<K,V>*> _table;
        size_t _size = 0;
        Harsh _harsh;
    };
}
#endif //HARSH_H
