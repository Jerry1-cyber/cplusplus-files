//
// Created by jerry on 2024/7/1.
//
//this BSTree is created by myself the function of it is to increase the speed of searching

#ifndef BSTREE_H
#define BSTREE_H
#include <iostream>
// using namespace std;//为了支持c++17,这里对命名空间std我不进行展开
using std::string;
using std::vector;
using std::list;
using std::stack;
using std::size_t;
using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using std::endl;
#include <stack>
namespace mystl {
	template <class T>
	struct TreeNode {
		T _val;
		TreeNode<T>* _left;
		TreeNode<T>* _right;
		TreeNode(const T& val, TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr) :\
			_val(val), _left(left), _right(right)
		{}
	};
	template <class T, class Compare = std::greater<T>>
	class BSTree {//搜索二叉树
	public:
		BSTree() :_head(nullptr), _size(0) {}
		~BSTree() {
			if (_head == nullptr) return;
			stack<TreeNode<T>*> sk;
			sk.push(_head);
			while (!sk.empty())
			{
				TreeNode<T>* root = sk.top();
				sk.pop();
				if (root->_left != nullptr) sk.push(root->_left);
				if (root->_right != nullptr) sk.push(root->_right);
				delete root;
			}
			_head = nullptr;
			_size = 0;
		}
		void set(TreeNode<T>* root, TreeNode<T>* newnode)
		{
			stack<TreeNode<T>*> sk;
			sk.push(root);
			while (!sk.empty()) {
				TreeNode<T>* head = sk.top();
				sk.pop();
				if (head->_left == nullptr && compare(head->_val, newnode->_val)) {
					head->_left = newnode;
					return;
				}
				else if (head->_right == nullptr && (!compare(head->_val, newnode->_val))) {
					head->_right = newnode;
					return;
				}
				if (compare(head->_val, newnode->_val)) sk.push(head->_left);
				else sk.push(head->_right);
			}
		}
		T& push(const T& src)
		{
			TreeNode<T>* newnode = new TreeNode<T>(src);
			if (_head == nullptr) _head = newnode;
			else {
				set(_head, newnode);
			}
			++_size;
			return newnode->_val;
		}
		bool pop(const T& src)
		{
			_size--;
			TreeNode<T>* parent = nullptr;
			TreeNode<T>* cur = _head;
			while (cur)
			{
				if (compare(src, cur->_val)) {
					parent = cur;
					cur = cur->_right;
				}
				else if (compare(cur->_val, src)) {
					parent = cur;
					cur = cur->_left;
				}
				else {
					if (cur->_left == nullptr) {
						if (cur == _head) _head = cur->_right;
						else {
							if (cur == parent->_left) parent->_left = cur->_right;
							else parent->_right = cur->_right;
						}
						delete cur;
						cur = nullptr;
					}
					else if (cur->_right == nullptr) {
						if (_head == cur) _head = cur->_left;
						else {
							if (cur == parent->_left) parent->_left = cur->_left;
							else parent->_right = cur->_left;
						}
						delete cur;
						cur = nullptr;
					}
					else {
						TreeNode<T>* minparent = cur;
						TreeNode<T>* min = cur->_right;
						while (min->_left)
						{
							minparent = min;
							min = min->_left;
						}
						std::swap(cur->_val, min->_val);
						if (minparent->_left == min) minparent->_left = min->_right;
						else minparent->_right = min->_right;
						delete min;
						min = nullptr;
					}
					return true;
				}
			}
			return false;
		}
		T* search(const T& src)
		{
			TreeNode<T>* cur = _head;
			while (cur)
			{
				if (cur->_val == src) return &(cur->_val);
				else if (compare(cur->_val, src)) cur = cur->_left;
				else cur = cur->_right;
			}
			return nullptr;
		}
		const T* search(const T& src) const {
			return const_cast<BSTree<T, Compare>&>(*this).search(src);
		}
		size_t size() const { return _size; }
		bool empty() const { return _size == 0; }
	private:
		TreeNode<T>* _head;
		std::size_t _size;
		Compare compare;//创建一个比较的类,实现仿函数
	};
}
#endif //BSTREE_H
