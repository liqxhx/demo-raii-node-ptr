#include <iostream>
#include "Node.h"

// 应用RAII将裸指针转换为智能指针
// 这里的智能指针是一个类，再利用了类对象的析构在生存期结束时确定会被调用的
// 只要重载operator->,*,=,拷贝构造函数就可实现对裸指针的包装
// 可以避免内存泄漏、空悬指针(指向已被回收的mwdh)、重复释放等问题

int main() {
    std::cout << "Hello, RAII(Resource Acquisition Is Initialization! 资源获取即初始化" << std::endl;

//    Node* pnode = new Node; // 由于没有delete所以会出现内存泄漏
//    NodePtr ptr(pnode);


    NodePtr ptr(new Node);

    NodePtr ptr2(ptr);

    NodePtr ptr3;
    ptr3 = ptr2;

    return 0;
}