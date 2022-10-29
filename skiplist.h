//
// Created by 卢城钦 on 2022/10/29.
//

#ifndef OJ_SKIPLIST_H
#define OJ_SKIPLIST_H

#include <time.h>
#include <cstdlib>

#include <iostream>
#include <random>
#include <vector>

using namespace std;

#define LEVEL_NUM 32
#define P 0.25

// 节点类
template <class T>
class myNode {
public:
    // 构造函数
    explicit myNode(T val, int level_num = LEVEL_NUM) : value(val), next(level_num, nullptr) {}

    // 节点值
    T value;

    // size为LEVEL_NUM，用于记录每个节点在不同层中的后继关系
    vector<myNode *> next;
};


// 跳表类
template <class T>
class SkipList {
public:
    // 构造函数
    SkipList() : head(new myNode<T>(-1)), level_num(0), urd(0, 1) {}

    int add(T val); // 添加新节点
    bool search(T val); // 按值寻找
    bool erase(T val); // 按值删除
    void print(); // 打印
    int randomLevelNum(); // 添加新节点时，随机生成需要添加的层数
private:
    // 头节点
    myNode<T> *head;
    // 层数
    int level_num;
    // 随机数相关
    mt19937 mt{random_device{}()};
    uniform_real_distribution<double> urd;
};

// 添加新节点时，随机生成需要添加的层数

template<class T>
int SkipList<T>::randomLevelNum() {
    int rd_level_num = 1;
    while (urd(mt) < P && rd_level_num < LEVEL_NUM) {
        rd_level_num++;
    }
    return rd_level_num;
}


template<class T>
int SkipList<T>::add(T val) {
    // 获取该节点将要被添加的层数
    int myNode_level_num = randomLevelNum();
    myNode<T> *cur = this->head;
    // 用于记录新节点所在层待更新的链接关系
    vector<myNode<T> *> toUpdateList(LEVEL_NUM, head);
    /*
        从最上层开始寻找“每层中最接近val的节点”，记录到对应层中的toUpdateList
        方便之后更新链接关系
    */
    for (int i = level_num - 1; i >= 0; i--) {
        while (cur->next[i] && cur->next[i]->value < val) {
            cur = cur->next[i];
        }
        toUpdateList[i] = cur;
    }
    // 新节点
    myNode<T> *newmyNode = new myNode<T>(val, myNode_level_num);
    // 更新跳表整个的层数
    level_num = max(level_num, myNode_level_num);
    // 从下到上根据toUpdateList中的记录更新myNode_level_num个层的链接关系，所以最底层包含所有节点之间的链接关系
    for (int i = 0; i < myNode_level_num; i++) {
        newmyNode->next[i] = toUpdateList[i]->next[i];
        toUpdateList[i]->next[i] = newmyNode;
    }
    return 0;
}


template<class T>
bool SkipList<T>::search(T val) {
    myNode<T> *cur = this->head;
    // 从上层到最底层寻找
    for (int i = level_num - 1; i >= 0; i--) {
        while (cur->next[i] && cur->next[i]->value < val) {
            cur = cur->next[i];
        }
    }
    if (cur && cur->value == val) {
        return true;
    }
    return false;
}


template<class T>
bool SkipList<T>::erase(T val) {
    // 先寻找是否有节点的value值为val，同上，不过此时需要记录toUpdateList
    vector<myNode<T> *> toUpdateList(LEVEL_NUM, nullptr);
    myNode<T> *cur = this->head;
    for (int i = level_num - 1; i >= 0; i--) {
        while (cur->next[i] && cur->next[i]->value < val) {
            cur = cur->next[i];
        }
        toUpdateList[i] = cur;
    }
    cur = cur->next[0];
    if (!cur || cur->value != val) {
        return false;
    }
    // 从最下层开始更新
    for (int i = 0; i < level_num; i++) {
        if (toUpdateList[i]->next[i] != cur) {
            break;
        }
        toUpdateList[i]->next[i] = cur->next[i]; // 更新
    }
    delete cur;
    while (level_num > 1 && head->next[level_num - 1] == nullptr) {
        level_num--;
    }
    return true;
}

template<class T>
void SkipList<T>::print() {
    for (int i = level_num - 1; i >= 0; i--) {
        myNode<T> *cur = this->head;
        cout << i << ": ";
        while (cur->next[i]) {
            cur = cur->next[i];
            cout << cur->value << " ";
        }
        cout << endl;
    }
}




//static double p = 1 / 4;
//static int MaxLevel = 32;
//
//int randomLevel() {
//    int level = 1;
//    srand((unsigned) time(NULL));
//    while ((rand() / double(RAND_MAX)) < p && level < MaxLevel) {
//        level++;
//    }
//    return level;
//}

#endif //OJ_SKIPLIST_H
