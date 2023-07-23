#include<bits/stdc++.h>
using std::queue,std::stack,std::pair,std::vector,std::cout,std::endl,std::cin,std::max,std::unordered_map;

#define In_INT 1
#define Pre_INT 2
#define Post_INT 3
#define In_CH 4
#define Pre_CH 5
#define Post_CH 6
#define Pre_Q 7

class data
{
public:
    int num;
    char ch;
};

class node
{
public:
    data DATA;
    node * left;
    node * right;

    node()
    {
        left = NULL;
        right = NULL;
    }

    node(int value)
    {
        DATA.num = value;
        left = NULL;
        right = NULL;
    }

    node(char c)
    {
        DATA.ch = c;
        left = NULL;
        right = NULL;
    }

    bool insert(int val)
    {
        if (left == NULL)
        {
            left = new node(val);
            return true;
        }
        else if (right == NULL)
        {
            right = new node(val);
            return true;
        }
        return false;
    }

    bool SortInsert(int val)
    {
        if (val < DATA.num)
        {
            if (left == NULL)
            {
                left = new node(val);
                return true;
            }
            else
            {
                return left->SortInsert(val);
            }
        }
        else if (val > DATA.num)
        {
            if (right == NULL)
            {
                right = new node(val);
                return true;
            }
            else
            {
                return right->SortInsert(val);
            }
        }
        return false;
    }

    bool SortInsert(pair<int,char> p)
    {
        int val = p.first;
        char ch = p.second;
        if (val < DATA.num)
        {
            if (left == NULL)
            {
                left = new node(val);
                left->DATA.ch = ch;
                return true;
            }
            else
            {
                return left->SortInsert(p);
            }
        }
        else if (val > DATA.num)
        {
            if (right == NULL)
            {
                right = new node(val);
                right->DATA.ch = ch;
                return true;
            }
            else
            {
                return right->SortInsert(p);
            }
        }
        return false;
    }
};

node * Create(queue<char> &q)
{
    if (q.empty())
    {
        return NULL;
    }
    char c = q.front();
    q.pop();
    if (c == '#')
    {
        return NULL;
    }
    else
    {
        node * temp = new node(c);
        temp->left = Create(q);
        temp->right = Create(q);
        return temp;
    }
}

class BTree
{
protected:
    node * root;
    int B_length;
    int B_depth;
public:
    BTree()
    {
        root = new node();
        B_length = 0;
        B_depth = 0;
    }

    BTree(int value)
    {
        root = new node(value);
        B_length = 1;
        B_depth = 1;
    }

    int getdepth(node * root)
    {
        if (root == NULL)
        {
            return 0;
        }
        else
        {
            int left = getdepth(root->left);
            int right = getdepth(root->right);
            return max(left,right) + 1;
        }
    }

    int depth()
    {
        B_depth = getdepth(root);
        return B_depth;
    }

    int length()
    {
        return B_length;
    }

    void insert(node *temp,int val)
    {
        temp->DATA.num = val;
        temp->left = new node();
        temp->right = new node();
        B_length++;
    }

    void Inorder(node *root, void (BTree::*visit)(node * temp))
    {
        if (root == NULL)
        {
            return;
        }
        else
        {
            Inorder(root->left, visit);
            (this->*visit)(root);
            Inorder(root->right, visit);
        }
    }

    void Preorder(node *root,void (BTree::*visit)(node * temp))
    {
        if (root == NULL)
        {
            return;
        }
        else
        {
            (this->*visit)(root);
            Preorder(root->left,visit);
            Preorder(root->right,visit);
        }
    }

    void Preorder(node *root,void (BTree::*visit)(node *temp,char c),queue<char> &q)
    {
        if (q.empty())
        {
            root = NULL;
            return;
        }
        char c = q.front();
        q.pop();
        if (c == '#')
        {
            root = NULL;
            return;
        }
        else
        {
            if (root == NULL)
            {
                root = new node();
            }
            (this->*visit)(root,c);
            Preorder(root->left,visit,q);
            Preorder(root->right,visit,q);
        }
    }

    void Preorder_Q(node *root,void (BTree::*visit)(node * temp))
    {
        stack<node *> s;
        node * temp = root;
        while (temp != NULL || !s.empty())
        {
            while (temp != NULL)
            {
                (this->*visit)(temp);
                s.push(temp);
                temp = temp->left;
            }
            if (!s.empty())
            {
                temp = s.top();
                s.pop();
                temp = temp->right;
            }
        }
    }

