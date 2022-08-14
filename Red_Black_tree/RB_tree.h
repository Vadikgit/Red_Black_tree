#pragma once

#include <iostream>
#include <vector>

template <class T>
class RB_tree
{
public:
    template <class T1>
    class Object
    {
    public:
        enum class M_COLOR
        {
            C_RED = 0,
            C_BLACK = 1,
        };

        Object(T1 key) : parent(nullptr), left_son(nullptr), right_son(nullptr),
            m_key{ key }, m_color{ M_COLOR::C_BLACK }
        {
        };

        virtual ~Object() {};
        Object* parent;
        Object* left_son;
        Object* right_son;
        T1 m_key;
        M_COLOR m_color;
    };

    //относительно бинарного дерева поиска поменян nullptr на фиктивный объект nil

    RB_tree(const T& key_for_nil) {
        pointer_arr.push_back(new Object<T>(key_for_nil));
        pointer_arr[0]->m_color = Object<T>::M_COLOR::C_BLACK;

        nil = pointer_arr[0];
        root = pointer_arr[0];
    };

    Object<T>* root;
    Object<T>* nil;
    virtual Object<T>* RB_Search(const T&);
    virtual Object<T>* RB_Minimum(Object<T>*);
    virtual Object<T>* RB_Maximum(Object<T>*);
    virtual Object<T>* RB_Predecessor(Object<T>*);
    virtual Object<T>* RB_Successor(Object<T>*);
    virtual Object<T>* RB_Insert(const T&);
    virtual void RB_Insert_Fixup(Object<T>*);
    virtual void RB_Delete(Object<T>*);
    virtual void RB_Delete_Fixup(Object<T>*);
    virtual void RB_Inorder_Walk(Object<T>*);
    virtual void Left_Rotate(Object<T>*);
    virtual void Right_Rotate(Object<T>*);

    std::vector<Object<T>*> pointer_arr;
    virtual ~RB_tree() {
        for (auto i : pointer_arr)
        {
            delete i;
        }
    };

    virtual void RB_Transplant(Object<T>*, Object<T>*); //используем только в Tree_Delete
};


