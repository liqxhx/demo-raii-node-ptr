//
// Created by liqxhx on 2018/1/30.
//

#ifndef _NODE_H_
#define _NODE_H_

// ===========================================================================
class Node
{
public:
    Node();
    ~Node();
};

// ===========================================================================
// RAII：一个对象可以拥有资源。在对象的构造函数中执行资源的获取，在析构函数中释放
// 简单地模拟智能指针，来管理资源：内存、文件句柄、套接字、互斥量、信号量...
// 利用RAII技法，将裸指针包装为智能指针
// 这里的智能指针是一个类，再利用了类对象的析构在生存期结束时确定会被调用的
// 只要重载operator->,*,=,拷贝构造函数就可实现对裸指针的包装
// 可以避免内存泄漏、空悬指针(指向已被回收的mwdh)、重复释放等问题
class NodePtr
{
public:
    // 在构造函数中获取资源
    // explicit防止编译器自动转换, 默认附空值
    explicit NodePtr(Node* ptr = 0):_pnode(ptr){}

    // 析构函数中释放资源
    ~NodePtr()
    {
        delete _pnode;
    }

    // 获取_pnode
    Node* Get() const
    {
        return _pnode;
    }

    // 为了像裸指针一样能使用->，重装指针运算符
    Node* operator ->()
    {
        return Get();
    }

    // 为了像支持裸指针一样使用*，重载*号运算符
    Node& operator *() const
    {
        return *Get();
    }

    // 释放资源所有权
    Node* Release()
    {
        Node* tmp = _pnode;
        _pnode = 0; // 避免空悬指针
        return tmp;
    }

    // 为了让NodePtr ptr2(ptr)这样调用，不会出现重复释放的问题，所以覆盖拷贝构造函数
    // 将other对_pnode的所有权转让给当前对象
//    NodePtr(const NodePtr& other):_pnode(Release()) 通常的拷贝构造函数参数是const引用，但这里other本身是会变的，所以去掉了const
    NodePtr(NodePtr& other):_pnode(Release())
    {
        // 释放other对其_pnode的资源所有权
//        _pnode = Release();

    }

    // 为了支持
    // NodePtr ptr2(new Node);
    // NodePtr ptr3;
    // ptr3 = ptr2
    // 重载operator=运算符
    NodePtr& operator=(NodePtr& other)
    {
        // 先调用other.Release()释放other对_pnode的所有权
        // 然后重置=号左边对象的
        Reset(other.Release());
        return *this;
    }
    void Reset(Node* ptr = 0)
    {
        if(ptr != _pnode)
        {
            delete _pnode; // 释放左边数
        }
        _pnode = ptr; // 将右边数释放的指针附值给左边数
    }
private:
    Node* _pnode;
};

#endif // _NODE_H_
