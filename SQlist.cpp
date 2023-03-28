#include<bits/stdc++.h>
using namespace std;

class data
{
    public:
        int num;
};

class List
{
    private:

        data * q;
        int l_size;
        int l_lenth;

    public:
        
        /// @brief this function is to create the list
        List(int size)
        {
            q = (data*)malloc(sizeof(data)*size);
            if (NULL==q)
            {
                cerr<<"error malloc"<<endl;
            }
            l_size = size;
            l_lenth = 0;
        }

        /// @brief this function is to init the list
        void initList()
        {
            int lenth;
            cout<<"please input the lenth of the list:";
            cin>>lenth;
            int num;
            cout<<"please input the data of list:"<<endl;
            for (int i = 0; i < lenth; i++)
            {                
                cin>>num;
                q[i].num = num;
                if (i < l_size-1)
                {
                    l_lenth++;
                }
            }
        }

        /// @brief this function is to print the list
        void printList()
        {
            printf("l_lenth = %d\n",l_lenth);
            for (int i = 0; i < l_lenth; i++)
            {
                printf("%d ",q[i].num);
            }
            printf("\n");
        }

        /// @brief this function is to find the data in the list
        /// @param num the data to find
        /// @return the pos of the data or -1 if not find
        int find_(int num)
        {
            if ((num < q[0].num and q[0].num < q[1].num)
            or (num > q[0].num and q[0].num > q[1].num)
            )
            {
                return 0;
            }

            for (int i = 0; i < l_lenth; i++)
            {
                
                if (q[i].num == num)
                {
                    return i;
                }
            }
            return -1;
        }

        /// @brief this function is to insert the data in the list
        /// @param num the data to insert
        /// @param pos the pos to insert
        void insertList(int num,int pos)
        {
            if (pos > l_lenth)
            {
                cerr<<"error pos"<<endl;
                return;
            }
            for (int i = l_lenth; i > pos; i--)
            {
                q[i].num = q[i-1].num;
            }
            q[pos].num = num;
            l_lenth++;
        }

        /// @brief this function is to delete the data in the list
        /// @param pos the pos to delete
        void deleteList(int pos)
        {
            if (pos > l_lenth)
            {
                cerr<<"error pos"<<endl;
                return;
            }
            for (int i = pos; i < l_lenth; i++)
            {
                q[i].num = q[i+1].num;
            }
            l_lenth--;
        }

        /// @brief this function is to free the list
        void freeList()
        {
            free(q);
        }
        
        /// @brief this function is to get the l_lenth of the list
        /// @return the l_lenth of the list
        int get_l_lenth()
        {
            return l_lenth;
        }

        /// @brief this function is to get the l_size of the list
        /// @return the l_size of the list
        int get_l_size()
        {
            return l_size;
        }

        /// @brief this function is to get the data in the list
        /// @param pos the pos of the data
        int get_data(int pos)
        {
            return q[pos].num;
        }
        
        /// @brief this function is to delete the neg data in the list
        /// @return the count of the neg data
        int del_neg()
        {
            int count = 0;
            for (int i = 0; i < l_lenth; i++)
            {
                if (q[i].num < 0)
                {
                    deleteList(i);
                    i--;
                    count++;
                }
            }
            return count;
        }

};

/// @brief this function is to merge two list
/// @param p the first list
/// @param q the second list
/// @return the new list after merge
List * mergeList(List p,List q,double *mid)
{
    int l_lenth = p.get_l_lenth() + q.get_l_lenth();
    List * r = new List(l_lenth);
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < p.get_l_lenth() and j < q.get_l_lenth())
    {
        if (p.get_data(i) < q.get_data(j))
        {
            r->insertList(p.get_data(i),k);
            i++;
            k++;
        }
        else
        {
            r->insertList(q.get_data(j),k);
            j++;
            k++;
        }
    }
    while (i < p.get_l_lenth())
    {
        r->insertList(p.get_data(i),k);
        i++;
        k++;
    }
    while (j < q.get_l_lenth())
    {
        r->insertList(q.get_data(j),k);
        j++;
        k++;
    }
    
    int len = r->get_l_lenth();
    if (len%2==0)
    {
		*mid = (r->get_data(len/2) + r->get_data(len/2 - 1)) / 2;
	}
	else
	{
		*mid = r->get_data(len/2);
	}
    return r;
}