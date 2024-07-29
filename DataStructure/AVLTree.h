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
        int _bf = 0;//balance factor 平衡因子
        pair<K,V> _kv;
        AVLTreeNode<K,V>* _parent;
        AVLTreeNode<K,V>* _left;
        AVLTreeNode<K,V>* _right;


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
        void insertRotateAll(Node* parent);//提供一份通用的Rotate的旋转的模版
        // void eraseRotateAll(Node* parent);
        void clear(Node* root);
        bool insert(const pair<K,V>& kv);
        bool erase(const K& val);
        void inorderHelper(Node* root) const {
            if(root == nullptr) return;
            inorderHelper(root->_left);
            cout << root->_kv.first << " ";
            inorderHelper(root->_right);
        }
        void inorder() const {inorderHelper(_root);}
        ~AVLTree(){ clear(_root); }
        AVLTreeNode<K,V>* find(const K& val);
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
                insertRotateAll(parent);
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
        }else _root = rightChild;//这个位置也很重要，更新root节点别忘了
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
        }else _root = leftChild;
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
    void AVLTree<K,V,Compare>::insertRotateAll(Node* parent) {
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

    }
    // template<class K,class V,class Compare>
    // void AVLTree<K,V,Compare>::eraseRotateAll(Node* parent) {
    //     if(parent->_bf == 2) {
    //         if(parent->_right->_bf == 0) {
    //             RotateLeft(parent);
    //             parent->_bf = 1;
    //             parent->_parent->_bf = -1;
    //         }
    //         else if(parent->_right->_bf == 1) RotateLeft(parent);
    //         else if(parent->_right->_bf == -1) {
    //             int balanceFactor = parent->_right->_left->_bf;
    //             RotateRight(parent->_right);
    //             RotateLeft(parent);
    //             parent = parent->_parent;
    //             if(balanceFactor == 1) parent->_left->_bf = -1;
    //             else if(balanceFactor == -1) parent->_right->_bf = 1;
    //         }else assert(false);
    //     }else {
    //         if(parent->_left->_bf == 0) {
    //             RotateRight(parent);
    //             parent->_bf = -1;
    //             parent->_parent->_bf = 1;
    //         }else if(parent->_left->_bf == -1) RotateRight(parent);
    //         else if(parent->_left->_bf == 1) {
    //             int balanceFactor = parent->_left->_right->_bf;
    //             RotateLeft(parent->_left);
    //             RotateRight(parent);
    //             parent = parent->_parent;
    //             if(balanceFactor == 1) parent->_left->_bf = -1;
    //             else if(balanceFactor == -1) parent->_right->_bf = 1;
    //         }else assert(false);
    //     }
    // }

    template<class K,class V,class Compare>
    bool AVLTree<K,V,Compare>::erase(const K& val) {
        Node* beginParent = nullptr;//这个指针用于存放我们后续开始平衡是的开始的节点
        PosfromAVLTree dirct;
        if(_root == nullptr) return false;
        //1.找到删除的节点的位置，由于这里是三叉链的结构因此我们没有必要进行记录其他
        Node* cur = _root;
        while(cur) {
            if(cur == nullptr) return false;//这里说明没有找到
            else if(_cmp(val,cur->_kv.first)) cur = cur->_left;
            else if(_cmp(cur->_kv.first,val)) cur = cur->_right;
            else break;//找到了呗
        }
        if(cur == nullptr) return false;
        //2.首先进行删除的操作
        // 1.只有一个孩子或者没有孩子节点
        if(cur->_left == nullptr || cur->_right == nullptr) {
            Node* child = cur->_left == nullptr ? cur->_right : cur->_left;
            Node* parent = cur->_parent;
            if(parent == nullptr) //这里说明cur是根节点
            {
                _root = child;
                beginParent = nullptr;
            }
            else {
                if(cur == parent->_left) {
                    parent->_left = child;
                    dirct = AVLleft;
                }else {
                    parent->_right = child;
                    dirct = AVLright;
                }
                beginParent = parent;
            }
        }//直接将孩子链接到parent上即可
        else {//有两个孩子
            //首先需要找到后继结点
            Node* minRight = cur->_right;
            while(minRight->_left){ minRight = minRight->_left; }
            cur->_kv = minRight->_kv;
            beginParent = minRight->_parent;//这里的实际就是删除minRight
            if(minRight == beginParent->_right) {
                beginParent->_right = minRight->_right;
                dirct = AVLright;
            }
            else {
                beginParent->_left = minRight->_right;
                dirct = AVLleft;
            }
            if(minRight->_right) minRight->_right->_parent = beginParent;//链接成功

        }
        //删除成功开始实现平衡的旋转
        while(beginParent) {
            if(dirct == AVLleft) ++beginParent->_bf;
            else --beginParent->_bf;
            int balanceFactor = beginParent->_bf;
            if(balanceFactor == 1 || balanceFactor == -1) break;//说明只是从完全平衡变得有点偏差
            else if(balanceFactor == 0) {
                Node* child = beginParent;
                if(beginParent->_parent) beginParent = beginParent->_parent;//他不会对这一层产生任何的影响,但是会影响下一层
                else break;
                if(child == beginParent->_left) dirct = AVLleft;
                else dirct = AVLright;
            }else if(balanceFactor == 2 || balanceFactor == -2) {
                if(balanceFactor == 2) {
                    //右边出现过高的情况
                    Node* rightChild = beginParent->_right;
                    if(rightChild->_bf == 0) {
                        RotateLeft(beginParent);
                        beginParent->_bf = 1;
                        rightChild->_bf = -1;
                        break;
                    }
                    else if(rightChild->_bf == 1) {
                        RotateLeft(beginParent);
                    }else if(rightChild->_bf == -1) {
                        Node* rLChild = rightChild->_left;
                        int ret = rLChild->_bf;
                        RotateRight(rightChild);
                        RotateLeft(beginParent);
                        if(ret == 1) {
                            beginParent->_bf = -1;
                        }else if(ret == -1) {
                            rightChild->_bf = 1;
                        }else assert(true);
                    }
                    beginParent = beginParent->_parent;
                    if(beginParent->_parent == nullptr) break;
                    else {
                        if(beginParent == beginParent->_parent->_left) dirct = AVLleft;
                        else dirct = AVLright;
                        beginParent = beginParent->_parent;

                    }
                }else {
                    //左边出现过高的情况
                    Node* leftChild = beginParent->_left;
                    if(leftChild->_bf == 0) {
                        RotateRight(beginParent);
                        beginParent->_bf = 1;
                        leftChild->_bf = 1;
                        break;
                    }else if(leftChild->_bf == -1) RotateRight(beginParent);
                    else if(leftChild->_bf == 1) {
                        Node* lRChild = leftChild->_right;
                        int ret = lRChild->_bf;
                        RotateLeft(leftChild);
                        RotateRight(beginParent);
                        if(ret == 1) leftChild->_bf = -1;
                        else if(ret == -1) beginParent->_bf = 1;
                        else assert(true);
                    }
                    beginParent = beginParent->_parent;
                    if(beginParent->_parent == nullptr) break;
                    else {
                        if(beginParent == beginParent->_parent->_left) dirct = AVLleft;
                        else dirct = AVLright;
                        beginParent = beginParent->_parent;

                    }
                }
            }


        }
        return true;
    }
    template <class K,class V,class Compare>
    AVLTreeNode<K,V>* AVLTree<K,V,Compare>::find(const K& val) {
        Node* cur = _root;
        if(cur == nullptr) return nullptr;
        while(cur) {
            if(_cmp(val,cur->_kv.first)) cur = cur->_left;
            else if(_cmp(cur->_kv.first,val)) cur = cur->_right;
            else return cur;
        }
        return nullptr;
    }
}
//后面是测试代码
/////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "BSTree.h"
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <cmath>
using std::abs;
#include "AVLTree.h"
using std::make_pair;
#include <queue>
using std::queue;
#include <ctime>
using std::rand;
// void testBSTree() {
//     mycode::BSTree<int> bst;
//     std::vector<int> arr = {14,2,3,4,5,6,7,8,9,10};
//     for(auto e:arr) {
//         bst.push(e);
//     }
//     bst.inOrder(bst.getRoot());
//     std::cout << '\n';
//     bool ret = bst.pop(1);
//     if(ret) std::cout << "true" << std::endl;
//     else std::cout << "false" << std::endl;
// }
//
template <class K,class V>
pair<bool,int> isBalance(mycode::AVLTreeNode<K,V>* root) {
    if(root == nullptr) return make_pair(true,0);
    pair<bool,int> lhs = isBalance(root->_left);
    pair<bool,int> rhs = isBalance(root->_right);
    if(lhs.first == false || rhs.first == false) return make_pair(false,-1);
    else {
        if(abs(lhs.second - rhs.second) >= 2) {
            cout << root->_kv.first << "没有平衡" << std::endl;

            return make_pair(false,-1);

        }
        int ret = lhs.second > rhs.second ? (lhs.second + 1) : (rhs.second + 1);
        return make_pair(true,ret);
    }
}
template <class K,class V>
vector<vector<pair<K,V>>> getInorder(mycode::AVLTreeNode<K,V>* root) {
    typedef mycode::AVLTreeNode<K,V> Node;
    vector<vector<pair<K,V>>> vvp;
    queue<Node*> lque;
    queue<int> rque;
    if(root == nullptr) return vvp;
    lque.push(root);
    rque.push(0);
    while(!lque.empty()) {
        Node* head = lque.front();
        lque.pop();
        int height = rque.front();
        rque.pop();
        vvp.resize(height+1);
        vvp[height].push_back(head->_kv);
        if(head->_left) {
            lque.push(head->_left);
            rque.push(height+1);
        }
        if(head->_right) {
            lque.push(head->_right);
            rque.push(height+1);
        }
    }
    return vvp;
}
template <class InputPtr>
int getHeight(InputPtr* root) {
    if(root == nullptr) return 0;
    int left = getHeight(root->_left);
    int right = getHeight(root->_right);
    return left > right ? (left + 1) : (right + 1);
}
template <class K,class V>
bool isRightOfBF(mycode::AVLTreeNode<K,V>* root) {
    if(root == nullptr) return true;
    isRightOfBF(root->_left);
    isRightOfBF(root->_right);
    int leftHeight = getHeight(root->_left);
    int rightHeight = getHeight(root->_right);
    if(root->_bf != rightHeight - leftHeight) {
        cout << root->_kv.first << "处的平衡因子和实际不符合" << std::endl;
        return false;
    }
    return true;
}

