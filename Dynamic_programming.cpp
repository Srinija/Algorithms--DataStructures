//
//  main.cpp
//  dp
//
//  Created by srinija on 10/23/14.
//  Copyright (c) 2014 srinija. All rights reserved.
//

#include <iostream>
using namespace std;

struct box{
    int length;
    int width;
    int height;
};

int max_sum_cont(int* arr, int size);
int min_cost_path(int arr[3][3], int m,int n);
int binomial_coeff(int n,int k);
int binomial_util(int** look_up,int n,int k);
int binomial_util2(int** look_up,int n,int k);
int matrix_multi(int* matrix, int n);
int get_min(int* matrix,int init,int final,int** A);
int longest_palin(char* palin,int size);
int word_wrap(int* word,int size,int line);
int word_wrap2(int* lword,int n,int M);
int cutting_rod(int* price,int size);
const int n=5;
int binary_matrix(int m,int matrix[][n]);
int min_jumps(int* arr,int size);
int box_stacking(box arr[],int n);
bool compare(box element1,box element2);
int knapsack(int w,int* weight,int* v,int n);
int long_inc_subsequence(int* arr,int n);
int long_com_subsequence(char* A, char* B,int a,int b);

int main(int argc, const char * argv[]) {
    int arr[]={-2, 1,-3, 4,-1, 2, 1,-5, 4};
    int size=sizeof(arr)/sizeof(arr[0]);
    int max_sum=max_sum_cont(arr, size);
    cout<<"The max_sum is: "<<max_sum<<endl;
    int arr2[3][3]={{1,2,3},{4,8,2},{1,5,3}};
    cout<<"Min cost path is: "<<min_cost_path(arr2,3,3)<<endl;
    cout<<"Coefficient of x^3 if n is 4 is: "<<binomial_coeff(1,0)<<endl;
    int p[] = {40, 20, 30, 10, 30} ;
    int size_p=sizeof(p)/sizeof(p[0]);
    cout<<"-------------------"<<endl;
    cout<<"The matrix multiplication result is: "<<matrix_multi(p,size_p)<<endl;//Answer is: 26000
    cout<<"-------------------"<<endl;

    char palin[]={'B','B','A','B','C','B','C','A','B'};
    int size_palin=sizeof(palin)/sizeof(palin[0]);
    cout<<"Length of longest Palindrome is: "<<longest_palin(palin,size_palin)<<endl;
    int word[]={7,2,1,4,4,4};
    int size_word=sizeof(word)/sizeof(word[0]);
    cout<<"Minimum cost of the line is: "<<word_wrap(word,size_word,15)<<endl;
    cout<<"Number 2: Minimum cost of the line is: "<<word_wrap2(word,size_word,15)<<endl;

    int rod[]={1,5,8,9,10,17,17,20};   //Answer is 22
    int size_rod=sizeof(rod)/sizeof(rod[0]);
    cout<<"Maximum value obtained by cutting the rod: "<<cutting_rod(rod,size_rod);
    int matrix[6][5]={{0,1,1,0,1},{1,1,0,1,0},{0,1,1,1,0},{1,1,1,1,0},{1,1,1,1,1},{0,0,0,0,0}};
    cout<<"The Maximum size square sub-matrix with all 1s is: "<<binary_matrix(5, matrix)<<endl;
    int jumps[]={1,3,5,8,9,2,6,7,6,8,9};
    cout<<"Minimum jumps from 1 to 9 is: "<<min_jumps(jumps,sizeof(jumps)/sizeof(jumps[0]))<<endl;
    box boxes[] = { {4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32} };
    
    cout<<"The maximum possible height of stack is: "
    <<box_stacking(boxes,sizeof(boxes)/sizeof(boxes[0]))<<endl;
    
    cout<<"Knapsack problem: ";
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int  W = 50;
    int n = sizeof(val)/sizeof(val[0]);
    cout<<"The best v value is: "<<knapsack(W,wt,val,n);
    
    int long_inc[] = { 10, 22, 9, 33, 21, 50, 41, 60 };
    cout<<"Longest increasing subsequence size is: "<<long_inc_subsequence(long_inc, sizeof(long_inc)/sizeof(long_inc[0]));
    
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";
    cout<<endl;
    int x = strlen(X);
    int y = strlen(Y);
    cout<<"Longest common subsequence: "<<long_com_subsequence(X, Y, x,y);
}

//KADANE'S ALGORITHM
/*This version doesnt allow 0 return value even in the case of negative arrays. */
int max_sum_cont(int* arr, int size)
{
    int max_sum=INT_MIN;
    int max_till=arr[0];
    for(int i=1;i<size;i++)
    {
        max_till=max(max_till+arr[i],arr[i]);
        if(max_till>max_sum)
            max_sum=max_till;
    }
    
    
        return max_sum;
    
}

