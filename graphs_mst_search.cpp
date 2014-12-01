//Graphs -- MST algorithms and search algorithms
//  main.cpp
//  graph_search
//
//  Created by srinija on 10/4/14.
//

#include <iostream>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;

class graphs{
private:
    struct node{
        int edge;
        int weight;
        node* next;
    };
    
    struct edge_arr{
        int v1;
        int v2;
        int weight;
    };
    node** vertices;
    int num_vertices=10;
    int num_edges=0;
    void add_edge2(int v,int e);
    void add_edge2(int v,int e,int w);
    bool find_vertex(int v,int* conq,int index);
    edge_arr* edge_array();
    static bool  compare(edge_arr edge1, edge_arr edge2);
    
    struct obj;
    struct head_node{
        int size;
        obj* head;
        obj* tail;
    };
    struct obj{
        head_node* home;
        obj* next;
    };
    bool check_parent(obj* objects, int u, int v);
    obj* find(obj* objects, int u);
    void fuse(obj* objects,int u,int v);
    
    
    
    
public:
    graphs(int num);
    void add_edge(int v1,int v2);
    void add_edge(int v1,int v2,int w);
    void print_graph();
    void shortest_paths(int v);
    void depth_first(int v);
    bool check_bipartite();
    bool check_cycles();
    bool check_cycles2(int v, bool* visited);
    void prims_mst();
    void kruskal_mst();
};


int main(int argc, const char * argv[])
{
    
    graphs graph(5);
    graph.add_edge(0, 1);
    graph.add_edge(0, 4);
    graph.add_edge(1, 2);
    graph.add_edge(1, 3);
    graph.add_edge(1, 4);
    graph.add_edge(2, 3);
    graph.add_edge(3, 4);
    
    graph.print_graph();
    
    graph.shortest_paths(0);
    
    graph.depth_first(0);
    graph.prims_mst();
    graph.kruskal_mst();
    
    
    cout<<"Checking Bipartite: "<<graph.check_bipartite()<<endl;
    
    graphs graph2(6);
    graph2.add_edge(0,1);
    graph2.add_edge(0,5);
    graph2.add_edge(1,2);
    graph2.add_edge(2,3);
    graph2.add_edge(3,4);
    graph2.add_edge(4,5);
    
    
    cout<<"Checking Bipartite: "<<graph2.check_bipartite()<<endl;
    
    graphs graph3(5);
    graph3.add_edge(0,3,6);
    graph3.add_edge(0,1,2);
    graph3.add_edge(3,1,8);
    graph3.add_edge(3,4,9);
    graph3.add_edge(1,2,3);
    graph3.add_edge(1,4,5);
    graph3.add_edge(2,4,7);
    graph3.prims_mst();
    graph3.kruskal_mst();
    
    graphs graph4(9);
    graph4.add_edge(7,6,1);
    graph4.add_edge(8,2,2);
    graph4.add_edge(6,5,2);
    graph4.add_edge(0,1,4);
    graph4.add_edge(2,5,4);
    graph4.add_edge(8,6,6);
    graph4.add_edge(2,3,7);
    graph4.add_edge(7,8,7);
    graph4.add_edge(0,7,8);
    graph4.add_edge(1,2,8);
    graph4.add_edge(3,4,9);
    graph4.add_edge(5,4,10);
    graph4.add_edge(1,7,11);
    graph4.add_edge(3,5,14);
    graph4.prims_mst();
    graph4.kruskal_mst();
    
}

graphs::graphs(int num)
{
    num_vertices=num;
    vertices=new node*[num_vertices];
    for(int i=0;i<num_vertices;i++)
        vertices[i]=NULL;
}

void graphs::add_edge(int v1,int v2)
{
    num_edges++;
    add_edge2(v1,v2);
    add_edge2(v2,v1);
}
void graphs::add_edge2(int v,int e)
{
    if(vertices[v]==NULL)
    {
        vertices[v]=new node;
        vertices[v]->edge=e;
        vertices[v]->weight=1;
        vertices[v]->next=NULL;
        return;
    }
    node* temp=vertices[v];
    vertices[v]=new node;
    vertices[v]->edge=e;
    vertices[v]->weight=1;
    vertices[v]->next=temp;
}

void graphs::add_edge(int v1,int v2,int w)
{
    num_edges++;
    add_edge2(v1,v2,w);
    add_edge2(v2,v1,w);
}
void graphs::add_edge2(int v,int e,int w)
{
    if(vertices[v]==NULL)
    {
        vertices[v]=new node;
        vertices[v]->edge=e;
        vertices[v]->weight=w;
        vertices[v]->next=NULL;
        return;
    }
    node* temp=vertices[v];
    vertices[v]=new node;
    vertices[v]->edge=e;
    vertices[v]->weight=w;
    vertices[v]->next=temp;
}

void graphs::print_graph()
{
    for(int i=0;i<num_vertices;i++)
    {
        cout<<"Vertex: "<<i<<"-- ";
        node* ptr=vertices[i];
        while(ptr!=NULL)
        {
            cout<<ptr->edge<<"  ";
            ptr=ptr->next;
        }
        cout<<endl;
    }
}

void graphs::shortest_paths(int v) //Breadth first Search
{
    int shortest_paths[num_vertices];
    for(int i=0;i<num_vertices;i++)
        shortest_paths[i]=-1;
    shortest_paths[v]=0;
    queue<int> q;
    q.push(v);
    int top;
    while(!q.empty())
    {
        top=q.front();
        q.pop();
        node* ptr=vertices[top];
        while(ptr!=NULL)
        {
            if(shortest_paths[ptr->edge]==-1){
                shortest_paths[ptr->edge]=shortest_paths[top]+1;
                q.push(ptr->edge);
            }
            ptr=ptr->next;
        }
        
    }
    cout<<"Printing shortest path lengths from "<<v<<endl;
    for(int i=0;i<num_vertices;i++)
    {
        cout<<"Vertex: "<<i<<" : "<<shortest_paths[i];
        cout<<endl;
    }
    cout<<endl;
}

