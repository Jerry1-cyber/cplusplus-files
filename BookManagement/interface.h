//
// Created by jerry on 2024/7/1.
//
//这个头文件的作用是提供一系列的函数的额接口
#ifndef INTERFACE_H
#define INTERFACE_H
#include "BookManagement.h"
class Connection{
public:
    Connection();//为了避免冲突，这个接口的类只允许被创建一次，否则会出现报错
    bool InitBookManagement(const string& rpos);//传递一个文件指针即可
    Users& InitUser(const string& name,const string& id);//注册新的用户
    Manager& InitManager(const string& name,const string& id);//注册管理员，用户没有权限
    Manager* Marigister(const string& name, const string& id);//这里实现的用户的登录
    Users* usrrigister(const string& name, const string& id);
    const BookInfor* search_by_usr(const Users& usr,const string& type,const string& name);//通过调用可以获得书籍的指针，没有就会返回空指针
    bool push_new_book(Manager& rma,const BookInfor& rbi);//管理员权限,书籍的增加，可以直接调用_mroot权限
    bool pop_old_book(Manager& rma,const string& type,const string& name);//书籍的删除
    bool usrborrow(const Users& usr, const string& type, const string& name);//借阅书籍的函数,由于这里Manager是Users的额继承
    //因此这里传递Manager的权限也是可以实现书本的借阅的,返回一个布尔值表示借阅是否成功
    size_t usersize() const { return _lur.size(); }//用户的人数
    size_t Managersize() const { return _vMa.size(); }//返回的是Manager的个数
    void the_connect_of_traverBSTree();//二叉树的中序遍历,以及深度优先遍历
    Manager& getRoot() {return _mroot; }
    bool clearUsr(const Users& rusr);//这两个接口是用户通过登录或注册获得自己的应用或者是指针，
    //在这里他有删除自己的权限,也可以理解为注销
    bool clearManager(const Manager& rma);//返回false就是没有该用户
    bool clearAllUser();//直接清空所有的用户的数据
    bool clearAllManager();
    bool clearAllBookInfor();//清除所有的图书的内容
    BookManagement& getManagement() { return _bma; }
private:
    BookManagement _bma;//直接建立一个图书馆管理系统
    mystl::BSTree<Users> _lur;
    vector<Manager> _vMa;
    Manager _mroot;//系统默认的管理员,你可以理解为root权限
protected:
    static int ConnectionSize;//这里用stactic控制着一个接口个数函数，这样我们可以保证的是Connection的类只能初始化一次
};
#endif //INTERFACE_H
