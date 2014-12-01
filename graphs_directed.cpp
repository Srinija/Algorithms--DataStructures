//
//  main.cpp
//  graphs_directed
//
//  Created by srinija on 10/4/14.
//  Copyright (c) 2014 srinija. All rights reserved.
//

#include <iostream>
using namespace std;

class graphs{
private:
    struct node{
        int edge;
        int weight;
        node* next;
    };
    node** vertex;
    int num_vert;
    void do_sort(node* ptr,int i,int* position,int* sort,bool* check);
    
    
public:
    graphs(int num);
    void add_edge(int v,int e);
    void add_edge(int v,int e,int w);
    void print_graph();
    int* topological_sort();
    void longest_path(int v);
};


int main(int argc, const char * argv[])
{

    graphs graph(6);
    graph.add_edge(5, 2);
    graph.add_edge(5, 0);
    graph.add_edge(4, 0);
    graph.add_edge(4, 1);
    graph.add_edge(2, 3);
    graph.add_edge(3, 1);
    graph.print_graph();
    graph.topological_sort();
    
    graphs graph2(6);
    graph2.add_edge(0, 1, 5);
    graph2.add_edge(0, 2, 3);
    graph2.add_edge(1, 3, 6);
    graph2.add_edge(1, 2, 2);
    graph2.add_edge(2, 4, 4);
    graph2.add_edge(2, 5, 2);
    graph2.add_edge(2, 3, 7);
    graph2.add_edge(3, 5, 1);
    graph2.add_edge(3, 4, -1);
    graph2.add_edge(4, 5, -2);
    
    graph2.longest_path(1);

  
}


graphs::graphs(int num)
{
    num_vert=num;
    vertex=new node*[num_vert];
    for(int i=0;i<num_vert;i++)
        vertex[i]=NULL;
}

void graphs::add_edge(int v,int e)
{
    node* temp=vertex[v];
    vertex[v]=new node;
    vertex[v]->edge=e;
    vertex[v]->weight=1;
    vertex[v]->next=temp;
    
}

void graphs::add_edge(int v,int e,int w)
{
    node* temp=vertex[v];
    vertex[v]=new node;
    vertex[v]->edge=e;
    vertex[v]->weight=w;
    vertex[v]->next=temp;
    
}

void graphs::print_graph()
{
    for(int i=0;i<num_vert;i++)
    {
        cout<<"Vertex: "<<i<<"-- ";
        node* ptr=vertex[i];
        while(ptr!=NULL)
        {
            cout<<ptr->edge<<"  ";
            ptr=ptr->next;
        }
        cout<<endl;
    }
}

int* graphs::topological_sort()
{
    int position=num_vert-1;
    int* sort=new int[num_vert];
    bool check[num_vert];
    for(int i=0;i<num_vert;i++)
        check[i]=false;
    for(int i=0;i<num_vert;i++)
    {
        if(check[i]==false)
            do_sort(vertex[i],i,&position,sort,check);
        
    }
    cout<<"Topological Sort results are: ";
    for(int i=0;i<num_vert;i++)
        cout<<"Position"<<i<<" vertex "<<sort[i]<<endl;
    return sort;
}

void graphs::do_sort(node* ptr,int i,int* position,int* sort,bool* check)
{
    check[i]=true;
    
    while(ptr!=NULL)
    {
        if(check[ptr->edge]==false)
            do_sort(vertex[ptr->edge],ptr->edge,position,sort,check);
        ptr=ptr->next;
    }
    sort[*position]=i;
    *position=*position-1;
    
}

void graphs::longest_path(int v)
{
    int* sort=topological_sort();
    int length[num_vert];
    for(int i=0;i<num_vert;i++)
        length[i]=INT_MIN;
    length[v]=0;
    int index=0;
    while(sort[index]!=v)
        index++;
    for(int i=index;i<num_vert;i++)
    {
        node* ptr=vertex[i];
        while(ptr!=NULL)
        {
            if(length[ptr->edge]<length[i]+ptr->weight)
                length[ptr->edge]=length[i]+ptr->weight;
            ptr=ptr->next;
        }
    }
    cout<<"The longest paths are: ";
    for(int i=0;i<num_vert;i++)
    {
        
        cout<<"vertex: "<<i<<" Length "<<length[i]<<endl;
    }
    
}

