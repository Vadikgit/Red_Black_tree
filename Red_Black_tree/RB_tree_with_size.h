#pragma once
#include "RB_tree.h"
#include "RB_tree.cpp"

template<class T>
class RB_tree_with_size : public RB_tree<T> {
public:
    RB_tree_with_size(const T& key_for_nil) :RB_tree<T>(key_for_nil) {
        this->pointer_arr.push_back(new Object_s<T>(key_for_nil));
        this->pointer_arr[1]->m_color = Object_s<T>::M_COLOR::C_BLACK;

        this->nil = this->pointer_arr[1];
        this->root = this->pointer_arr[1];
    };

    template<class T1>
    class Object_s : public RB_tree_with_size::Object<T1> {
    public:
        int m_size;

        Object_s(T1 key) : RB_tree_with_size::Object<T1>::Object(key), m_size{ 0 }
        {
        }
        ~Object_s() {};
    };

    Object_s<T>* Select_from_RB(RB_tree_with_size<T>::Object<T>*, int);
    Object_s<T>* RB_Insert(const T&) override;
    void RB_Inorder_Walk(RB_tree_with_size<T>::Object<T>*) override;
    void RB_Delete(RB_tree_with_size<T>::Object<T>*) override;
    void Left_Rotate(RB_tree_with_size<T>::Object<T>*) override;
    void Right_Rotate(RB_tree_with_size<T>::Object<T>*) override;
};

