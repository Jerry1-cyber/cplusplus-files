//
// Created by jerry on 2024/7/1.
//
#include "interface.h"

bool Connection::InitBookManagement(const string& rpos)
{
    FILE* pf = fopen(rpos.c_str(), "r");
    char* book = new char[70];
    while (fgets(book, 70, pf))
    {
        BookInfor tmp;
        char* pch;
        pch = strtok(book, "   -\n\0");
        tmp._name += pch;
        if (tmp._name == string("") || tmp._name == string("end")) break;
        pch = strtok(NULL, "  -\n\0");
        tmp._type += pch;
        pch = strtok(NULL, "   -\n\0");
        tmp._writer += pch;
        _bma.pushnewtype(tmp._type);
        _mroot.push(_bma, tmp._type, tmp);
    }
    std::list<BSTree>::iterator it = _bma.getSearchTree().begin();
    while(it != _bma.getSearchTree().end()) {
        (*it).BalanceBST();
        it++;
    }//在文件初始化完成之后转换为平衡二叉树AVL树
    return true;
}
Users& Connection::InitUser(const string& name, const string& id)
{
    /*_lur.push_back({name,id});
    return _lur.back();*/
    return _lur.push({ name,id });
}
Manager& Connection::InitManager(const string& name, const string& id)
{
    /*_vMa.push_back({name,id});
    return _vMa.back();*/
    _vMa.push_back({ name,id });
    return _vMa.back();
}
const BookInfor* Connection::search_by_usr(const Users& usr, const string& type, const string& name)
{
    /*return usr.usersearch(_bma, type, name);*/
    return usr.usersearch(_bma, type, name);
}
bool Connection::push_new_book(Manager& rma, const BookInfor& rbi)
{
    rma.push(_bma, rbi._type, rbi);
    return true;
}
bool Connection::pop_old_book(Manager& rma, const string& type, const string& name)
{
    rma.pop(_bma, type, name);
    return true;
}
bool Connection::usrborrow(Users& usr, const string& type, const string& name)
{
    return usr.borrow(_bma,type,name);
}
Manager* Connection::Marigister(const string& name, const string& id)
{
    Manager tmp(name, id);
    vector<Manager>::iterator it = _vMa.begin();
    while(it != _vMa.end()) {
        if((*it) == tmp) break;
        ++it;
    }

    if (it == _vMa.end()) return nullptr;
    // return &_vMa[it - _vMa.begin()];
    return &(*it);
}
Users* Connection::usrrigister(const string& name, const string& id)
{
    return _lur.search({ name,id });
}
void Connection::the_connect_of_traverBSTree() {
    _bma.traverBSTree_by_type();
}
Connection::Connection() {
    ConnectionSize++;
    if(ConnectionSize > 1) perror("this interface can be constracted only once");
}
bool Connection::clearUsr(const Users& rusr) {
    return _lur.pop(rusr);
}
bool Connection::clearManager(const Manager& rma) {
    vector<Manager>::iterator it = _vMa.begin();
    while(it != _vMa.end()) {
        if((*it) == rma) break;\
        ++it;
    }
    if(it == _vMa.end()) return false;
    _vMa.erase(it);
    return true;
}

bool Connection::clearAllUser() {
    _lur.~BSTree();
    return true;
}
bool Connection::clearAllManager() {
    _vMa.clear();
    return true;
}

bool Connection::clearAllBookInfor() {
    _bma.clear();
    return true;
}
vector<BookInfor> &Connection::getAllBookInfor(vector<BookInfor> &rvbi) {
    _bma.pushAllBookInfor(rvbi);
    return rvbi;
}
void Connection::balanceBST() {
    _bma.getBalance();
}
bool Connection::returnBook(Users& usr) {
    return usr.retBook(_bma);
}





