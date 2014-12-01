//Question1:
//Question 2:Reversing a stack using recursion
//Question 3: Special Stack - has a getMin function with O(1)
//  main.cpp
//  stack_applications
//
//  Created by srinija on 10/1/14.
//  Copyright (c) 2014 srinija. All rights reserved.
//

#include <iostream>
#include<stack>

using namespace std;
int* next_greater(int *arr,int size);
void reverse_stack(stack<int> &stk1);
void reverse_stack_2(stack<int> &stk1, stack<int> &stk2);
int* get_span(int* price, int size);

class special_stack{
private:
    struct node{
        int value;
        node* next;
    };
    
    node* top1=NULL;
    node* top2=NULL;
    
    
public:
    void push(int num);
    int top();
    void pop();
    int get_min();
};


int main(int argc, const char * argv[])
{

    int arr[]={11,13,21,3};
    int size=sizeof(arr)/sizeof(int);

    int* result=next_greater(arr,size);
    for(int i=0;i<size;i++)
    {
        cout<<result[i]<<endl;
    }
    
    //Reversing a stack
    stack<int> stk1;
    for(int i=0;i<size;i++)
    {
        stk1.push(i);
    }
    
    reverse_stack(stk1);
    
    
    special_stack stk;
    stk.push(10);
    stk.push(20);
    stk.push(15);
    stk.push(5);
    stk.pop();
    stk.pop();
    int min=stk.get_min();
    cout<<"The min is: "<<min<<endl;
    
    //The Stock Span Problem
    int price[]={100, 80, 60, 70, 60, 75, 85};
    int size2=sizeof(price)/sizeof(price[0]);
    int* span=get_span(price,size2);
    cout<<"printing the spans: "<<endl;
    for(int i=0;i<size2;i++)
    {
        cout<<span[i]<<"  ";
    }
    cout<<endl;
    
    return 0;
}

int* next_greater(int *arr,int size)
{
    int* result=new int[size];
    stack<int> stk;
    stk.push(arr[size-1]);
    result[size-1]=-1;
    for(int i=size-2;i>=0;i--)
    {
        int number=arr[i];
       
       if(arr[i]>stk.top())
           {
               while(!stk.empty()&&arr[i]>stk.top())
                   stk.pop();
           }
        if(stk.empty())
           result[i]=-1;
        else
           result[i]=stk.top();
        stk.push(arr[i]);
    }
    return result;
}

void reverse_stack(stack<int> &stk1)
{
    stack<int> stk2;
    
    reverse_stack_2(stk1,stk2);
    while(!stk2.empty())
    {
        cout<<stk2.top()<<endl;
        stk2.pop();
    }
}

void reverse_stack_2(stack<int> &stk1, stack<int> &stk2)
{
    if(stk1.empty())
        return;
    int num=stk1.top();
    stk1.pop();
    stk2.push(num);
    reverse_stack_2(stk1,stk2);
}

int* get_span(int* price, int size)
{
    int* span=new int[size];
    span[0]=1;
    stack<int> index_stack;
    index_stack.push(0);
    for(int i=1;i<size;i++)
    {
        while(!index_stack.empty()&&price[index_stack.top()]<price[i])
        {
            index_stack.pop();
        }
        if(index_stack.empty())
            span[i]=i+1;
        else
            span[i]=i-index_stack.top();
        index_stack.push(i);
        
    }
    return span;
}

void special_stack::push(int num)
{
    if(top1==NULL)
    {
        top1=new node;
        top1->value=num;
        top1->next=NULL;
        top2=new node;
        top2->value=num;
        top2->next=NULL;
    }
    else
    {
        node* temp1=top1;
        node* temp2=top2;
        top1=new node;
        top1->value=num;
        top1->next=temp1;
        if(num<top2->value)
        {
            top2=new node;
            top2->value=num;
            top2->next=temp2;
        }
        else{
            num=top2->value;
            top2=new node;
            top2->value=num;
            top2->next=temp2;
        }
    }
}


int special_stack::top()
{
    return top1->value;
}

void special_stack::pop()
{
    node* temp1=top1;
    node* temp2=top2;
    top1=top1->next;
    top2=top2->next;
    delete temp1;
    delete temp2;
    temp1=NULL;
    temp2=NULL;
}

int special_stack::get_min()
{
    return top2->value;

}