//Min cost path
int min_cost_path(int arr[3][3], int m,int n)
{
    int** A=new int*[m];
    for(int i=0;i<m;i++)
        A[i]=new int[n];
    A[0][0]=arr[0][0];
    for(int j=1;j<n;j++)
    {
        A[0][j]=A[0][j-1]+arr[0][j];
    }
    for(int i=1;i<m;i++)
        A[i][0]=A[i-1][0]+arr[i][0];
    for(int i=1;i<m;i++)
    {
        for(int j=0;j<n;j++)
            A[i][j]=min(min(A[i-1][j],A[i][j-1]),A[i-1][j-1])+arr[i][j];
    }
    return A[m-1][n-1];
    
}

//Find the corresponding binomial coefficient
int binomial_coeff(int n,int k)
{
    int** look_up=new int*[n];
    for(int i=0;i<n;i++)
    {
        look_up[i]=new int[n];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            look_up[i][j]=0;
    }
    for(int i=0;i<n;i++)
        look_up[0][i]=1;
    for(int i=0;i<n;i++)
        look_up[i][i]=1;
    return binomial_util(look_up,n,k);
    
    
}

//Utility function for the above
int binomial_util(int** look_up,int n,int k)
{
    if(k==0||k==n)return 1;
    if(n==1)return 1;
    int coeff;
    coeff= binomial_util2(look_up,n-1,k-1)+binomial_util2(look_up,n-1,k);
    look_up[n-1][k-1]=coeff;
    return coeff;
}


int binomial_util2(int** look_up,int n,int k)
{
    if(look_up[n-1][k-1]!=0)return look_up[n-1][k-1];
    else {
        return binomial_util(look_up,n,k);
    }
}

int matrix_multi(int* matrix, int n)  //Incomplete
{
    
    
    int** A=new int*[n];
    for(int i=0;i<n;i++)
    {
        A[i]=new int[n];
    }
    for(int i=0;i<n;i++)
        A[i][0]=0;
    for(int i=0;i<n-2;i++)
    {
            A[i][1]=matrix[i]*matrix[i+1]*matrix[i+2];
    }
    for(int j=2;j<n;j++)
    {
        for(int i=0;i<n-j+1;i++)
        {
            int val;
            int min=INT_MAX;
            for(int k=i;k<j+i+1;k++){
                val=A[i][j]+A[i+1][j+1]+matrix[j]*matrix[k+1]*matrix[j+i+1];
                if(min>val)
                    min=val;
            }
            A[i][j]=min;
        }
    }
    return A[0][4];
}

//Longest palindrome in a given string
int longest_palin(char* palin,int size)
{
    int** p=new int*[size];
    for(int i=0;i<size;i++)
        p[i]=new int[size];
    for(int i=0;i<size;i++)
        p[i][i]=1;
    for(int j=1;j<size;j++)
    {
        for(int i=j-1;i>=0;i--)
        {
            if(palin[i]==palin[j])
                p[i][j]=2+p[i+1][j-1];
            else p[i][j]=max(p[i][j-1],p[i+1][j]);
        }
    }
    return p[0][size-1];
}

//Word wrap problem
int word_wrap(int* word,int size,int line)
{
    int* look_up=new int[size];
    look_up[size-1]=(line-word[size-1])*(line-word[size-1])*(line-word[size-1]);
    for(int i=size-2;i>=0;i--)
    {
        int gap=line;
        int j=i;
        int min_cost=INT_MAX;
        while(gap-word[j]>=0 && j<size)
        {
            gap=gap-word[j];
            min_cost=min(min_cost,gap*gap*gap+look_up[j+1]);
            j++;
            gap--;
        }
        look_up[i]=min_cost;
    }
    
    return look_up[0];
}

int word_wrap2(int* const lword,int n,int const M)
{
    int cost[n];
    cost[0]=(M-lword[0])*(M-lword[0])*(M-lword[0]);
    for(int i=1;i<n;i++)
    {
        int sum=lword[i];
        int mini=(M-lword[i])*(M-lword[i])*(M-lword[i])+cost[i-1];
        
        for(int j=1;j<=i&&sum+lword[i-j]+1<=M;j++)
        {
            sum=sum+lword[i-j]+1;
            if(i-j-1>=0)
                mini=min(mini,(M-sum)*(M-sum)*(M-sum)+cost[i-j-1]);
            else
                mini=min(mini,(M-sum)*(M-sum)*(M-sum));
        }
        
        cost[i]=mini;
       
    }

    return cost[n-1];
}


