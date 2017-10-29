#include <gtest/gtest.h>


#define protected public
#define private public
//yes
#include "../link_list_v2.h"

#include <utility>
using namespace expr;

TEST(link_list_test,ctor_basic){
    //testing default ctor
    link_list<int> f;
    ASSERT_EQ(0, f.size());
    ASSERT_DEBUG_DEATH(f.front(),"");
    ASSERT_DEBUG_DEATH(f.back(), "");

    //testing copy ctor of empty list
    link_list<int> f1 = f;
    ASSERT_EQ(0, f1.size());
    ASSERT_DEBUG_DEATH(f1.front(),"");
    ASSERT_DEBUG_DEATH(f1.back(), "");

    //testing copy ctor of empty list
    link_list<int> f2 = link_list<int>(f1);

    ASSERT_EQ(0, f1.size());
    ASSERT_DEBUG_DEATH(f1.front(),"");
    ASSERT_DEBUG_DEATH(f1.back(), "");

}

TEST(link_list_test, push_back_and_pop_back){
    link_list<int> f;
    //filling list
    for(int i = 0; i < 20; i++){
        f.push_back(i);
    }
    //checking if list is filled right
    ASSERT_EQ(20,f.size());
    for(int i = 0; i < 20; i++){
        ASSERT_EQ(i, f.at(i));
        ASSERT_EQ(i, f[i]);
    }

    //emptying the list and checking if empty
    for(int i = 0; i < 20; i++){
        f.pop_back();
    }
    ASSERT_EQ(0,f.size());
}

TEST(link_list_test, back_and_front){
    link_list<int> f;
    //filling the list
    for(int i = 0; i < 20; i++){
        f.push_back(i);
    }

    //checking back and front
    ASSERT_EQ(0,f.front());
    ASSERT_EQ(19,f.back());
}

TEST(link_list_test, emplace_back_and_emplace_front){

    link_list<std::pair<int,int>> f;
    for (int i = 0; i < 20; ++i) {
        f.emplace_back(i,i);
    }

    for (int i = 0; i < 20; ++i) {
        auto t = std::pair<int,int>(i,i);
        ASSERT_EQ(f[i],t );
    }

    link_list<std::pair<int,int>> g;
    for (int i = 0; i < 20; ++i) {
        g.emplace_front(i,i);
    }

    for (int i = 19; i >= 0; --i) {
        auto t = std::pair<int,int>(i,i);
        ASSERT_EQ(g[19 - i], t);
    }


}

TEST(link_list_test, push_front_and_pop_front){
    link_list<int> f;
    //filling the list
    for(int i = 0; i < 20; i++){
        f.push_front(i);
    }

    //checking if the list was fill right, in this case reversed then push back and pop back
    ASSERT_EQ(20,f.size());
    for (int i = 19; i > -1; --i) {
        ASSERT_EQ(i, f.at(19-i));
        ASSERT_EQ(i, f[19-i]);
    }

    //emptying the list and checking if empty
    for(int i = 0; i < 20; i++){
        f.pop_front();
    }
    ASSERT_EQ(0,f.size());

}

TEST(link_list_test, iter_end_and_begin){
    link_list<int> f;
    //checking end empty iterator
    auto it = f.end();
    ASSERT_EQ(nullptr,it.ptr_);
    ASSERT_TRUE(it.end_);
    ASSERT_DEBUG_DEATH(*it,"");

    it = f.begin();

    //checking begin empty iterator
    ASSERT_TRUE(it.end_);
    ASSERT_EQ(nullptr, it.ptr_);
    ASSERT_DEBUG_DEATH(*it,"");

    //filling the list
    for(int i = 0; i < 20; i++){
        f.push_back(i);
    }

    //checking begin iterator of filled list
    it = f.begin();
    ASSERT_EQ(0,*it);
    ASSERT_FALSE(it.end_);

    //checking end iterator of empty list
    it = f.end();
    ASSERT_TRUE(it.ptr_->data_ == 19);
    ASSERT_TRUE(it.end_);
    auto it1 = f.begin();

    //moving an begin iterator to the end and then checking if they are equal
    for(int i = 0; i < 20; i++){
        it1++;
    }

    ASSERT_TRUE(it == it1);
}

TEST(link_list_test, ctor_advance){
    //testing copy ctor of filled list
    link_list<int> f;
    for(int i = 0; i < 20; i++){
        f.push_back(i);
    }
    link_list<int> g(f);

    for (int j = 0; j < 20; ++j) {
        ASSERT_EQ(j,g[j]);
        ASSERT_TRUE(&f[j] != &g[j]);
    }

    //testing assinment ctor of filled list
    link_list<int> q;
    q = g;

    for (int j = 0; j < 20; ++j) {
        ASSERT_EQ(j,g[j]);
        ASSERT_TRUE(&q[j] != &g[j]);
    }
}



