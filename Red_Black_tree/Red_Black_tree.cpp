// Red_Black_tree.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <vector>

template <class T>
class RB_tree
{
public:
    template <class T>
    class Object
    {
    public:
        enum class M_COLOR
        {
            C_RED = 0,
            C_BLACK = 1,
        };

        Object(T key) : parent(nullptr), left_son(nullptr), right_son(nullptr),
            m_key{ key }, m_color{ M_COLOR::C_BLACK }
        {
        };
        
        virtual ~Object() {};
        Object* parent;
        Object* left_son;
        Object* right_son;
        T m_key;
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

template<class T>
RB_tree<T>::Object<T>* RB_tree<T>::RB_Insert(const T& key) {
    Object<T>* obj = new Object<T>(key);

    if (obj->left_son == nullptr)
    {
        obj->left_son = nil;
    }

    if (obj->right_son == nullptr)
    {
        obj->right_son = nil;
    }

    if (obj->parent == nullptr)
    {
        obj->parent = nil;
    }
    
    Object<T>* y = nil;
    Object<T>* x = root;
    while (x != nil)//спускаемся
    {
       

        y = x;
        if (x->m_key > obj->m_key)
        {
            x = x->left_son;
        }
        else
        {
            x = x->right_son;

        }
    }

    obj->parent = y;//связываем
    if (y == nil)
    {
        root = obj;
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

    obj->left_son = nil;
    obj->right_son = nil;
    obj->m_color = Object<T>::M_COLOR::C_RED;
    RB_Insert_Fixup(obj);

    pointer_arr.push_back(obj);
    return obj;
}

template<class T>
RB_tree<T>::Object<T>* RB_tree<T>::RB_Search(const T& key) {
    Object<T>* x = root;
    while ((x != nil) && (x->m_key != key))
    {
        if (x->m_key > key)
        {
            x = x->left_son;
        }
        else
        {
            x = x->right_son;
        }
    }
    return x;
}

template<class T>
RB_tree<T>::Object<T>* RB_tree<T>::RB_Minimum(Object<T>* x) {
    if (x != nil)
    {
        while (x->left_son != nil)
        {
            x = x->left_son;
        }
    }

    return x;
}

template<class T>
RB_tree<T>::Object<T>* RB_tree<T>::RB_Maximum(Object<T>* x) {
    if (x != nil)
    {
        while (x->right_son != nil)
        {
            x = x->right_son;
        }
    }

    return x;
}

template<class T>
RB_tree<T>::Object<T>* RB_tree<T>::RB_Predecessor(Object<T>* obj) {
    if (obj->left_son != 0)
    {
        return RB_Maximum(obj->left_son);
    }
    else
    {
        Object<T>* y = obj->parent;
        while ((y != nil) && (obj == y->left_son))
        {
            obj = y;
            y = obj->parent;
        }
        return y;
    }
}

template<class T>
RB_tree<T>::Object<T>* RB_tree<T>::RB_Successor(Object<T>* obj) {
    if (obj->right_son != 0)
    {
        return RB_Minimum(obj->right_son);
    }
    else
    {
        Object<T>* y = obj->parent;
        while ((y != nil) && (obj == y->right_son))
        {
            obj = y;
            y = obj->parent;
        }
        return y;
    }
}

template<class T>
void RB_tree<T>::Left_Rotate(Object<T>* obj) {
    Object<T>* right = obj->right_son;
    obj->right_son = right->left_son;

    if (right->left_son != nil)
    {
        right->left_son->parent = obj;
    }
    right->parent = obj->parent;

    if (obj->parent == nil)
    {
        root = right;
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
}

template<class T>
void RB_tree<T>::Right_Rotate(Object<T>* obj) {
    Object<T>* left = obj->left_son;
    obj->left_son = left->right_son;

    if (left->right_son != nil)
    {
        left->right_son->parent = obj;
    }
    left->parent = obj->parent;

    if (obj->parent == nil)
    {
        root = left;
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
}

template<class T>
void RB_tree<T>::RB_Insert_Fixup(Object<T>* obj) {
    Object<T>* y;
    while (obj->parent->m_color == Object<T>::M_COLOR::C_RED)
    {
        if (obj->parent == obj->parent->parent->left_son)
        {
            y = obj->parent->parent->right_son;
            if (y->m_color == Object<T>::M_COLOR::C_RED)
            {
                obj->parent->m_color = Object<T>::M_COLOR::C_BLACK;
                y->m_color = Object<T>::M_COLOR::C_BLACK;
                obj->parent->parent->m_color = Object<T>::M_COLOR::C_RED;
                obj = obj->parent->parent;
            }
            else
            {
                if (obj == obj->parent->right_son)
                {
                    obj = obj->parent;
                    Left_Rotate(obj);
                }

                obj->parent->m_color = Object<T>::M_COLOR::C_BLACK;
                obj->parent->parent->m_color = Object<T>::M_COLOR::C_RED;
                Right_Rotate(obj->parent->parent);
            }
        }

        else
        {
            y = obj->parent->parent->left_son;
            if (y->m_color == Object<T>::M_COLOR::C_RED)
            {
                obj->parent->m_color = Object<T>::M_COLOR::C_BLACK;
                y->m_color = Object<T>::M_COLOR::C_BLACK;
                obj->parent->parent->m_color = Object<T>::M_COLOR::C_RED;
                obj = obj->parent->parent;
            }
            else {
                if (obj == obj->parent->left_son)
                {
                    obj = obj->parent;
                    Right_Rotate(obj);
                }

                obj->parent->m_color = Object<T>::M_COLOR::C_BLACK;
                obj->parent->parent->m_color = Object<T>::M_COLOR::C_RED;
                Left_Rotate(obj->parent->parent);
            }
        }

    }
    root->m_color = Object<T>::M_COLOR::C_BLACK;
}

template<class T>
void RB_tree<T>::RB_Transplant(Object<T>* obj_old, Object<T>* obj_new) {
    if (obj_old->parent == nil)
    {
        root = obj_new;
    }
    else if (obj_old == obj_old->parent->left_son)
    {
        obj_old->parent->left_son = obj_new;
    }
    else
    {
        obj_old->parent->right_son = obj_new;
    }
    obj_new->parent = obj_old->parent;//допускаем даже если новый указывает на фиктивный ограничитель

}

template<class T>
void RB_tree<T>::RB_Delete(Object<T>* obj) {
    Object<T>* y = obj;

    Object<T>* x;
    enum Object<T>::M_COLOR y_orig_color = y->m_color;

    if (obj->left_son == nil)
    {
        x = obj->right_son;
        RB_Transplant(obj, obj->right_son);
    }
    else if (obj->right_son == nil)
    {
        x = obj->left_son;
        RB_Transplant(obj, obj->left_son);
    }
    else
    {
        y = RB_Minimum(obj->right_son);

        y_orig_color = y->m_color;
        x = y->right_son;

        if (y->parent == obj)
        {
            x->parent = y;
        }
        else {
            RB_Transplant(y, y->right_son);
            y->right_son = obj->right_son;
            y->right_son->parent = y;
        }

        RB_Transplant(obj, y);
        y->left_son = obj->left_son;
        y->left_son->parent = y;
        y->m_color = obj->m_color;
    }

    if (y_orig_color == Object<T>::M_COLOR::C_BLACK)
    {
        RB_Delete_Fixup(x);
    }
}

template<class T>
void RB_tree<T>::RB_Delete_Fixup(Object<T>* obj) {
    Object<T>* w;
    while ((obj != root) && (obj->m_color == Object<T>::M_COLOR::C_BLACK))
    {
        if (obj == obj->parent->left_son)
        {
            w = obj->parent->right_son;
            if (w->m_color == Object<T>::M_COLOR::C_RED)
            {
                w->m_color = Object<T>::M_COLOR::C_BLACK;
                obj->parent->m_color = Object<T>::M_COLOR::C_RED;
                Left_Rotate(obj->parent);
                w = obj->parent->right_son;
            }

            if ((w->left_son->m_color == Object<T>::M_COLOR::C_BLACK) && (w->right_son->m_color == Object<T>::M_COLOR::C_BLACK))
            {
                w->m_color = Object<T>::M_COLOR::C_RED;
                obj = obj->parent;
            }
            else {
                if (w->right_son->m_color == Object<T>::M_COLOR::C_BLACK)
                {
                    w->left_son->m_color = Object<T>::M_COLOR::C_BLACK;
                    w->m_color = Object<T>::M_COLOR::C_RED;
                    Right_Rotate(w);
                    w = obj->parent->right_son;
                }

                w->m_color = obj->parent->m_color;
                obj->parent->m_color = Object<T>::M_COLOR::C_BLACK;
                w->right_son->m_color = Object<T>::M_COLOR::C_BLACK;
                Left_Rotate(obj->parent);
                obj = root;

            }
        }



        else
        {
            w = obj->parent->left_son;
            if (w->m_color == Object<T>::M_COLOR::C_RED)
            {
                w->m_color = Object<T>::M_COLOR::C_BLACK;
                obj->parent->m_color = Object<T>::M_COLOR::C_RED;
                Right_Rotate(obj->parent);
                w = obj->parent->left_son;
            }

            if ((w->right_son->m_color == Object<T>::M_COLOR::C_BLACK) && (w->left_son->m_color == Object<T>::M_COLOR::C_BLACK))
            {
                w->m_color = Object<T>::M_COLOR::C_RED;
                obj = obj->parent;
            }
            else {
                if (w->left_son->m_color == Object<T>::M_COLOR::C_BLACK)
                {
                    w->right_son->m_color = Object<T>::M_COLOR::C_BLACK;
                    w->m_color = Object<T>::M_COLOR::C_RED;
                    Left_Rotate(w);
                    w = obj->parent->left_son;
                }

                w->m_color = obj->parent->m_color;
                obj->parent->m_color = Object<T>::M_COLOR::C_BLACK;
                w->left_son->m_color = Object<T>::M_COLOR::C_BLACK;
                Right_Rotate(obj->parent);
                obj = root;
            }
        }
    }
    obj->m_color = Object<T>::M_COLOR::C_BLACK;
}

template<class T>
void RB_tree<T>::RB_Inorder_Walk(Object<T>* obj) {
    if (obj != nil)
    {
        RB_Inorder_Walk(obj->left_son);
        std::cout << '\n' << obj->m_key << " left - " << obj->left_son->m_key << "; right - " << obj->right_son->m_key;
        RB_Inorder_Walk(obj->right_son);
    }
}
//---------------------RB_tree defined---------------------------


//---------------------expansion of RB_tree---------------------------
template<class T>
class RB_tree_with_size : public RB_tree<T> {
public:
    RB_tree_with_size(const T& key_for_nil):RB_tree<T>(key_for_nil) {
        this->pointer_arr.push_back(new Object_s<T>(key_for_nil));
        this->pointer_arr[1]->m_color = Object_s<T>::M_COLOR::C_BLACK;

        this->nil = this->pointer_arr[1];
        this->root = this->pointer_arr[1];
    };

    template<class T>
    class Object_s : public RB_tree_with_size::Object<T>{
    public:
        int m_size;

        Object_s(T key) : RB_tree_with_size<T>::Object<T>::Object(key), m_size{0}
        {
        }  
        ~Object_s() {};
    };

    Object_s<T>* Select_from_RB(RB_tree_with_size::Object<T>*, int);
    Object_s<T>* RB_Insert(const T&) override;
    void RB_Inorder_Walk(RB_tree_with_size::Object<T>*) override;
    void RB_Delete(RB_tree_with_size::Object<T>*) override;
    void Left_Rotate(RB_tree_with_size::Object<T>*) override;
    void Right_Rotate(RB_tree_with_size::Object<T>*) override;
};


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
RB_tree_with_size<T>::Object_s<T>* RB_tree_with_size<T>::Select_from_RB(RB_tree_with_size::Object<T>* cur_root, int rank) {
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
void RB_tree_with_size<T>::RB_Inorder_Walk(RB_tree_with_size::Object<T> * obj) {
    if (obj != this->nil)
    {
        RB_Inorder_Walk(obj->left_son);
        std::cout << '\n' << obj->m_key << " size [" << dynamic_cast<Object_s<T>*> (obj)->m_size << "]; left - " << obj->left_son->m_key << "; right - " << obj->right_son->m_key;
        RB_Inorder_Walk(obj->right_son);
    }
}

template<class T>
void RB_tree_with_size<T>::RB_Delete(RB_tree_with_size::Object<T> * obj) {
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
void RB_tree_with_size<T>::Left_Rotate(RB_tree_with_size::Object<T>* obj) {
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
void RB_tree_with_size<T>::Right_Rotate(RB_tree_with_size::Object<T>* obj) {
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


int main()
{
    RB_tree_with_size<int> tree(-1);
    tree.RB_Insert(5);
    tree.RB_Insert(34);
    tree.RB_Insert(256);
    tree.RB_Insert(29);
    tree.RB_Insert(72);
    tree.RB_Insert(2);
    tree.RB_Insert(25);
    tree.RB_Insert(6);

    //std::cout << tree.root->left_son->m_key;
    tree.RB_Inorder_Walk(dynamic_cast<RB_tree_with_size<int>::Object_s<int> *>(tree.root));
    std::cout << '\n';
    tree.RB_Delete(dynamic_cast<RB_tree_with_size<int>::Object_s<int>*>(tree.root));
    tree.RB_Inorder_Walk(dynamic_cast<RB_tree_with_size<int>::Object_s<int>*>(tree.root));
}



