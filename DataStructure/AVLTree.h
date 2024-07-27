//
// Created by jerry on 2024/7/26.
//

#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <cassert>
using std::pair;
using std::cin;
using std::cout;
using std::string;
using std::less;

//这里我们写的AVL树还是key / value型
namespace mycode {
    enum PosfromAVLTree {
        AVLleft,
        AVLright,
    };
    template <class K,class V>
    struct  AVLTreeNode {
        AVLTreeNode<K,V>* _parent;
        AVLTreeNode<K,V>* _left;
        AVLTreeNode<K,V>* _right;
        int _bf = 0;//balance factor 平衡因子
        pair<K,V> _kv;
        explicit AVLTreeNode(const pair<K,V> kv,AVLTreeNode<K,V>* parent = nullptr,AVLTreeNode<K,V>* left = nullptr,\
            AVLTreeNode<K,V>* right = nullptr):_parent(parent),_left(left),_right(right),_kv(kv){}

    };
    template <class K,class V,class Compare = std::less<K>>
    class AVLTree {
        typedef AVLTreeNode<K,V> Node;
    public:
        explicit AVLTree() = default;
        Node* getRoot() { return _root; }
        void RotateLeft(Node* parent);
        void RotateRight(Node* parent);
        void RotateAll(Node* parent);//提供一份通用的Rotate的旋转的模版
        void clear(Node* root);
        bool insert(const pair<K,V>& kv);
        void inorderHelper(Node* root) const {
            if(root == nullptr) return;
            inorderHelper(root->_left);
            cout << root->_kv.first << " ";
            inorderHelper(root->_right);
        }
        void inorder() const {inorderHelper(_root);}
        ~AVLTree(){ clear(_root); }
    private:
        Node* _root = nullptr;
        size_t _size = 0;
        Compare _cmp;
    };
    template <class K,class V,class Compare>
    bool AVLTree<K,V,Compare>::insert(const pair<K,V>& kv) {
        ::mycode::PosfromAVLTree position = ::mycode::PosfromAVLTree::AVLleft;
        Node* parent = nullptr;
        Node* cur = _root;
        if(cur == nullptr) {
            _root = new AVLTreeNode<K,V>(kv);
            _size++;
            return true;
        }
        while(cur) {
            if(_cmp(kv.first,cur->_kv.first)) {
                parent = cur;
                cur = cur->_left;
                position = ::mycode::PosfromAVLTree::AVLleft;
            }else if(_cmp(cur->_kv.first,kv.first)) {
                parent = cur;
                cur = cur->_right;
                position = ::mycode::PosfromAVLTree::AVLright;
            }
            else return false;
        }
        cur = new Node(kv);
        cur->_parent = parent;
        if(position == ::mycode::PosfromAVLTree::AVLleft) parent->_left\
    = cur;
        else parent->_right = cur;
        _size++;//插入成功后考虑平衡的问题
        //更新平衡因子
        while(parent) {
            if(cur == parent->_left) { --parent->_bf; }
            else { ++parent->_bf; }
            if(parent->_bf == 0) break;
            else if(parent->_bf == -1 || parent->_bf == 1) {
                cur = parent;
                parent = parent->_parent;
            }else if(parent->_bf == -2 || parent->_bf == 2) {
                //进行旋转
                //分为左旋 + 右旋 + 先左旋后右旋 + 先右旋后左旋
                RotateAll(parent);
                break;
            }else assert(false);//断言结束
        }

        return true;
    }
    template<class K, class V, class Compare>
    void AVLTree<K, V, Compare>::RotateLeft(Node *parent) {
        //左旋的原理
        //由于某个根节点的平衡因子本身处于1的状态，这个时候如果我们在右子树进行push的时候
        //平衡被打破，进行右旋，将rightChild的left作为parent的rightchild并且将parent作为
        //rightChild的左节点同时将rightchild作为新的根节点
        //
        //右旋我们要考虑几个关键的点
        //1.设置的时候不要忘了我们这里是三叉链的结构
        //2.rCLeftChild可能是nullptr
        //3.旋转之后,parent 和 rightChild 的 balancefactor都应该变成0
        Node* tmp = parent->_parent;//记录根节点
        Node* rightChild = parent->_right;
        Node* rCLeftChild = rightChild->_left;
        parent->_right = rCLeftChild;
        rightChild->_left = parent;
        parent->_parent = rightChild;
        if(rCLeftChild) rCLeftChild->_parent = parent;//由于rCleftChild可能为空
        rightChild->_parent = tmp;//他的parent是parent的parent
        if(tmp) {
            if(parent == tmp->_left) tmp->_left = rightChild;
            else tmp->_right = rightChild;
        }
        parent->_bf = rightChild->_bf = 0;
    }
    template<class K, class V, class Compare>
    void AVLTree<K, V, Compare>::RotateRight(Node *parent) {
        Node* tmp = parent->_parent;
        Node* leftChild = parent->_left;
        Node* lCRightChild = leftChild->_right;
        parent->_left = lCRightChild;
        leftChild->_right = parent;
        parent->_parent = leftChild;
        if(lCRightChild) lCRightChild->_parent = parent;
        leftChild->_parent = tmp;
        if(tmp) {
            if(parent == tmp->_left) tmp->_left = leftChild;
            else tmp->_right = leftChild;
        }
        parent->_bf = leftChild->_bf = 0;
    }
    template <class K,class V,class Compare>
    void AVLTree<K,V,Compare>::clear(Node* root) {
        if(root == nullptr) return;
        clear(root->_left);
        clear(root->_right);
        delete root;
        _size = 0;
    }
    template <class K,class V,class Compare>
    void AVLTree<K,V,Compare>::RotateAll(Node* parent) {
        if(parent->_bf == 2 && parent->_right->_bf == 1)
            RotateLeft(parent);//左单旋
        else if(parent->_bf == -2 && parent->_left->_bf == -1)
            RotateRight(parent);
        else if(parent->_bf == 2 && parent->_right->_bf == -1) {
            int bfOfRCChild = parent->_right->_left->_bf;
            RotateRight(parent->_right);
            RotateLeft(parent);
            //这里唯一的问题就是旋转之后处理balancefactor的问题
            parent = parent->_parent;//parent在这里发生了变化
            if(bfOfRCChild == 1) {
                parent->_left->_bf = -1;
            } else if(bfOfRCChild == -1)
                parent->_right->_bf = 1;
            else if(bfOfRCChild == 0) assert(true);
            else assert(false);
        }
        else if(parent->_bf == -2 && parent->_left->_bf == 1) {
            int bfOfLCChild = parent->_left->_right->_bf;
            RotateLeft(parent->_left);
            RotateRight(parent);
            parent = parent->_parent;
            if(bfOfLCChild == 0) assert(true);
            else if(bfOfLCChild == 1) parent->_left->_bf = -1;
            else if(bfOfLCChild == -1) parent->_right->_bf = 1;
            else assert(false);
        }
        Node* rootparent = _root->_parent;//这里还需要更新一下root
        while(rootparent) {
            _root = _root->_parent;
            rootparent = rootparent->_parent;
        }
    }



}

#endif //AVLTREE_H