TEST(link_list_test, iter_over_secq){
    //testing iterating over a secqunce
    link_list<int> f;
    for(int i = 0; i < 20; i++){
        f.push_back(i);
    }
    int n = 0;
    for(auto i : f){
        ASSERT_EQ(n, i);
        n++;
    }

    ASSERT_EQ(n,20);
}

TEST(link_list_test, clear){
    //testing clear if it clears the list
    link_list<int> f;
    for(int i = 0; i < 20; i++){
        f.push_back(i);
    }
    f.clear();
    ASSERT_TRUE(f.size() == 0);
    ASSERT_DEBUG_DEATH(f[0], "");
    ASSERT_DEBUG_DEATH(f.at(0), "");
}


TEST(link_list_test, erase){
    link_list<int> f;
    for(int i = 0; i < 20; i++){
        f.push_back(i);
    }

    //eraseing in the middle;
    f.erase(5,10);
    ASSERT_TRUE(f[5] == 10);
    ASSERT_TRUE(f.size() == 15);

    //eraseing in the beginning
    f.erase(0,5);
    ASSERT_TRUE(f[0] == 10);
    ASSERT_TRUE(f.size() == 10);

    //eraseing in the end
    f.erase(5,10);
    ASSERT_TRUE(f[4] == 14);
    ASSERT_TRUE(f.size() == 5);
}

TEST(link_list_test, insert){
    link_list<int> f;

    //testing insert in empty list
    f.insert(10,0);
    ASSERT_EQ(10,f[0]);

    //filling the list with numbers
    for (int i = 0; i < 10; ++i) {
        f.push_back(i);
    }

    //inserting in middle
    f.insert(23,4);
    ASSERT_EQ(23,f[4]);
    ASSERT_EQ(2,f[3]); //checking to see if 2 is still in spot 3
    ASSERT_EQ(3,f[5]);//checking to see if 3 has been shifted to 5

    //testing the size
    ASSERT_EQ(12,f.size());

    //testing insert at beginning;
    f.insert(24,0);
    ASSERT_EQ(24,f[0]);
    ASSERT_EQ(24,f.front());

    //test inserting at the end
    f.insert(35,13);
    ASSERT_EQ(35,f[13]);
    ASSERT_EQ(35, f.back());

    //testing the size again
    ASSERT_EQ(14,f.size());
}


TEST(link_list_test, emplace){
    link_list<std::pair<int,int> > f;

    //testing emplace in empty list
    f.emplace(0, 1,1);
    auto t1 = std::pair<int,int>(1,1);
    ASSERT_EQ(t1,f[0]);

    //filling the list with numbers pairs
    for (int i = 0; i < 10; ++i) {
        f.emplace_back(i,i);
    }

    //emplaceing in middle
    auto t2 = std::pair<int,int>(23,23);
    f.emplace(4,23,23);
    ASSERT_EQ(t2,f[4]);
    auto t3 = std::pair<int,int>(2,2);
    ASSERT_EQ(t3,f[3]); //checking to see if 2,2 is still in spot 3
    auto t4 = std::pair<int,int>(3,3);
    ASSERT_EQ(t4,f[5]);//checking to see if 3,3 has been shifted to 5

    //testing the size
    ASSERT_EQ(12,f.size());

    //testing insert at beginning;
    auto t5 = std::pair<int,int>(24,24);
    f.emplace(0,24,24);
    ASSERT_EQ(t5,f[0]);
    ASSERT_EQ(t5,f.front());

    //test inserting at the end
    auto t6 = std::pair<int,int>(35,35);
    f.emplace(13,35,35);
    ASSERT_EQ(t6,f[13]);
    ASSERT_EQ(t6, f.back());

    //testing the size again
    ASSERT_EQ(14,f.size());
}

TEST(link_list_test, rsize){
    link_list<int> f;
    //filling the list with numbers
    for (int i = 0; i < 10; ++i) {
        f.push_back(i);
    }
    //testing the resize and if it dose everything right
    f.rsize(5);
    ASSERT_EQ(5,f.size());
    ASSERT_DEATH(f[5],"");
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(f[i],i);
    }
}

TEST(link_list_test, reverse_iters){
    link_list<int> f;
    for (int i = 0; i < 10; ++i) {
        f.push_back(i);
    }

    link_list<int> g;
    for(auto i = f.rbegin(); i != f.rend(); i++){
        g.push_back(*i);
    }

    for (int i = 9; i > -1; --i) {
        ASSERT_EQ(f[9-i],g[i]);
    }
}