    void Preorder(node *root,void (BTree::*visit)(node * temp,unordered_map<int, char> &m),unordered_map<int, char> &m)
    {
        if (root == NULL)
        {
            return;
        }
        else
        {
            (this->*visit)(root,m);
            Preorder(root->left,visit,m);
            Preorder(root->right,visit,m);
        }
    }

    // 有点问题
    void Preorder(node *root,void (BTree::*visit)(node * temp,int val),queue<int> &q)
    {
        if (root == NULL)
        {
            return;
        }
        else
        {
            (this->*visit)(root,q.front());
            q.pop();
            Preorder(root->left,visit,q);
            Preorder(root->right,visit,q);
        }
    }

    void PreorderCreate(queue<char> &q)
    {
        root = Create(q);
    }

    void Postorder(node *root,void (BTree::*visit)(node * temp))
    {
        if (root == NULL)
        {
            return;
        }
        else
        {
            Postorder(root->left,visit);
            Postorder(root->right,visit);
            (this->*visit)(root);
        }
    }

    void Layerorder(node *root,void (*visit)(node * temp))
    {
        node * temp = root;
        queue<node *> q;
        q.push(temp);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            visit(temp);
            if (temp->left != NULL)
            {
                q.push(temp->left);
            }
            if (temp->right != NULL)
            {
                q.push(temp->right);
            }
        }
    }   

    void singlePrint_INT(node * temp)
    {
        cout << temp->DATA.num << " ";
    }

    void singlePrint_CH(node * temp)
    {
        cout << temp->DATA.ch << " ";
    }

    void singleReset(node * temp,unordered_map<int,char> &m)
    {
        temp->DATA.ch = m[temp->DATA.num];
    }
    
    void print(int index)
    {
        switch (index)
        {
        case In_INT:
            Inorder(root,singlePrint_INT);
            break;
        case Pre_INT:
            Preorder(root,singlePrint_INT);
            break;
        case Post_INT:
            Postorder(root,singlePrint_INT);
            break;
        case In_CH:
            Inorder(root,singlePrint_CH);
            break;
        case Pre_CH:
            Preorder(root,singlePrint_CH);
            break;
        case Post_CH:
            Postorder(root,singlePrint_CH);
            break;
        case Pre_Q:
            Preorder_Q(root,singlePrint_INT);
            break;
        default:
            break;
        }
    }

    void SortBTreeCreate(queue<int> &q)
    {
        int val = q.front();
        q.pop();
        root->DATA.num = val;
        B_length++;
        while (!q.empty() and root->SortInsert(q.front()))
        {
            q.pop();
            B_length++;
        }
    }

    void SortBTreeCreate(queue<pair<int,char>> &q)
    {
        int val = q.front().first;
        char c = q.front().second;
        q.pop();
        root->DATA.num = val;
        root->DATA.ch = c;  
        B_length++;
        while (!q.empty() and root->SortInsert(q.front()))
        {
            q.pop();
            B_length++;
        }
    }

    node * SortBTreeSearch(int val)
    {
        node * temp = root;
        while (temp != NULL)
        {
            if (temp->DATA.num == val)
            {
                return temp;
            }
            else if (temp->DATA.num > val)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        return NULL;
    }

    void ReConstruct(vector<char>& pre, vector<char>& in)
    {
        if (pre.size() != in.size())
        {
            return;
        }

        unordered_map<char, int> in_map;
        unordered_map<int, char> in_map_t;
        for (int i = 0; i < in.size(); i++)
        {
            in_map[in[i]] = i;
            in_map_t[i] = in[i];
        }
        queue<int> q;
        for (int i = 0; i < pre.size(); i++)
        {
            q.push(in_map[pre[i]]);
        }
        /*
        queue<pair<int, char>> q;
        for (int i = 0; i < pre.size(); i++)
        {
            q.push(make_pair(in_map[in[i]], pre[i]));
        }
        */
        SortBTreeCreate(q);
        Preorder(root,singleReset,in_map_t);
    }

    ~BTree()
    {
        delete root;
        B_length = 0;
        B_depth = 0;
    }
};

class AVLnode:public node
{
public:
    AVLnode *left;
    AVLnode *right;
    AVLnode *parent;
    int balance_factor;

    AVLnode(int val) : node(val)
    {
        left = NULL;
        right = NULL;
        parent = NULL;
        balance_factor = 0;
    }

