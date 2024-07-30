//
// Created by jerry on 2024/7/30.
//
//自建红黑树
#include <vector>
using std::vector;
#ifndef RBTREE_H
#define RBTREE_H
#include <iostream>
using std::size;
using std::pair;
namespace mycode {
    enum Color {
        Red,
        Black,
    };
    template <class K,class V>
    struct RBTreeNode {
        RBTreeNode(const std::pair<K,V>& kv,RBTreeNode<K,V>* left = nullptr\
            ,RBTreeNode<K,V>* right = nullptr,RBTreeNode<K,V>* parent = nullptr):\
        _kv(kv),_left(left),_right(right),_parent(parent)
        {}
        Color _col = Black;
        std::pair<K,V> _kv;
        RBTreeNode<K,V>* _left;
        RBTreeNode<K,V>* _right;
        RBTreeNode<K,V>* _parent;
    };
    template <class K,class V,class Compare = std::less<K>>
    class RBTree {
    public:
        typedef RBTreeNode<K,V> Node;
        size_t size() const { return _size; }
        void RotateLeft(Node* parent);
        void RotateRight(Node* parent);
        bool insert(const pair<K,V>& kv);
        Node* getRoot() { return _root; }
        pair<bool,int> isTheRightRBTree(Node* root) {
            if(root == nullptr) return std::make_pair(true,1);
            pair<bool,int> lhs = isTheRightRBTree(root->_left);
            if(lhs.first == false) return std::make_pair(false,-1);
            pair<bool,int> rhs = isTheRightRBTree(root->_right);
            if(rhs.first == false) return std::make_pair(false,-1);
            if(lhs.second != rhs.second) return std::make_pair(false,-1);
            if(root->_col == Red) {
                if((root->_left && root->_left->_col == Red) || (root->_right && root->_right->_col == Red))
                    return {false,-1};
                return { true,rhs.second};
            }else return { true,rhs.second + 1};
        }
        void inorderHelper(Node* root,vector<Node*>& sk) {
            if(root == nullptr) {
                int blackSize = 0;
                for(auto& e : sk) {
                    std::cout << e->_kv.first << " ";
                    if(e->_col == Black) {
                        std::cout << "Black ";
                        blackSize++;
                    }
                    else std::cout << "Red ";
                }
                std::cout << "nullptr " << blackSize << std::endl;
                return;
            }
            if(root->_left) sk.push_back(root->_left);
            inorderHelper(root->_left,sk);
            if(root->_left) sk.pop_back();
            if(root->_right) sk.push_back(root->_right);
            inorderHelper(root->_right,sk);
            if(root->_right) sk.pop_back();
        }
        void inorder() {
            vector<Node*> sk;
            sk.push_back(_root);
            inorderHelper(_root,sk);
        }
    private:
        Node* _root = nullptr;
        std::size_t _size = 0;
        Compare _cmp;
    };
    template <class K,class V,class Compare>
    bool RBTree<K,V,Compare>::insert(const pair<K,V>& kv) {

        enum RBDirct {
            left,
            right,
        };
        enum RBDirct rb_dirct = left;
        Node* parent = nullptr;
        Node* cur = _root;
        if(cur == nullptr) {
            _root = new RBTreeNode<K,V>(kv);
            _size++;
            return true;
        }
        while(cur) {
            parent = cur;
            if(_cmp(kv.first,cur->_kv.first)) {
                cur = cur->_left;
                rb_dirct = left;
            }
            else if(_cmp(cur->_kv.first,kv.first)) {
                cur = cur->_right;
                rb_dirct = right;
            }
            else return false;
        }

        cur = new Node(kv);
        _size++;
        cur->_col = Red;//新创建节点如果不是根节点,直接给红色的节点
        //cur这里是新增的节点
        cur->_parent = parent;
        if(rb_dirct == left) parent->_left = cur;
        else parent->_right = cur;
        while(cur) {
            parent = cur->_parent;
            if(parent == nullptr) {
                cur->_col = Black;
                break;
            }else if(parent->_col == Black) break;
            Node* grandParent = parent->_parent;
            if(grandParent == nullptr) {
                parent->_col = Black;
                break;
            }else {
                Node* uncle = nullptr;
                if(parent == grandParent->_left) uncle = grandParent->_right;
                else uncle = grandParent->_left;
                if(uncle && uncle->_col == Red) {
                    parent->_col = uncle->_col = Black;
                    grandParent->_col = Red;
                    cur = grandParent;
                }else {//叔叔不存在 / 叔叔存在且为黑
                    if(uncle == nullptr) {
                        if(uncle == grandParent->_left) {
                            if(cur == parent->_right) {
                                RotateLeft(grandParent);
                                grandParent->_col = Red;
                                parent->_col = Black;
                            }
                            else {
                                RotateRight(parent);
                                RotateLeft(grandParent);
                                cur->_col = Black;
                                grandParent->_col = Red;
                            }

                        }
                        else {
                            if(cur == parent->_left) {
                                RotateRight(grandParent);
                                grandParent->_col = Red;
                                parent->_col = Black;
                            }
                            else {
                                RotateLeft(parent);
                                RotateRight(grandParent);
                                cur->_col = Black;
                                grandParent->_col = Red;
                            }
                        }

                    }else {
                        if(uncle == grandParent->_left) {
                            if(cur == parent->_right) {
                                RotateLeft(grandParent);
                                grandParent->_col = Red;
                                parent->_col = Black;
                            }
                            else {
                                RotateRight(parent);
                                RotateLeft(grandParent);
                                cur->_col = Black;
                                grandParent->_col = parent->_col = Red;
                            }
                        }else {
                            if(cur == parent->_left) {
                                RotateRight(grandParent);
                                grandParent->_col = Red;
                                parent->_col = Black;
                            }else {
                                RotateLeft(parent);
                                RotateRight(grandParent);
                                cur->_col = Black;
                                grandParent->_col = parent->_col = Red;
                            }
                        }
                    }
                    break;
                }
            }
        }

        // while(cur) {
        //     if(cur->_parent == nullptr) break;
        //     else if(cur->_parent->_col == Red) {
        //         parent = cur->_parent;
        //         if(parent->_parent == nullptr) parent->_col = Black;//这里说明parent是root
        //         else {
        //             Node* grandParent = parent->_parent;
        //             Node* uncle = nullptr;
        //             if(parent == grandParent->_left) uncle = grandParent->_right;
        //             else uncle = grandParent->_right;
        //             if(uncle == nullptr) {
        //                 if(uncle == grandParent->_left) RotateLeft(grandParent);
        //                 else RotateRight(grandParent);
        //                 parent->_col = Black;
        //                 grandParent->_col = Red;
        //                 cur = parent;
        //                 if(parent->_parent == nullptr) _root = parent;
        //                 break;
        //             }else if(uncle->_col == Red) {
        //                 parent->_col = uncle->_col = Black;
        //                 grandParent->_col = Red;
        //                 cur = grandParent;
        //             }else {
        //
        //             }
        //         }
        //     }else break;
        // }
        return true;
    }
    template<class K, class V, class Compare>
    void RBTree<K, V, Compare>::RotateLeft(Node *parent) {
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
        }else _root = rightChild;//这个位置也很重要，更新root节点别忘了
    }
    template<class K, class V, class Compare>
    void RBTree<K, V, Compare>::RotateRight(Node *parent) {
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
        }else _root = leftChild;
    }
}
#endif //RBTREE_H
