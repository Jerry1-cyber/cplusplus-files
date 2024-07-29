//
// Created by jerry on 2024/7/13.
//
#include <iostream>
#include <stack>
using std::size_t;
using std::stack;
#ifndef BSTREE_H
#define BSTREE_H
namespace mycode {
    enum PosfromBSTree {
        left,
        right,
    };
    template<class T,class V>//这里改成了key / value 模型
    struct BSTreeNode {
        T _val;
        V _value;
        BSTreeNode<T,V>* _left;
        BSTreeNode<T,V>* _right;
        BSTreeNode(const T& val = T(),const V& value = V(),BSTreeNode<T,V>* left = nullptr,BSTreeNode<T,V>* right = nullptr):\
    _value(value),_val(val),_left(left),_right(right){};
    };
    template<class T,class V,class Compare = std::less<T>>
    class BSTree {
    public:
        typedef BSTreeNode<T,V> Node;
        explicit BSTree():_root(nullptr),_size(0){}
        Node* getRoot() { return _root; }
        void clear(Node* root);//这里为什么要单独调用getRoot(),这是因为这里还来不及调用this指针

        bool push(const T& val,const V& va);
        bool pop(const T& val);
        size_t size() const { return _size; }
        bool empty() const { return _root == nullptr; }
        Node* Find(const T& src);
        void inOrder(Node* root) const {
            if(root == nullptr) return;
            inOrder(root->_left);
            std::cout << root->_val << " ";
            inOrder(root->_right);
        }
        bool erase(const T& val);
        ~BSTree(){ clear(_root); _root = nullptr; _size = 0; }

    private:
        Node* _root;
        size_t _size;
        Compare cmp;//创建仿函数可以方便整个类进行调用
    };
    template<class T,class V,class Compare>
    void BSTree<T,V,Compare>::clear(Node* root) {
        if(root == nullptr) return;
        clear(root->_left);
        clear(root->_right);
        delete root;
        root = nullptr;
    }
    template<class T,class V,class Compare>
    bool BSTree<T,V,Compare>::push(const T& val,const V& va){
        ::mycode::PosfromBSTree position = ::mycode::PosfromBSTree::left;
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
                position = ::mycode::PosfromBSTree::left;
            }else if(cmp(cur->_val,val)) {
                parent = cur;
                cur = cur->_right;
                position = ::mycode::PosfromBSTree::right;
            }
            else return false;
        }
        cur = new Node(val,va);
        if(position == ::mycode::PosfromBSTree::left) parent->_left = cur;
        else parent->_right = cur;
        _size++;
        return true;
    }
    template<class T,class V,class Compare>
    bool BSTree<T,V,Compare>::pop(const T& val){
        Node* parent = nullptr;
        Node* cur = _root;
        if(cur == nullptr) return false;
        while(cur) {
            if(cmp(val,cur->_val)) {
                parent = cur;
                cur = cur->_left;
            }
            else if(cmp(cur->_val,val)) {
                parent = cur;
                cur = cur->_right;
            }
            else {
                if(cur == nullptr) return false;//没找到直接返回false
                //找到节点
                //0个或者一个孩子的情况可以统一考虑
                if(cur->_left == nullptr) {
                    if(parent == nullptr) _root = cur->_right;
                    else {
                        if(cur == parent->_left) parent->_left = cur->_right;
                        else parent->_right = cur->_right;
                    }
                }else if(cur->_right == nullptr) {
                    if(parent == nullptr) _root = cur->_left;
                    else {
                        if(cur == parent->_left) parent->_left = cur->_left;
                        else parent->_right = cur->_left;
                    }
                }else {
                    Node* minright = cur->_right;
                    while(minright->_left != nullptr) {
                        minright = minright->_left;
                    }
                    minright->_left = cur->_left;
                    if(parent == nullptr)
                        _root = cur->_right;
                    else {
                        if(cur == parent->_left) {
                            parent->_left = cur->_right;
                        }else parent->_right = cur->_right;
                    }

                }
                delete cur;
                return true;
            }
        }
        return false;

    }
    template<class T,class V,class Compare>
    typename BSTree<T,V,Compare>::Node* BSTree<T,V,Compare>::Find(const T& src) {
        Node* cur = _root;;
        if(cur == nullptr) return nullptr;//如果什么都没有肯定就是直接返回的是NULL
        while(cur) {
            if(cmp(src,cur->_val)) cur = cur->_left;
            else if(cmp(cur->_val,src)) cur = cur->_right;
            else return cur;
        }
        return nullptr;
    }
}
#endif //BSTREE_H
