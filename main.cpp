#include "skiplist.h"
#include "avl_tree.h"
#include <bits/stdc++.h>

#define init_size 200000
#define test_size 100

int main()
{
    // SkipList<int> *skiplist = new SkipList<int>();
    // for (int i=0;i<100;i++) {
    //     skiplist->add(rand());
    // }
    // skiplist->print();
    // return 0;


    srand(time(nullptr));

    //测试数据部分
    vector<int> init_datas;
    vector<int> test_datas;

    //定义跳表
    SkipList<int> *skiplist = new SkipList<int>();
    //定义红黑树
    // RBTree rbTree;
    //定义AVL树
    AVLTree<int> avl;

    //计时部分
    clock_t t; //时间戳
    clock_t init_time[3] = {0};
    clock_t search_time[3]= {0};
    clock_t erase_time[3]= {0};

    //随机产生插入测试数据
    for (int i = 0; i < init_size; i++)
    {
        init_datas.push_back(rand());
    }
    //随机产生查找、删除测试数据
    for (int i = 0; i < test_size; i++)
    {
        test_datas.push_back(rand() % init_size);
    }


    // /*插入测试部分开始*/
    //测试插入跳表
    t = clock();
    for (int i = 0; i < init_datas.size(); i++){
        skiplist->add(init_datas[i]);
    }
    init_time[0] = clock() - t;
    //测试插入红黑树
    // t = clock();
    // for (int i = 0; i < init_datas.size(); i++){
    //     rbTree.insertValue(init_datas[i]);
    // }
    // init_time[1] = clock() -t;
    //测试插入AVL树
    t = clock();
    for (int i = 0; i < init_datas.size(); i++){
        avl.insert(init_datas[i]);
    }
    init_time[2] = clock() - t;
    // /*插入测试部分结束*/


    // /*查找测试部分开始*/
    //测试跳表
    t = clock();
    for (int i = 0; i < init_datas.size(); i++){
        skiplist->search(init_datas[i]);
    }
    search_time[0] = clock() - t;
    //测试红黑树
    // t = clock();
    // for (int i = 0; i < init_datas.size(); i++){
    //     rbTree.    (init_datas[i]);
    // }
    // init_time[1] = t - clock();
    //测试AVL树
    t = clock();
    for (int i = 0; i < init_datas.size(); i++){
        avl.find(init_datas[i]);
    }
    search_time[2] = clock() - t;
    // /*查找测试部分结束*/


    // /*删除测试部分开始*/
    //测试跳表
    t = clock();
    for (int i = 0; i < init_datas.size(); i++){
        skiplist->erase(init_datas[i]);
    }
    erase_time[0] = clock() -t;
    // //测试红黑树
    // t = clock();
    // for (int i = 0; i < init_datas.size(); i++){
    //     rbTree.deleteValue(init_datas[i]);
    // }
    // erase_time[1] = clock() -t;
    //测试AVL树
    t = clock();
    for (int i = 0; i < init_datas.size(); i++){
        avl.remove(init_datas[i]);
    }
    erase_time[2] = clock() - t;
    // /*删除测试部分结束*/

    /*输出部分*/
    cout << "本轮测试数据:\n数据量:" << init_size << "\n查找以及删除数据量：" << test_size <<endl; 
    cout << "跳表\n初始化时间:" << float(init_time[0])/CLOCKS_PER_SEC << " s" << " 查找时间:" << float(search_time[0])/CLOCKS_PER_SEC << " s" << " 删除时间:" << float(erase_time[0])/CLOCKS_PER_SEC << " s" << endl;
    // cout << "红黑树\n初始化时间：" << init_time[1] << " 查找时间： " << search_time[1] << " 删除时间: " << erase_time[1] << endl;
    cout << "AVL树\n初始化时间:" << float(init_time[2])/CLOCKS_PER_SEC << " s" << " 查找时间:" << float(search_time[2])/CLOCKS_PER_SEC << " s" << " 删除时间:" << float(erase_time[2])/CLOCKS_PER_SEC << " s" << endl;
    //printf("It took me %d clicks (%f seconds) to find  .\n", init_time[0], ((float)t) / CLOCKS_PER_SEC);

}