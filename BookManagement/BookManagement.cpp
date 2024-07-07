//
// Created by jerry on 2024/7/1.
//
#include "BookManagement.h"
void setpos(int x, int y)
{

}
void slideconsor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO Cursor_Infor = { 0 };
	GetConsoleCursorInfo(handle, &Cursor_Infor);
	Cursor_Infor.bVisible = false;
	SetConsoleCursorInfo(handle, &Cursor_Infor);
}
void SearchTree::set(TreeNode* root, TreeNode* newnode)
{
	/*if (root->_left == nullptr && root->_val._name >= newnode->_val._name)
	{
		root->_left = newnode;
		return;
	}
	else if (root->_right == nullptr && root->_val._name <= newnode->_val._name)
	{
		root->_right = newnode;
		return;
	}//这里是通过递归的实现代码
	if (root->_val._name > newnode->_val._name)
		set(root->_left, newnode);
	else
		set(root->_right, newnode);*/
	stack<TreeNode*> sk;
	sk.push(root);
	while (!sk.empty())
	{
		TreeNode* head = sk.top();
		sk.pop();
		if (head->_left == nullptr && head->_val._name >= newnode->_val._name) {
			head->_left = newnode;
			return;
		}
		else if (head->_right == nullptr && head->_val._name\
			<= newnode->_val._name) {
			head->_right = newnode;
			return;
		}
		if (head->_val._name > newnode->_val._name) sk.push(head->_left);
		else sk.push(head->_right);
	}
}
void SearchTree::push(const BookInfor& src)
{
	TreeNode* newnode = new TreeNode(src);
	if (_head == nullptr) _head = newnode;
	else {
		set(_head, newnode);
	}
	_size++;
}
bool SearchTree::pop(const string& name)
{
	_size--;
	TreeNode* parent = nullptr;
	TreeNode* cur = _head;
	while (cur)
	{
		if (cur->_val._name < name) {
			parent = cur;
			cur = cur->_right;
		}
		else if (cur->_val._name > name) {
			parent = cur;
			cur = cur->_left;
		}
		else {
			//开始删除
			//1.左为空
			//2.右为空
			//3.左右都不为空
			if (cur->_left == nullptr) {
				//判断当前节点是否是root节点,如果是,无法用parent
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
				TreeNode* minparent = cur;
				TreeNode* min = cur->_right;
				while (min->_left) {
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
const BookInfor* SearchTree::search(const string& name) const
{
	TreeNode* cur = _head;
	while (cur)
	{
		if (cur->_val._name == name) return &(cur->_val);
		else if (name < cur->_val._name) cur = cur->_left;
		else cur = cur->_right;
	}
	return nullptr;
}
ostream& operator<<(ostream& out, const BookInfor& rbi)
{
	out << "书名：" << rbi._name << "  类型：" << rbi._type << "  作者：" << rbi._type;
	if (rbi._system == in)
		out << "  该书未被借走";
	else
		out << "  该书已被借走";
	return out;
}
void BookManagement::pushnewtype(const string& type)
{
	for (auto& e : _vstr)
	{
		if (e == type) return;
	}
	_vstr.push_back(type);
	_vST.resize(_vST.size() + 1);
}
void BookManagement::traverBSTree_by_type() {
	list<SearchTree>::iterator it = _vST.begin();
	vector<string>::iterator _it = _vstr.begin();
	while(it != _vST.end()) {
		cout << *_it <<endl;
		++_it;
		(*it).traverBSTree();
		++it;
	}

}
void SearchTree::Destroy() {
	TreeNode* head = _head;
	if (head == nullptr) return;
	stack<TreeNode*> sk;
	sk.push(head);
	while (!sk.empty())
	{
		TreeNode* root = sk.top();
		sk.pop();
		if (root->_right) sk.push(root->_right);
		if (root->_left) sk.push(root->_left);
		delete root;
		root = nullptr;
	}
}
bool BookManagement::clear() {
	if(_vstr.size() == 0) return true;
	list<SearchTree>::iterator it = _vST.begin();
	while(it != _vST.end()) {
		(*it).Destroy();
		++it;
	}
	return true;
}

const BookInfor* Users::usersearch(const BookManagement& BMa,const string& type,\
const string& name) const
{
	vector<string>::const_iterator it = BMa.getString().begin();
	while(it != BMa.getString().end()) {
		if((*it) == type) break;
		++it;
	}

	if (it == BMa.getString().end()) return nullptr;//如果找不到那个种类，就返回空指针
	/*return BMa.getSearchTree()[it - BMa.getString().begin()].search(name);*/
	size_t size = it - BMa.getString().begin();
	list<SearchTree>::const_iterator const_it = BMa.getSearchTree().begin();
	while (size)
	{
		++const_it;
		--size;
	}
	return (*const_it).search(name);
}
void SearchTree::traverBSTree() {
	if(_head == nullptr) perror("your BSTree don't have any information");
	stack<TreeNode*> sk;
	sk.push(_head);
	while(!sk.empty()) {
		TreeNode* root = sk.top();
		sk.pop();
		const BookInfor& ret = root->_val;
		////
		///在这地方你可以对数据进行访问,ret就是你能获取的一个图书类型的应用,但是在这里你只有访问的额权限
		///你没有修改的权限,you can only use it with const
		cout<<ret<<endl;
		if(root->_right != nullptr) sk.push(root->_right);
		if(root->_left != nullptr) sk.push(root->_left);
	}

}

void Manager::push(BookManagement& BMa, const string& type,const BookInfor& BI) {
	if(usersearch(BMa,type,BI._name) == nullptr) return;//如果原本就含有这本书就不会再添加
	vector<string>::iterator it = BMa.getString().begin();
	while(it != BMa.getString().end()) {
		if((*it) == type) break;
		++it;
	}

    /*BMa.getSearchTree()[it - BMa.getString().begin()].push(BI);*/
	size_t size = it - BMa.getString().begin();
	list<SearchTree>::iterator Sit = BMa.getSearchTree().begin();
	while (size)
	{
		++Sit;
		--size;
	}
	(*Sit).push(BI);
	return;
}

void Manager::pop(BookManagement& BMa, const string& type,const string& name)
{
	vector<string>::iterator it = BMa.getString().begin();
	while(it != BMa.getString().end()) {
		if((*it) == type) break;
		++it;
	}

	size_t size = it - BMa.getString().begin();
	list<SearchTree>::iterator Sit = BMa.getSearchTree().begin();
	while (size)
	{
		++Sit;
		--size;
	}
	(*Sit).pop(name);
	return ;
}
bool Users::borrow(BookManagement& BMa, const string& type, const string& name) const
{
	BookInfor* ret = const_cast<BookInfor*>(usersearch(BMa, type, name));
	ret->_system = leave;
	return true;
}