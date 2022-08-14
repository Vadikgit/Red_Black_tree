#include "RB_tree_with_size.h"

template<class T>
RB_tree_with_size<T>::Object_s<T>* RB_tree_with_size<T>::RB_Insert(const T& key) {
    Object_s<T>* obj = new Object_s<T>(key);

    if (obj->left_son == nullptr)
    {
        obj->left_son = this->nil;
    }

    if (obj->right_son == nullptr)
    {
        obj->right_son = this->nil;
    }

    if (obj->parent == nullptr)
    {
        obj->parent = this->nil;
    }
    //--------
    obj->m_size = 1;
    //--------
    Object_s<T>* y = dynamic_cast<Object_s<T>*>(this->nil);
    Object_s<T>* x = dynamic_cast<Object_s<T>*>(this->root);
    while (x != this->nil)//спускаемся
    {
        //--------
        x->m_size += 1;
        //--------

        y = x;
        if (x->m_key > obj->m_key)
        {
            x = dynamic_cast<Object_s<T>*> (x->left_son);
        }
        else
        {
            x = dynamic_cast<Object_s<T>*> (x->right_son);

        }
    }

    obj->parent = y;//связываем
    if (y == this->nil)
    {
        this->root = obj;
    }
    else
    {
        if (obj->m_key < y->m_key)//x == y->left_son не сработает потому что как слева, так и справа могут быть nullptr
        {
            y->left_son = obj;
        }
        else
        {
            y->right_son = obj;
        }
    }

    obj->left_son = this->nil;
    obj->right_son = this->nil;
    obj->m_color = RB_tree_with_size::Object<T>::M_COLOR::C_RED;
    this->RB_Insert_Fixup(obj);

    this->pointer_arr.push_back(obj);
    return obj;
}

template<class T>
RB_tree_with_size<T>::Object_s<T>* RB_tree_with_size<T>::Select_from_RB(RB_tree_with_size<T>::Object<T>* cur_root, int rank) {
    if (rank == dynamic_cast<Object_s<T>*> (cur_root->left_son)->m_size + 1 - 1)
    {
        return dynamic_cast<Object_s<T>*> (cur_root);
    }
    else if (rank > dynamic_cast<Object_s<T>*> (cur_root->left_son)->m_size + 1 - 1)
    {
        return dynamic_cast<Object_s<T>*> (Select_from_RB(cur_root->right_son, rank - dynamic_cast<Object_s<T>*> (cur_root->left_son)->m_size - 1));
    }
    else
    {
        return dynamic_cast<Object_s<T>*> (Select_from_RB(cur_root->left_son, rank));
    }
}

template<class T>
void RB_tree_with_size<T>::RB_Inorder_Walk(RB_tree_with_size<T>::Object<T>* obj) {
    if (obj != this->nil)
    {
        RB_Inorder_Walk(obj->left_son);
        std::cout << '\n' << obj->m_key << " size [" << dynamic_cast<Object_s<T>*> (obj)->m_size << "]; left - " << obj->left_son->m_key << "; right - " << obj->right_son->m_key;
        RB_Inorder_Walk(obj->right_son);
    }
}

template<class T>
void RB_tree_with_size<T>::RB_Delete(RB_tree_with_size<T>::Object<T>* obj) {
    Object_s<T>* y = dynamic_cast<Object_s<T>*> (obj);

    //-------
    Object_s<T>* y_for_up = y;
    //-------

    Object_s<T>* x;
    enum Object_s<T>::M_COLOR y_orig_color = y->m_color;

    if (obj->left_son == this->nil)
    {
        x = dynamic_cast<Object_s<T>*> (obj->right_son);
        this->RB_Transplant(obj, obj->right_son);
        //-------

        //-------
    }
    else if (obj->right_son == this->nil)
    {
        x = dynamic_cast<Object_s<T>*> (obj->left_son);
        this->RB_Transplant(obj, obj->left_son);
        //-------

        //-------
    }
    else
    {
        y = dynamic_cast<Object_s<T>*> (this->RB_Minimum(obj->right_son));

        //-------
        y_for_up = y;
        //-------

        y_orig_color = y->m_color;
        x = dynamic_cast<Object_s<T>*> (y->right_son);

        if (y->parent == obj)
        {
            x->parent = y;
        }
        else {
            this->RB_Transplant(y, y->right_son);
            y->right_son = obj->right_son;
            y->right_son->parent = y;
        }

        //-------
        y_for_up = dynamic_cast<Object_s<T>*> (y_for_up->parent);
        //-------
        this->RB_Transplant(obj, y);
        y->left_son = obj->left_son;
        y->left_son->parent = y;
        y->m_color = obj->m_color;
        //-------
        y->m_size = dynamic_cast<Object_s<T>*> (y->left_son)->m_size + dynamic_cast<Object_s<T>*> (y->right_son)->m_size + 1;
        //-------
    }

    //-------
    while (y_for_up != this->nil)
    {
        y_for_up->m_size = y_for_up->m_size - 1;
        y_for_up = dynamic_cast<Object_s<T>*> (y_for_up->parent);
    }
    //-------   


    if (y_orig_color == RB_tree_with_size<T>::Object<T>::M_COLOR::C_BLACK)
    {
        this->RB_Delete_Fixup(x);
    }
}

template<class T>
void RB_tree_with_size<T>::Left_Rotate(RB_tree_with_size<T>::Object<T>* obj) {
    Object_s<T>* right = dynamic_cast<Object_s<T>*> (obj->right_son);
    obj->right_son = right->left_son;

    if (right->left_son != this->nil)
    {
        right->left_son->parent = obj;
    }
    right->parent = obj->parent;

    if (obj->parent == this->nil)
    {
        this->root = right;
    }
    else if (obj == obj->parent->left_son)
    {
        obj->parent->left_son = right;
    }
    else
    {
        obj->parent->right_son = right;
    }

    right->left_son = obj;
    obj->parent = right;


    //--------
    right->m_size = dynamic_cast<Object_s<T>*> (obj)->m_size;
    dynamic_cast<Object_s<T>*> (obj)->m_size = dynamic_cast<Object_s<T>*> (obj->left_son)->m_size
        + dynamic_cast<Object_s<T>*> (obj->right_son)->m_size + 1;
    //--------
}

template<class T>
void RB_tree_with_size<T>::Right_Rotate(RB_tree_with_size<T>::Object<T>* obj) {
    Object_s<T>* left = dynamic_cast<Object_s<T>*> (obj->left_son);
    obj->left_son = left->right_son;

    if (left->right_son != this->nil)
    {
        left->right_son->parent = obj;
    }
    left->parent = obj->parent;

    if (obj->parent == this->nil)
    {
        this->root = left;
    }
    else if (obj == obj->parent->left_son)
    {
        obj->parent->left_son = left;
    }
    else
    {
        obj->parent->right_son = left;
    }

    left->right_son = obj;
    obj->parent = left;


    //--------
    left->m_size = dynamic_cast<Object_s<T>*> (obj)->m_size;
    dynamic_cast<Object_s<T>*> (obj)->m_size = dynamic_cast<Object_s<T>*> (obj->left_son)->m_size +
        dynamic_cast<Object_s<T>*> (obj->right_son)->m_size + 1;
    //--------
}