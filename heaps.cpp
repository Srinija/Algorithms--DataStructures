//Finding the median of a stream of integers
//  main.cpp
//  heaps
//
//  Created by srinija on 9/14/14.
//

#include <iostream>
#include<fstream>
using namespace std;

class heaps{
private:
    int big[5001];
    int small[5001];
    int big_index=0;
    int small_index=0;
    void insert_big(int num);
    void insert_small(int num);
    int extract_min();
    int extract_max();
    void swap(int*,int*);
    void check_balance();
    
public:
    void insert(int num);
    int get_median();
};


int main()
{
    heaps heap;
    ifstream myfile ("Median.txt");
    long sum=0;
    if (myfile.is_open())
    {
        int num;
        while(myfile>>num)
        {
            heap.insert(num);
            sum+=heap.get_median();
        }
        myfile.close();
    }
    else cout << "Unable to open file";
    
    
    cout<<"The modulo sum is: "<<sum%10000<<endl;
}


void heaps::insert(int num)
{
    if(big_index==0&&small_index==0)
    {
        big[1]=num;
        big_index++;
    }
    else if(small_index==0)
    {
        if(num>big[1])
        {
            small[1]=big[1];
            big[1]=num;
        }
        else
        {
            small[1]=num;
        }
        small_index++;
    }
    
    else
    {
        if(num>big[1])
            insert_big(num);                     //insert in big
        else if(num<small[1])
            insert_small(num);
        else
        {
            if(big_index>small_index)
                insert_small(num); //insert in small
            else
                insert_big(num);
        }
    }
    check_balance();
}


void heaps::insert_big(int num)
{
    big[big_index+1]=num;
    big_index++;
    int i=big_index;
    while(big[i]<big[i/2])
    {
        swap(&big[i],&big[i/2]);
        i=i/2;
    }
}


void heaps::insert_small(int num)
{
    small[small_index+1]=num;
    small_index++;
    int i=small_index;
    while(small[i]>small[i/2])
    {
        swap(&small[i],&small[i/2]);
        i=i/2;
    }
}


void heaps::check_balance()
{
    if(big_index>small_index+1)
    {
        insert_small(extract_min());
    }
    if (small_index>big_index+1)
    {
        insert_big(extract_max()); //extra max from small -> insert in big
    }
}


int heaps::extract_min()
{
    int root=big[1];
    big[1]=big[big_index];
    big_index--;
    int i=1;
    while((2*i<=big_index&& big[i]>big[2*i])||((2*i+1)<=big_index && big[i]>big[2*i+1]))
    {
        if(big[i]>big[2*i]){
            swap(&big[i],&big[2*i]);
            i=2*i;
            
        }
        else{
            swap(&big[i],&big[2*i+1]);
            i=2*i+1;
        }
        
    }
    return root;
    
}


int heaps::extract_max()
{
    int root=small[1];
    small[1]=small[small_index];
    small_index--;
    int i=1;
    while((2*i<=small_index&& small[i]<small[2*i])||((2*i+1)<=small_index && small[i]<small[2*i+1]))
    {
        if(small[i]<small[2*i]){
            swap(&small[i],&small[2*i]);
            i=2*i;
            
        }
        else{
            swap(&small[i],&small[2*i+1]);
            i=2*i+1;
        }
        
    }
    return root;
    
}

void heaps::swap(int* p,int* q)
{
    int temp=*p;
    *p=*q;
    *q=temp;
}

int heaps::get_median()
{
    if(big_index==small_index)
        return small[1];
    else if(big_index==small_index+1)
        return big[1];
    else if(big_index+1==small_index)
        return small[1];
    else
    {
        std::cout<<"Something is wrong!!"<<std::endl;
        return -1;
    }
    
}
