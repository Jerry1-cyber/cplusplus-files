//
// Created by jerry on 2024/7/13.
//
#include <iostream>
using std::size_t;
using std::stack;
#ifndef BSTREE_H
#define BSTREE_H
namespace mycode {
    enum PosfromBSTree {
        left,
        right,
    };
    template<class T>
    struct BSTreeNode {
        T _val;
        BSTreeNode<T>* _left;
        BSTreeNode<T>* _right;
        BSTreeNode(const T& val = T(),BSTreeNode<T>* left = nullptr,BSTreeNode<T>* right = nullptr):\
    _val(val),_left(left),_right(right){};
    };
    template<class T,class Compare = std::less<T>>
    class BSTree {
    public:
        typedef BSTreeNode<T> Node;
        explicit BSTree():_root(nullptr),_size(0){}
        Node* getRoot() { return _root; }
        void clear(Node* root = getRoot());//这里为什么要单独调用getRoot(),这是因为这里还来不及调用this指针

        bool push(const T& val);
        bool pop(const T& val);
        size_t size() const { return _size; }
        bool empty() const { return _root == nullptr; }
        Node* Find(cosnt T& src);
        ~BSTree(){ clear(); _root = nullptr; _size = 0; }
    private:
        Node* _root;
        size_t _size;
        Compare cmp;//创建仿函数可以方便整个类进行调用
    };
    template<class T,class Compare = std::less<T>>
    void BSTree<T,Compare>::clear(BSTreeNode<T>* root) {
        if(root == nullptr) return;
        clear(root->_left);
        clear(root->_right);
        delete root;
        root = nullptr;
    }
    template<class T,class Compare = std::less<T>>
    bool BSTree<T,Compare>::push(const T& val) {
        ::mycode::PosfromBSTree position = ::mycode::left;
        Node* parent = nullptr;
        Node* cur = _root;
        if(cur == nullptr) {
            _root = new Node(val);
            return true;
        }
        while(cur) {
            if(cmp(val,cur->_val)) {
                parent = cur;
                cur = cur->_left;
                position = ::mycode::left;
            }else if(cmp(cur->_val,val)) {
                parent = cur;
                cur = cur->_right;
                position = ::mycode::right;
            }
            else return false;
        }
        cur = new Node(val);
        if(position == left) parent->_left = cur;
        else parent->_right = cur;
        return true;
    }
    template<class T,class Compare = std::less<T>>
    bool BSTree<T,Compare>::pop(const T& val) {
        Node* cur = _root;
        if(cur == nullptr) return false;
        while(cur) {
            if(cmp(val,cur->_val)) {
                cur = cur->_left;
            }
            else if(cmp(cur->_val,val)) {
                cur = cur->_right;
            }
            else {

            }
        }
        return false;

    }
}
#endif //BSTREE_H
