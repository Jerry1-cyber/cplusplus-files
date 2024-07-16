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
    // const BookInfor* tmp = con.search_by_usr(con.ge；。tRoot(),"小说","《高老头》");
    // cout << *tmp << endl;
    // Users& usr1 = con.InitUser("heruijie","1882");
    // con.usrborrow(usr1,"小说","《高老头》");
    // tmp = con.search_by_usr(con.getRoot(),"小说","《高老头》");
    // cout<<*tmp<<endl;
    // const BookInfor* cpbi = con.search_by_usr(usr1,"小说","老人与海");
    // if(!cpbi) cout << "没有这本书" << endl;
    // else cout << *cpbi <<endl;

    Manager& rma = con.InitManager("heruijie","123");
    Manager* pma = con.Marigister("heruijie","123");
    if(pma == nullptr) cout << "查无此人" << endl;
    else cout << "确有此人" << endl;
    Users& rusr = con.InitUser("heruijie","123");
    Users* pusr = con.usrrigister("heruijie","123");
    if(pusr == nullptr) cout << "查无此人" << endl;
    else cout << "确有此人" << endl;
    con.clearAllBookInfor();
    bool ret = con.clearManager(rma);
    ret = con.clearUsr(rusr);

}
// enum choice1 {
//     usr_rigiste = 1,
//     manager_rigiste,
//     Init_new_rigiste,
//     break_from_BookManagement,
//     overview,
//     cinerror,
// };
// istream& operator>>(istream& in,enum choice1& rcho) {
//     int tmp = 0;
//     in >> tmp;
//     switch(tmp) {
//         case 1:rcho = usr_rigiste;break;
//         case 2:rcho = manager_rigiste;break;
//         case 3:rcho = Init_new_rigiste;break;
//         case 4:rcho = overview;break;
//         case 5:rcho = break_from_BookManagement;break;
//         default:rcho = cinerror;break;
//     }
//     return in;
// }
// void menu1() {
//     system("title BookManagerment");
//     cout << "*************************" << endl;
//     cout << "****  1.user rigiste   ***" << endl;
//     cout << "****  2.manager rigiste ***" << endl;
//     cout << "****  3.Init new user  ****" << endl;
//     cout << "****  4.overview   ********" << endl;
//     cout << "****  5.break  ************" << endl;
//     cout << "***************************" << endl;
// }
// void InitNewRigiste(Connection& con) {
//     string name,id;
//     cout << "what't your name:";
//     cin >> name;
//     cout << "the id that you want:";
//     cin >> id;
//     con.InitUser(name,id);
//     system("cls");
//     cout << "注册成功" << endl;
//     cout << "请前往登录" << endl;
//     system("pause");
// }
// void Rigiste_usr(Connection& con) {
//     string name,id;
//     cout << "your name:";
//     cin >> name;
//     cout << "your password";
//     cin >> id;
//     Users* pusr = con.usrrigister(name,id);
//     if(pusr == nullptr) {
//         cout << "this usr is not exist,please check your name and passwd" << endl;
//         return;
//     }
//     cout << "rigiste successfully"<<endl;
//     system("pause");
//     system("cls");
//
// }
int main()
{
    test02();
    return 0;
}