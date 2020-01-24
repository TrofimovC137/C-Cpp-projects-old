#include <iostream>
#include <stdlib.h>
#include <stdio.h>
template <class T>
struct Item{
    T key;
    Item* left;
    Item* right;
    Item();
    Item(T tkey);
    ~Item();
    void add(Item* p);
    void add_left(Item* p);
    void add_right(Item* p);
    void show();
};
template <class T>
Item<T>::Item(){
    left=NULL;
    right=NULL;
    key=0;
}
template <class T>
Item<T>::Item(T tkey){
    left=NULL;
    right=NULL;
    key=tkey;
}
template <class T>
Item<T>::~Item(){
    if(left!=NULL)delete left;
    if(right!=NULL)delete right;
    key=0;
}
template <class T>
void Item<T>::add_left(Item* p){
    if(left==NULL){
            left=p;
        }
        else{
            left->add(p);
        }
}
template <class T>
void Item<T>::add_right(Item* p){
    if(right==NULL){
            right=p;
        }
        else{
            right->add(p);
        }
}
template <class T>
void Item<T>::add(Item* p){
    if(p->key<key){
        add_left(p);
    }
    else{
        add_right(p);
    }
}
template <class T>
void Item<T>::show(){
    if(left!=NULL){
        left->show();
    }
    std::cout<<key<<std::endl;
    if(right!=NULL){
        right->show();
    }
}
template <class T>
class Tree{
    Item<T>* root;
public:
    Tree();
    ~Tree();
    void add(Item<T>* p);
    void show();
};
template <class T>
Tree<T>::Tree(){
    root=NULL;
}
template <class T>
Tree<T>::~Tree(){
    if(root!=NULL)
    delete root;
}
template <class T>
void Tree<T>::add(Item<T>* p){
    if(root==NULL){
        root=p;
    }
    else{
        root->add(p);
    }
}
template <class T>
void Tree<T>::show(){
    root->show();
}
int main()
{
    Tree<char> A;
    Item<char>* a=new Item<char>;
    Item<char>* b=new Item<char>;
    a->key='a';
    b->key='z';
    A.add(a);
    A.add(b);
    A.show();
    return 0;
}
