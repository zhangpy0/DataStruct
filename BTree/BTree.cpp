#include "../Data/Data.cpp"
#include "../Array/Array.cpp"
#include "../Queue/Queue.cpp"
#include "../Stack/Stack.cpp"
#include<stdexcept>

#define In_INT 1
#define Pre_INT 2
#define Post_INT 3
#define In_CH 4
#define Pre_CH 5
#define Post_CH 6
#define Pre_Q 7

template<typename T>
class node
{
public:
    Data<T> data;
    node<T> *left;
    node<T> *right;

    node();
    node(T data);
    ~node();

    void insert(T data);
};

template<typename T>
class BTree
{
protected:
    node<T> *root;
    size_t BT_size;
    size_t BT_depth;

public:
    BTree();
    size_t size();
    size_t depth();
    
    void InOrder(node<T> *root, void (*visit)(node<T> *p, Array<T> &arr), Array<T> &arr);
    void PreOrder(node<T> *root, void (*visit)(node<T> *p, Array<T> &arr), Array<T> &arr);
    void PostOrder(node<T> *root, void (*visit)(node<T> *p, Array<T> &arr), Array<T> &arr);
    void LayerOrder(node<T> *root, void (*visit)(node<T> *p, Array<T> &arr), Array<T> &arr);

    void PreCreate(Array<T> &arr);
};

template<typename T>
node<T>::node()
{
    left = nullptr;
    right = nullptr;
}

template<typename T>
node<T>::node(T data)
{
    this->data = data;
    left = nullptr;
    right = nullptr;
}

// TODO: 记得检查内存，会不会内存泄漏
template<typename T>
node<T>::~node()
{
    delete left;
    delete right;
}

template<typename T>
void node<T>::insert(T val)
{
    if 
}


template<typename T>
BTree<T>::BTree()
{
    root = nullptr;
    BT_size = 0;
    BT_depth = 0;
}

template<typename T>
size_t BTree<T>::size()
{
    return BT_size;
}

template<typename T>
size_t BTree<T>::depth()
{
    return BT_depth;
}

template<typename T>
void BTree<T>::InOrder(node<T> *root, void (*visit)(node<T> *p, Array<T> &arr), Array<T> &arr)
{
    if (root == nullptr)
    {
        return;
    }
    InOrder(root->left, visit, arr);
    visit(root, arr);
    InOrder(root->right, visit, arr);
}

template<typename T>
void BTree<T>::PreOrder(node<T> *root, void (*visit)(node<T> *p, Array<T> &arr), Array<T> &arr)
{
    if (root == nullptr)
    {
        return;
    }
    visit(root, arr);
    PreOrder(root->left, visit, arr);
    PreOrder(root->right, visit, arr);
}

template<typename T>
void BTree<T>::PostOrder(node<T> *root, void (*visit)(node<T> *p, Array<T> &arr), Array<T> &arr)
{
    if (root == nullptr)
    {
        return;
    }
    PostOrder(root->left, visit, arr);
    PostOrder(root->right, visit, arr);
    visit(root, arr);
}

template<typename T>
void BTree<T>::LayerOrder(node<T> *root, void (*visit)(node<T> *p, Array<T> &arr), Array<T> &arr)
{
    Queue<node<T> *> q;
    node<T> *p = root;
    q.push(p);
    while (!q.empty())
    {
        p = q.pop();
        visit(p, arr);
        if (p->left != nullptr)
        {
            q.push(p->left);
        }
        if (p->right != nullptr)
        {
            q.push(p->right);
        }
    }
}

template<typename T>
void BTree<T>::PreCreate(Array<T> &arr)
{
    if (arr.empty() || root != nullptr)
    {
        return;
    }
    Stack<node<T> *> s;
    node<T> *p = nullptr;
    node<T> *q = nullptr;
    
}
