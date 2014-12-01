//
//  main.cpp
//  sorting
//
//  Created by srinija on 10/9/14.
//  Copyright (c) 2014 srinija. All rights reserved.
//

#include <iostream>
using namespace std;

class sorting{
private:
    void swap(int* a,int* b);
    void insert_heap(int* heap,int index,int num);
    int heap_min(int* heap,int *index);
    void combine(int* arr,int size);
    
public:
    bool binary_search(int* arr,int size, int n);
    void bubble_sort(int* arr, int size);
    void print_array(int* arr, int size);
    void insertion_sort(int* arr, int size);
    void heap_sort(int* arr,int size);
    void merge_sort(int* arr,int size);
    
};


int main(int argc, const char * argv[])
{
    sorting obj;
    int arr[]={2, 3, 4, 10, 40};
    int size = sizeof(arr)/ sizeof(arr[0]);
    bool result=obj.binary_search(arr, size,3);
    result==true? cout<<"The element was found in the array\n":cout<<"The element was not found\n";
    int arr2[]={10,4,3,40,2};
    int arr3[] = {12, 11, 13, 5, 6, 7};
    obj.print_array(arr2, size);
    obj.merge_sort(arr2, size);
    obj.print_array(arr2, size);
    obj.print_array(arr3, size);
    obj.merge_sort(arr3, size);
    obj.print_array(arr3, size);

}


//
//  sorting.cpp
//  sorting
//
//  Created by srinija on 10/9/14.
//  Copyright (c) 2014 srinija. All rights reserved.
//

#include "sorting.h"
#include<iostream>
using namespace std;

bool sorting::binary_search(int* arr, int size,int n)
{
    if(size==0)
        return false;
    
    if(size==1)
    {
        return arr[0]==n? true:false;
    }
    
    int middle=size/2;
    if(arr[middle]==n)
        return true;
    
    else if(arr[middle]<n)
        return binary_search(&arr[middle+1], (size-1)/2, n);
    
    else
        return binary_search(arr, size/2, n);
    
}

void sorting::bubble_sort(int *arr, int size)
{
    bool check=true;
    while(check)
    {
        check=false;
        for(int i=0;i<size-1;i++,size--)
        {
            if(arr[i]>arr[i+1]){
                swap(&arr[i],&arr[i+1]);
                check=true;
            }
        }
    }
    
}

void sorting::insertion_sort(int *arr, int size)
{
    for(int i=1;i<size;i++)
    {
        int key=arr[i];
        int j=i-1;
        while(j>=0&&arr[j]>key)
        {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}

void sorting::swap(int* a,int* b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

void sorting::print_array(int* arr, int size)
{
    cout<<"Printing the array: ";
    for(int i=0;i<size;i++)
        cout<<arr[i]<<"  ";
    cout<<endl;
}

void sorting::heap_sort(int* arr, int size)
{
    int index=0;
    int* heap=new int[size];
    
    for(int i=0;i<size;i++)
    {
        insert_heap( heap, index, arr[i]);
        index++;
        
    }
    
    for(int i=0;i<size;i++)
    {
        arr[i]=heap_min(heap,&index);
    }
    
    
    
}

void sorting::insert_heap(int* heap,int index,int num)
{
    heap[index]=num;
    if(index==0) return;
    int i=index;
    while((i-1)/2>=0&&heap[i]<heap[(i-1)/2])
    {
        swap(&heap[i],&heap[(i-1)/2]);
        i=(i-1)/2;
    }
    
}

int sorting::heap_min(int* heap,int* index_ref)
{
    int index=*index_ref;
    if(index==1){
        return heap[0];
    }
    int min=heap[0];
    heap[0]=heap[index-1];
    
    (*index_ref)--;
    int i=0;
    while(((2*i+1)<index&&heap[i]>heap[2*i+1])||((2*i+2)<index&&heap[i]>heap[2*i+2]))
    {
        if(2*i+2<index){
            if(heap[2*i+1]<heap[2*i+2]){
                swap(&heap[i],&heap[2*i+1]);
                i=2*i+1;
            }
            else{
                swap(&heap[i],&heap[2*i+2]);
                i=2*i+2;
            }
        }
        else{
            if(heap[2*i+1]<heap[i]){
                swap(&heap[2*i+1],&heap[i]);
                i=2*i+1;
            }
        }
        
    }
    
    return min;
}


void sorting::merge_sort(int* arr,int size)
{
    if(size==0||size==1)
        return;
    merge_sort(arr,size/2);
    merge_sort(&arr[size/2],(size+1)/2);
    combine(arr,size);
}

void sorting::combine(int* arr,int size)
{
    int i=0,j=size/2,k=0;
    int* result=new int[size];
    for(k=0;k<size;k++)
    {
        if(i<(size)/2&&j<size)
        {
            if(arr[i]<arr[j]){
                result[k]=arr[i];
                i++;
            }
            else{
                result[k]=arr[j];
                j++;
            }
        }
        else{
            while(i<size/2)
            {
                result[k]=arr[i];
                i++;
            }
            while(j<size)
            {
                result[k]=arr[j];
                j++;
            }
        }
        
    }
    
    for(i=0;i<size;i++)
    {
        arr[i]=result[i];
    }
    
}






