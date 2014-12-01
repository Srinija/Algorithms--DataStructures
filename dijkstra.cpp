//  Working implementation of Dijkstra's Algorithm! (Naive one though... try to use heaps to speed up things!)
//Incase of changing the input file, change 'NUM_VERTICES' in the header
// For implemetation details: March 21st
//  main.cpp
//  Dijkstra's Algo
//
//  Created by srinija on 9/11/14.
//  Copyright (c) 2014 srinija. All rights reserved.
//

#include <iostream>
#include <fstream>
#include<sstream>
using namespace std;
//
//  dijkstra.h
//  Dijkstra's Algo
//
//  Created by srinija on 9/11/14.
//

#ifndef __Dijkstra_s_Algo__dijkstra__
#define __Dijkstra_s_Algo__dijkstra__

#include <iostream>

class dijkstra{
    
    static const int NUM_VERTICES=200;
    
private:
    struct edge{
        int vertex_no;
        int le;
        edge* next;
    };
    
    struct a{
        int val;
        int len;
    };
    
    edge* orig[NUM_VERTICES];
    a conq[NUM_VERTICES];
    int len_conq = 0;
    
    bool vertex_in_conq(int v);
    
    
public:
    dijkstra();
    void add_edge (int v, int e, int length);
    void find_paths();
    void print_lengths();
    
    
    
    
};

#endif /* defined(__Dijkstra_s_Algo__dijkstra__) */



int main(int argc, const char * argv[])
{

    dijkstra graph;
    /*graph.add_edge(1, 2, 3);
    graph.add_edge(1, 3, 5);
    graph.add_edge(2, 3, 1);
    graph.add_edge(2, 4, 2);
    graph.add_edge(3, 4, 50);
    graph.find_paths();
    graph.print_lengths();*/
    
    ifstream myfile ("testCaseDijkstraData.txt");
    string line;
    if (myfile.is_open())
    {
        string::size_type sz;
        while ( getline (myfile,line) )
        {
            int v= stoi(line, &sz);
            line=line.substr(sz);
            while(line!="\t\r"&& line!="\r"&&line!="")
                  {
                      int e=stoi(line,&sz);
                      line=line.substr(sz);
                      int length=stoi(line.substr(1),&sz);
                      line=line.substr(sz+1);
                      graph.add_edge(v,e,length);
                      
                  }
        }
        myfile.close();
    }
    
    else cout << "Unable to open file";
    graph.find_paths();
    graph.print_lengths();
 
}


//Implementation of the class


dijkstra::dijkstra()                 //As soon as the object is created,
{
    for (int i=0;i<NUM_VERTICES;i++)
        orig[i]=NULL;
    for (int i=0;i<NUM_VERTICES;i++)
    {
        conq[i].val=0;
        conq[i].len=0;
        
    }
}

void dijkstra::add_edge(int v, int e,int length)
{
    v--;
    e--;
    if (orig[v]==NULL)
    {
        orig[v]=new edge;
        orig[v]->vertex_no=e;
        orig[v]->le=length;
        orig[v]->next=NULL;
    }
    else
    {
        edge* ptr=orig[v];
        while (ptr->next!=NULL)
        {
            ptr=ptr->next;
        }
        ptr->next=new edge;
        ptr->next->vertex_no=e;
        ptr->next->le=length;
        ptr->next->next=NULL;
        
    }
}


void dijkstra::find_paths()
{
    int min=INT_MAX;
    int req_node=0;
    conq[0].val=0;
    conq[0].len=0;
    len_conq++;
    while (len_conq!=NUM_VERTICES)
    {
        min=INT_MAX;
        for(int i=0; i<len_conq;i++)
        {
            int vertex= conq[i].val;
            edge* ptr=orig[vertex];
            while (ptr!=NULL)
            {
                if((ptr->le)+conq[i].len<min && !vertex_in_conq(ptr->vertex_no))
                {
                    min=(ptr->le)+conq[i].len;
                    req_node=ptr->vertex_no;
                    
                }
                ptr=ptr->next;
            }
        }
        conq[len_conq].len=min;
        conq[len_conq].val=req_node;
        len_conq++;
    }
    
}


bool dijkstra::vertex_in_conq(int v)
{
    for(int i=0;i<len_conq;i++)
    {
        if(conq[i].val==v)
            return true;
        
    }
    return false;
}


void dijkstra::print_lengths()
{
    std::cout<<"Printing the lengths"<<std::endl;
    for(int i=0; i<NUM_VERTICES; i++)
        std::cout<<conq[i].val+1<<": "<<conq[i].len<<std::endl;
}
