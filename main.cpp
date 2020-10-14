#include<bits/stdc++.h>
using namespace std;
#define NODE_SIZE 10
class node
{
    public:
        //bool visited[NODE_SIZE];
        vector<int> consider;
        int g,h,f;
        // int parent;
        // int position;
        vector<int> ans;
//    public:
//        node& operator = (const node &t)
//    {
//        // cout<<"Assignment operator called "<<endl;
//        return *this;
//    }
};
class myComparator
{
public:
    int operator() (const node& p1, const node& p2)
    {
        return p1.f < p2.f;
    }
};

int minKey(int key[], bool mstSet[],int V)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}


int calculate_hn(int matrix[][NODE_SIZE], const node &newnode)
{
    int V=newnode.consider.size();
    int new_matrix[newnode.consider.size()][newnode.consider.size()];
    int i=0;
    for (int x : newnode.consider)
    {
        int j=0;
        for (int y : newnode.consider)
        {
            new_matrix[i][j]=matrix[x][y];
            j++;
        }
        i++;
    }


    // Array to store constructed MST
    int parent[V];

    // Key values used to pick minimum weight edge in cut
    int key[V];

    // To represent set of vertices included in MST
    bool mstSet[V];

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;


    key[0] = 0;
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++)
    {

        int u = minKey(key, mstSet,V);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;


        for (int v = 0; v < V; v++)


            if (new_matrix[u][v] && mstSet[v] == false && new_matrix[u][v] < key[v])
                parent[v] = u, key[v] = new_matrix[u][v];
    }
    int MST=0;
    for (int i = 1; i < V; i++)
        MST=MST+new_matrix[i][parent[i]];
    return MST;
}

vector<int> A_star(priority_queue <node, vector<node>, myComparator>  min_heap,int matrix[NODE_SIZE][NODE_SIZE])
{
    while(min_heap.size()>0)
    {
        node check;
        check=min_heap.top();
        min_heap.pop();
        if(check.consider.size()==0)
            return check.ans;
        for (int i = 0; i < check.consider.size(); i++)
        {
            node newnode;
            newnode=check;
            newnode.g=newnode.g+matrix[newnode.ans.back()][check.consider[i]];

            //newnode.visited[check.consider[i]]=true;
            newnode.ans.push_back(check.consider[i]);
            newnode.consider.erase(newnode.consider.begin()+i);

            if(newnode.consider.size()==0)
                newnode.h=matrix[newnode.ans.back()][newnode.ans.front()];
            else if(newnode.consider.size()==1)
                newnode.h=matrix[newnode.ans.back()][newnode.consider[0]];
            else if(newnode.consider.size()>1)
                newnode.h=calculate_hn(matrix,newnode);
            newnode.f=newnode.g+newnode.h;
            min_heap.push(newnode);
        }


    }
}

int main()
{
    priority_queue <node, vector<node>, myComparator>  min_heap;
    node start ;
//    for(int i=0;i<NODE_SIZE;i++)
//        start.visited[i]=false;
    start.f=0;
    start.g=0;
    start.h=0;//starting node
    start.ans.push_back(0);
    //start.visited[0]=true;
    for(int i=1;i<NODE_SIZE;i++)
        start.consider.push_back(i);
    min_heap.push(start);
    int matrix[NODE_SIZE][NODE_SIZE]={
            {0,43,77,88,30,10,74,73,18,23},
            {43,0,71,46,58,73,4,65,83,8},
            {77,71,0,28,97,24,75,67,76,66},
            {88,46,28,0,66,26,53,26,73,58},
            {30,58,97,66,0,31,88,31,32,30},
            {10,73,24,26,31,0,85,54,60,10},
            {74,4,75,53,88,85,0,38,76,64},
            {73,65,67,26,31,54,38,0,24,29},
            {18,83,76,73,32,60,76,24,0,50},
            {23,8,66,58,30,10,64,29,50,0},
    };

    vector<int> list=A_star(min_heap,matrix);
//     cout <<"\n"<<list.size();
     for(int i=0;i<list.size();i++)
     cout<< list[i]<<"--> ";
     cout<<"0";

}