void graphs::depth_first(int v)
{
    stack<int> stk;
    stk.push(v);
    bool check[num_vertices];
    for(int i=0;i<num_vertices;i++)
        check[i]=false;
    check[v]=true;
    node* ptr;
    cout<<"Depth First Search: ";
    while(!stk.empty())
    {
        int top=stk.top();
        stk.pop();
        ptr=vertices[top];
        while(ptr!=NULL&&check[ptr->edge])
            ptr=ptr->next;
        if(ptr!=NULL){
            check[ptr->edge]=true;
            cout<<ptr->edge<<"  ";
            stk.push(ptr->edge);
        }
        
    }
    cout<<endl;
    
}

bool graphs::check_bipartite()
{
    int set[num_vertices];
    for(int i=0;i<num_vertices;i++)
    {
        set[i]=0;
    }
    queue<int> q;
    q.push(0);
    set[0]=1;
    while(!q.empty())
    {
        int top=q.front();
        q.pop();
        node* ptr=vertices[top];
        while(ptr!=NULL)
        {
            if(set[ptr->edge]==0){
                set[ptr->edge]=set[top]*-1;
                q.push(ptr->edge);
            }
            else if(set[ptr->edge]==set[top])
                return false;
            ptr=ptr->next;
        }
    }
    return true;
    
}



void graphs::prims_mst()
{
    int min_length=INT_MAX;
    int min_u = 0,min_v = 0;
    int conq[num_vertices];
    
    edge_arr mst[num_vertices];
    conq[0]=0;
    int index=1;
    while(index!=num_vertices)
    {
        min_length=INT_MAX;
        for(int i=0;i<index;i++)
        {
            node* ptr=vertices[conq[i]];
            while(ptr!=NULL)
            {
                if(ptr->weight<min_length)
                {
                    if(!find_vertex(ptr->edge,conq,index))
                    {
                        min_length=ptr->weight;
                        min_u=conq[i];
                        min_v=ptr->edge;
                        
                    }
                }
                ptr=ptr->next;
                
            }
        }
        conq[index]=min_v;
        mst[index].v1=min_u;
        mst[index].v2=min_v;
        mst[index].weight=min_length;
        index++;
        
    }
    cout<<"Printing Prim's MST: "<<endl;
    for(int i=1;i<num_vertices;i++)
    {
        cout<<mst[i].v1<<", "<<mst[i].v2<<" Weight: "<<mst[i].weight<<endl;
    }
}

bool graphs::find_vertex(int v,int* conq,int index)
{
    for(int i=0;i<index;i++)
    {
        if(conq[i]==v)
            return true;
    }
    return false;
}





void graphs::kruskal_mst()
{
    edge_arr* edges=edge_array();
    edge_arr mst[num_edges];
    int mst_index=0;
    sort(edges, edges+num_edges, graphs::compare);
    obj objects[num_vertices];
    for(int i=0;i<num_vertices;i++)
    {
        objects[i].home=new head_node;
        objects[i].next=NULL;
        objects[i].home->size=1;
        objects[i].home->head=&objects[i];
        objects[i].home->tail=&objects[i];
    }
    
    for(int i=0;i<num_edges;i++)
    {
        int u=edges[i].v1;
        int v=edges[i].v2;
        if(!check_parent(objects,u,v)){
            mst[mst_index].v1=u;
            mst[mst_index].v2=v;
            mst[mst_index].weight=edges[i].weight;
            mst_index++;
            fuse(objects,u,v);
        }
    }
    cout<<"Printing Kruskal's MST: "<<endl;
    for(int i=0;i<mst_index;i++)
    {
        cout<<mst[i].v1<<"  "<<mst[i].v2<<" Weight: "<<mst[i].weight<<endl;
    }
}



bool graphs::check_parent(obj* objects, int u, int v)
{
    if(find(objects,u)==find(objects,v)) return true;
    return false;
}

graphs::obj* graphs::find(obj* objects, int u)
{
    return objects[u].home->head;
}

void graphs::fuse(obj* objects,int u,int v)
{
    head_node* h1=objects[u].home;
    head_node* h2=objects[v].home;
    int s1=objects[u].home->size;
    int s2=objects[v].home->size;
    
    if(s1<s2)
    {
        obj* ptr=h1->head;
        while(ptr!=NULL)
        {
            ptr->home=h2;
            ptr=ptr->next;
        }
        h2->tail->next=h1->head;
        h2->tail=h1->tail;
        
    }
    else{
        obj* ptr=h2->head;
        while(ptr!=NULL)
        {
            ptr->home=h1;
            ptr=ptr->next;
        }
        h1->tail->next=h2->head;
        h1->tail=h2->tail;
    }
}

bool  graphs::compare(edge_arr edge1, edge_arr edge2)
{
    return edge1.weight<edge2.weight;
}



graphs::edge_arr* graphs::edge_array()
{
    edge_arr* edges=new edge_arr[num_edges];
    int index=0;
    for(int i=0;i<num_vertices;i++)
    {
        node* ptr=vertices[i];
        while(ptr!=NULL)
        {
            if(i<ptr->edge)
            {
                edges[index].v1=i;
                edges[index].v2=ptr->edge;
                edges[index].weight=ptr->weight;
                index++;
            }
            ptr=ptr->next;
            
        }
    }
    return edges;
    
}