int cutting_rod(int* price,int size)
{
    int* A=new int[size];
    A[0]=price[0];
    for(int i=1;i<size;i++)
    {
        int max_price=price[i];
        for(int j=0;j<i;j++)
        {
            max_price=max(max_price,price[j]+A[i-j-1]);
        }
        A[i]=max_price;
    }
    return A[size-1];
}

int binary_matrix(int m,int matrix[][n])
{
    int** A=new int*[m];
    for(int i=0;i<m;i++)
        A[i]=new int[n];
    int max=0;
    for(int i=0;i<n;i++)
        A[i][0]=matrix[i][0];
    for(int j=0;j<m;j++)
        A[0][j]=matrix[0][j];
    for(int j=1;j<m;j++)
    {
        for(int i=1;i<n;i++)
        {
            if(matrix[i][j]==0) A[i][j]=0;
            else {
                A[i][j]=min(A[i-1][j-1],min(A[i-1][j],A[i][j-1]))+1;
             
                if(A[i][j]>max) max=A[i][j];
            }
        }
    }
    return max;
}

int min_jumps(int* arr,int size)
{
    int* jumps=new int[size];
    jumps[0]=0;
    for(int i=1;i<size;i++)
    {
        int min_jumps=INT_MAX;
        for(int j=0;j<i;j++)
        {
         if(arr[j]>=i-j)
             min_jumps=min(min_jumps,jumps[j]+1);
        }
        jumps[i]=min_jumps;
    }
        return jumps[size-1];
}

int box_stacking(box arr[],int n)
{
    
    box* array=new box[n*3];
    for(int i=0;i<n;i++)        //length>width ==> so that comparing length and width of 2 boxes becomes easier
    {
        array[i].length=max(arr[i].length,arr[i].width);
        array[i].width=min(arr[i].length,arr[i].width);
        array[i].height=arr[i].height;
    }
    for(int i=n,j=0;i<2*n;i++,j++)
    {
        array[i].length=max(arr[j].height,arr[j].width);
        array[i].width=min(arr[j].height,arr[j].width);
        array[i].height=arr[j].length;
    }
    
    for (int i=2*n,j=0;i<3*n;i++,j++)
    {
        array[i].length=max(arr[j].length,arr[j].height);
        array[i].width=min(arr[j].length,arr[j].height);
        array[i].height=arr[j].width;
    }
       sort(array,array+3*n,compare);  //Sorting array in decreasing order of base area
    
    int hmax[3*n];
    hmax[0]=array[0].height;
    int max_overall=INT_MIN;
    for(int i=1;i<3*n;i++)
    {
        int max_h=array[i].height;
        for(int j=0;j<i;j++)
        {
            if(array[i].length<array[j].length&&array[i].width<array[j].width)
                max_h=max(max_h,hmax[j]+array[i].height);
        }
        hmax[i]=max_h;
        max_overall=max(max_overall, hmax[i]);
    }

    return max_overall;
}

bool compare(box element1,box element2)   //Utitlity function for box stacking problem
{

    return element1.length*element1.width>element2.length*element2.width; //Sorting in decreasing order
}

int knapsack(int w,int* weight,int* v,int n)
{
    int** A=new int*[w+1];
    for(int i=0;i<w+1;i++)
    {
        A[i]=new int[n+1];
    }
    
    for(int i=0;i<w+1;i++)
        A[i][0]=0;
    for(int i=0;i<n+1;i++)
        A[0][i]=0;
    
    for(int j=1;j<n+1;j++)
    {
        for(int i=1;i<w+1;i++)
        {
            if(weight[j-1]>i) A[i][j]=A[i][j-1];
            else A[i][j]=max(v[j-1]+A[i-weight[j-1]][j-1],A[i][j-1]);
        }
    }
    
    return A[w][n];
}


int long_inc_subsequence(int* arr,int n)
{
    int* result=new int[n];
    int final=INT_MIN;
    for(int i=0;i<n;i++)
        result[i]=0;
    result[0]=1;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(arr[j]<arr[i]&&result[j]+1>result[i])result[i]=result[j]+1;
        }
        final=max(final,result[i]);

    }
    return final;
}


int long_com_subsequence(char* A, char* B,int a,int b)
{
    int** R=new int*[a+1];
    for(int i=0;i<a+1;i++)
    {
        R[i]=new int[b+1];
    }
    R[0][0]=0;
    int maximum=INT_MIN;
    for(int i=0;i<a+1;i++)
    {
        for(int j=0;j<b+1;j++)
        {
            if(i==0||j==0) R[i][j]=0;
            else if(A[i]==B[j])R[i][j]=1+R[i-1][j-1];
            else R[i][j]=max(R[i][j-1],R[i-1][j]);
            maximum=max(maximum,R[i][j]);
        }
    }
    return maximum;
}