    void leftRotate(AVLnode **root)
    {
        AVLnode *temp = right;
        if (parent != NULL)
        {
            if (parent->left == this)
            {
                parent->left = right;
            }
            else
            {
                temp->parent = parent;
                parent->right = right;
            }
            right = temp->left;
            temp->left = this;
            this->parent = temp;
            if (right != NULL)
            {
                right->parent = this;
            }
        }
        else
        {
            right->parent = NULL;
            *root = right;
            right = temp->left;
            temp->left = this;
            this->parent = temp;
            if (right != NULL)
            {
                right->parent = this;
            }
        }
        this->balance_factor = 0;
        temp->balance_factor = 0;
    }

    void rightRotate(AVLnode **root)
    {
        AVLnode *temp = left;
        if (parent != NULL)
        {
            if (parent->left == this)
            {
                parent->left = left;
            }
            else
            {
                temp->parent = parent;
                parent->right = left;
            }
            left = temp->right;
            temp->right = this;
            this->parent = temp;
            if (left != NULL)
            {
                left->parent = this;
            }
        }
        else
        {
            left->parent = NULL;
            *root = left;
            left = temp->right;
            temp->right = this;
            this->parent = temp;
            if (left != NULL)
            {
                left->parent = this;
            }
        }
        this->balance_factor = 0;
        temp->balance_factor = 0;
    }

    bool insert(int val,AVLnode **root)
    {
        AVLnode *temp = NULL;
        bool flag = false;
        if (val == DATA.num)
        {
            return false;
        }
        else if (val < DATA.num)
        {
            if (left == NULL)
            {
                left = new AVLnode(val);
                temp = left;
                left->parent = this;
                flag = true;
            }
            else
            {
                flag = left->insert(val,root);
            }
        }
        else
        {
            if (right == NULL)
            {
                right = new AVLnode(val);
                temp = right;
                right->parent = this;
                flag = true;
            }
            else
            {
                flag = right->insert(val,root);
            }
        }
        if (!flag)
        {
            return false;
        }
        if (temp != NULL) 
        {
            while (temp->parent != NULL)
            {
                if (temp->parent->left == temp)
                {
                    temp->parent->balance_factor--;
                }
                else if (temp->parent->right == temp)
                {
                    temp->parent->balance_factor++;
                }
                if (temp->parent->balance_factor == 0)
                {
                    break;
                }
                else if (temp->parent->balance_factor == 1 || temp->parent->balance_factor == -1)
                {
                    temp = temp->parent;
                }
                else if (temp->parent->balance_factor == 2 || temp->parent->balance_factor == -2)
                {
                    if (temp->parent->balance_factor == 2)
                    {
                        if (temp->balance_factor == 1)
                        {
                            temp->parent->leftRotate(root);
                        }
                        else if (temp->balance_factor == -1)
                        {
                            temp->left->rightRotate(root);
                            temp->parent->leftRotate(root);
                        }
                    }
                    else if (temp->parent->balance_factor == -2)
                    {
                        if (temp->balance_factor == -1)
                        {
                            temp->parent->rightRotate(root);
                        }
                        else if (temp->balance_factor == 1)
                        {
                            temp->right->leftRotate(root);
                            temp->parent->rightRotate(root);
                        }
                    }
                    break;
                }  
            }
        }
        return true;
    }
};

class AVLTree:public BTree
{
    public:
    AVLnode *AVLroot;

    AVLTree() : BTree()
    {
        AVLroot = NULL;
    }

    void rootRotate(AVLnode *temp)
    {
        AVLroot = temp;
    }

    void Create(vector<int> &v)
    {
        for (int i = 0; i < v.size(); i++)
        {
            if (AVLroot == NULL)
            {
                AVLroot = new AVLnode(v[i]);
            }
            else
            {
                AVLroot->insert(v[i],&AVLroot);
            }
        }
        Trans(AVLroot,root);
    }

    void Trans(AVLnode *temp,node *root)
    {
        if (temp == NULL)
        {
            root = NULL;
            return;
        }
        else
        {
            root->DATA.num = temp->DATA.num;
            if (temp->left != NULL)
            {
                root->left = new node();
            }
            Trans(temp->left,root->left);
            if (temp->right != NULL)
            {
                root->right = new node();
            }
            Trans(temp->right,root->right);
        }
    }

    ~AVLTree()
    {
        delete AVLroot;
    }
};