using std::endl;
void testKeyValueTree() {
    mycode::AVLTree<int,int> avlii;
    // mycode::AVLTreeNode<int,int> n1(make_pair(1,1));
    // mycode::AVLTreeNode<int,int> n2(make_pair(2,1));
    // mycode::AVLTreeNode<int,int> n3(make_pair(3,1));
    // n1._left = &n2;
    // n2._left = &n3;
    // avlii.RotateRight(&n1);
    vector<int> arr = { 16,3,7,11,9,26,18,14,15};
    // vector<int> arr = {4,2,6,1,3,5,15,7,16,14};
    // for(auto e : arr){ avlii.insert({e,1}); }
    // avlii.inorder();
    //
    // cout << endl;

    enum { NUM = 1000000, };//num hack

    // vector<vector<pair<int,int>>> vvii = getInorder(avlii.getRoot());
    // for(int cols = 0;cols < vvii.size();cols++) {
    //     for(int lines = 0;lines < vvii[cols].size();lines++) {
    //         cout << vvii[cols][lines].first << " ";
    //     }
    //     cout << endl;
    // }


    for(int i = 0;i < 100;i++) { avlii.insert(make_pair(i,1));}
    isRightOfBF(avlii.getRoot());
    bool ret = avlii.erase(15);
    for(int i = 10;i < 90;i++) {
        avlii.erase(i);
        isRightOfBF(avlii.getRoot());

        cout << i << " :";
        if(isBalance(avlii.getRoot()).first == true) cout << "已经平衡" << endl;
        else cout << "未平衡" << endl;
    }
    // mycode::AVLTreeNode<int,int>* p = avlii.find(23);
    // cout << p->_bf << endl;
    // if(isBalance(p).first) cout << "该书平衡" << endl;
    // else cout << "不平衡" << endl;
    // vector<vector<pair<int,int>>> vvii = getInorder(avlii.getRoot());
    // for(int cols = 0;cols < vvii.size();cols++) {
    //     for(int lines = 0;lines < vvii[cols].size();lines++) {
    //         cout << vvii[cols][lines].first << " ";
    //     }
    //     cout << endl;
    // }
    // int leftHeight = getHeight(p->_left);
    // int rightHeight = getHeight(p->_right);
    // cout << leftHeight << " " << rightHeight << endl;
    // isRightOfBF(p);

}

//将0~99用AVL树的结构显示出来
int main() {

    testKeyValueTree();
    return 0;
}
#endif //AVLTREE_H
