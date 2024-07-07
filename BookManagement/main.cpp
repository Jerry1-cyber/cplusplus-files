//这个文件里面都只是我的测试
#include "interface.h"
int Connection::ConnectionSize = 0;
class compare {
public:
    bool operator()(const string& str1, const string& str2) {
        return str1 < str2;
    }
};
void test01()
{
    mystl::BSTree<string, compare> bst;
    bst.push("heruijie");
    bst.push("heruicie");
    bst.push("heruihie");
    bst.push("heruihie");
}
void test02() {
    Connection con;
    con.InitBookManagement("../book.txt");
    // const BookInfor* tmp = con.search_by_usr(con.getRoot(),"小说","《高老头》");
    // cout << *tmp << endl;
    // Users& usr1 = con.InitUser("heruijie","1882");
    // con.usrborrow(usr1,"小说","《高老头》");
    // tmp = con.search_by_usr(con.getRoot(),"小说","《高老头》");
    // cout<<*tmp<<endl;
    // const BookInfor* cpbi = con.search_by_usr(usr1,"小说","老人与海");
    // if(!cpbi) cout << "没有这本书" << endl;
    // else cout << *cpbi <<endl;
    con.the_connect_of_traverBSTree();

}
void testclear() {
    Connection con;
    con.InitBookManagement("../book.txt");
    //通过book.txt对图书管理系统进行一个初始化
    // int begin1 = clock();
    // for(size_t i = 1; i < 10000;i++) {
    //     string name = "heruijie";
    //     string id = "123";
    //     con.InitUser(name,id);
    // }
    // int end1 = clock();
    // cout << end1 - begin1 << endl;
    Manager& rma = con.InitManager("heruijie","123");
    BookInfor tmp("老人与海","小说","海明威");
    int begin1 = clock();
    for(size_t i = 1;i < 10000;i++) {
        rma.push(con.getManagement(),tmp._type,tmp);
    }
    int end1 = clock();
    cout << end1 - begin1 << endl;
    Users* ret = con.usrrigister("heruijie","23");
    con.clearUsr(*ret);
    int begin2 = clock();
    const BookInfor* bi = con.search_by_usr(*ret,"小说","老人与海");
    int end2 = clock();
    cout << end2 - begin2 << endl;
}
int main()
{
    testclear();
    return 0;
}