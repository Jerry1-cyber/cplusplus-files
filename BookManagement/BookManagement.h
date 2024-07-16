//
// Created by jerry on 2024/7/1.
//

#ifndef BOOKMANAGEMENT_H
#define BOOKMANAGEMENT_H
// #include <iostream>

#include <vector>
#include <cassert>
#include <windows.h>
#include <stack>
#include <list>
#include <fstream>
#include "BSTree.h"


void setpos(int x, int y);
void slideconsor();
enum system {
	leave = 1,
	in = 2,
};

struct BookInfor {
	BookInfor(string name = string(),string type = string(),string writer = string()):
		_name(name),_type(type),_writer(writer),_system(in)
	{}
	string _name;
	string _type;
	string _writer;
	enum system _system = ::in;//状态，是否被借阅
	friend ostream& operator<<(ostream& out, const BookInfor& rbi);
};
ostream& operator<<(ostream& out, const BookInfor& rbi);
struct TreeNode {
	BookInfor _val;
	TreeNode* _left;
	TreeNode* _right;
	TreeNode(const BookInfor& val = BookInfor(), TreeNode* left = nullptr, \
		TreeNode* right = nullptr):_val(val),_left(left),_right(right)
	{}
};//建立搜索二叉树的结构
class BSTree {//我们将名字作为key来进行搜索二叉树的建立
public:
	BSTree() :_head(nullptr), _size(0) {}


	void set(TreeNode* root, TreeNode* newnode);//通过_name作为key建立搜索二叉树
	void push(const BookInfor& src);//这里的push函数实际上是通过set函数进行实现的
	bool pop(const string& name);//管理员在删除的时候直接通过名字进行删除即可
	const BookInfor* search(const string& name) const;//由于这里的查找函数我们
	//没有提供修改的权限，所以这里返回的指针是const修饰的
	//这里由于如果没有找到，返回一个nullptr,这也是这里我们将指针作为返回值的原因

	void traverBSTree();//深度优先遍历二叉树
	int getheight(TreeNode* root) const {
		if(root == nullptr) return 0;
		return std::max(getheight(root->_left),getheight(root->_right)) + 1;
	}
	TreeNode* leftRotate(TreeNode* root);//左旋

	TreeNode* rightRotate(TreeNode* root);//右旋
	void pushAllBookInforHelper(vector<BookInfor>& rvbi,TreeNode* root);
	bool pushAllBookInfor(vector<BookInfor>& rvbi);
	TreeNode* balanceBST(TreeNode* root);
	void  BalanceBST();//平衡二叉树AVL树,将我们建立的搜索二叉树进行平衡化
	void Destroy();
	~BSTree() { Destroy(); }
private:
	TreeNode* _head;
	size_t _size;
};

class BookManagement {
public:
	const vector<string>& getString() const { return _vstr; }
	const list<BSTree>& getSearchTree() const { return _vST; }
	vector<string>& getString() { return _vstr; };
	list<BSTree>& getSearchTree() { return _vST; }
	void pushnewtype(const string& type);
	void traverBSTree_by_type();
	bool pushAllBookInfor(vector<BookInfor>& rvbi);
	bool clear();//清除里面的所有的内容
	void getBalance();
private:
	list<BSTree> _vST;//搜索二叉树数组
	vector<string> _vstr;//类型数组，他的下标和二叉树中对应的类型匹配
};
class Users {
public:
	Users(string username = string(),string id = string()):_username(username)
		,_id(id)
	{}
	const BookInfor* usersearch(const BookManagement& BMa,const string& type,\
	const string& name) const;//
	bool operator>=(const Users& usr) const { return _username >= usr._username; }//这里设置这个函数的目的是，在BSTree中
	//默认的greater函数只是return left < right,所以我们这里需要对<符号进行重载
	bool operator==(const Users& usr) const { return ((_username == usr._username) && (_id == usr._id) );}
	Users& operator=(const Users& usr) { _username = usr._username ; _id = usr._id; return *this;}

	bool operator<(const Users& usr) const { return _username < usr._username;}
	bool operator<=(const Users& usr) const { return operator<(usr) || operator==(usr); }
	bool operator>(const Users& usr) const { return !operator<=(usr); }
	bool borrow(BookManagement& BMa, const string& type, const string& name);
	bool retBook(BookManagement& bma);
	//由于书本本身的种类很少，这里没有必要再写一个搜索二叉树
	//这里我觉得这里加上type这个接口你们的图形化好些一点
	virtual void push(BookManagement& BMa, const string& type, const BookInfor& BI) {};
	virtual void pop(BookManagement& BMa, const string& type, const string& name) {};
	bool operator==(const Users& usr) { return _username == usr._username && _id == usr._id;}
	void setBookPtr(const BookInfor* pbi) { _borrow = pbi; }
protected:
	string _username;
	string _id;
	const BookInfor* _borrow = nullptr;
};
class Manager :public Users {
public:
	Manager(string username = string(),string id = string()):
		Users(username,id)
	{}
	virtual void push(BookManagement& BMa,const string& type,const BookInfor& BI);
	virtual void pop(BookManagement& BMa,const string& type,const string& name);//push和pop是Manager独有的权限
	bool operator==(const Manager& rma) { return _username == rma._username && _id == rma._id; }
protected:
};

#endif //BOOKMANAGEMENT_H
