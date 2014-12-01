//
//  main.cpp
//  binary_search_tree
//
//  Created by srinija on 10/3/14.
//  Copyright (c) 2014 srinija. All rights reserved.
//

#include <iostream>
#include<stack>
using namespace std;

class bst{
private:
    struct node{
        int key;
        node* left;
        node* right;
    };
    node* head=NULL;
    void insert(node* ptr,int n);
    void search(node* ptr,int n);
    void inorder(node* head);
    void preorder(node* head);
    void postorder(node* ptr);
    node* delete_node(node* ptr,int n);
    int min_value(node* ptr);
    void inorder_array(int* arr,int n, int i);
    int largest_bst(node* root, int low, int high,int* size);
    void all_greater_vals(node* root,int* sum);
    int sum_tree(node* root);
    
    
public:
    void insert(int n);
    void search(int n);
    void inorder();
    void inorder_iter();
    void preorder();
    void postorder();
    void preorder_iter();
    void postorder_iter();
    void delete_node(int n);
    int min_value();
    void inorder_array(int* arr,int n);
    int largest_bst();
    void all_greater_vals();
    bool check_single_child(int* arr,int n);
    
    
};

int main(int argc, const char * argv[])
{
    bst tree;
    
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    cout<<"Min value in the tree: "<<tree.min_value()<<endl;
    
    tree.search(70);
    tree.search(100);
    
    tree.inorder();
    tree.inorder_iter();
    tree.preorder();
    tree.preorder_iter();
    tree.postorder();
    tree.postorder_iter();
    
    tree.delete_node(20);
    tree.inorder();
    cout<<"Min value in the tree: "<<tree.min_value()<<endl;
    int arr[]={4, 2, 5, 1, 3};
    tree.inorder_array(arr, sizeof(arr)/sizeof(arr[0]));
    tree.insert(20);
    tree.all_greater_vals();
    tree.inorder();
    int pre[]={20, 10, 11, 13, 25};//Should print no.  //For yes, change 25 to 12
    cout<<"Checking single child:  "<<tree.check_single_child(pre, sizeof(pre)/sizeof(pre[0]))<<endl;
}


void bst::insert(int n)
{
    if(head==NULL){
        head=new node;
        insert(head,n);
        return;
    }
    node* ptr=head;
    while(true)
    {
        if(n<ptr->key)
        {
            if(ptr->left)
                ptr=ptr->left;
            else{
                ptr->left=new node;
                insert(ptr->left,n);
                break;
            }
        }
        else if(n>ptr->key)
        {
            if(ptr->right)
                ptr=ptr->right;
            else{
                ptr->right=new node;
                insert(ptr->right,n);
                break;
            }
        }
    }
    
}

void bst::insert(node* ptr,int n)
{
    ptr->key=n;
    ptr->left=NULL;
    ptr->right=NULL;
}

void bst::search(int n)
{
    search(head,n);
    
}

void bst::search(node* ptr,int n)
{
    if(ptr==NULL)
        cout<<"The key: "<<n<<" was not found!"<<endl;
    
    else if(n==ptr->key) cout<<"The key was found!"<<endl;
    
    else if(n>ptr->key) search(ptr->right,n);
    
    else search(ptr->left,n);
}

void bst::preorder()
{
    cout<<"Printing Preoder: "<<endl;
    preorder(head);
}

void bst::preorder(node* head)
{
    if(head==NULL)
        return;
    cout<<head->key<<"  ";
    preorder(head->left);
    preorder(head->right);
}

void bst::inorder()
{
    cout<<"Printing inorder: "<<endl;
    inorder(head);
}

void bst::inorder(node* head)
{
    if(head==NULL)
        return;
    inorder(head->left);
    cout<<head->key<<"  ";
    inorder(head->right);
}

void bst::inorder_iter()
{
    cout<<"Printing inorder from iteration: ";
    stack<node*> stk;
    node* ptr=head;
    stk.push(head);
    ptr=ptr->left;
    while(!stk.empty()||ptr!=NULL)
    {
        while(ptr!=NULL)
        {
            stk.push(ptr);
            // cout<<"Pushed "<<ptr->key<<endl;
            
            ptr=ptr->left;
        }
        ptr=stk.top();
        stk.pop();
        cout<<ptr->key<<"  ";
        ptr=ptr->right;
    }
}

/*void bst::preorder_iter()
 {
 cout<<"Printing pre-order from iteration: ";
 stack<node*> stk;
 node* ptr=head;
 stk.push(head);
 cout<<ptr->key<<"  ";
 ptr=ptr->left;
 while(!stk.empty()||ptr!=NULL)
 {
 while(ptr!=NULL)
 {
 stk.push(ptr);
 cout<<ptr->key<<"  ";
 ptr=ptr->left;
 }
 ptr=stk.top();
 stk.pop();
 ptr=ptr->right;
 }
 }*/

void bst::postorder()
{
    cout<<"Printing post order: "<<endl;
    postorder(head);
    
}

void bst::postorder(node* ptr)
{
    if(ptr==NULL)
        return;
    postorder(ptr->left);
    postorder(ptr->right);
    cout<<ptr->key<<"  ";
}

void bst::preorder_iter()
{
    cout<<"Printing pre-order from iteration: ";
    stack<node*> stk;
    node* ptr=head;
    stk.push(ptr);
    while(!stk.empty()){
        ptr=stk.top();
        stk.pop();
        cout<<ptr->key<<"  ";
        if(ptr->right!=NULL)stk.push(ptr->right);
        if(ptr->left!=NULL)stk.push(ptr->left);
    }
    
}

void bst::postorder_iter()
{
    cout<<"Printing post-order from iteration: ";
    stack<node*> stk1;
    stack<int>stk2;
    node* ptr=head;
    stk1.push(ptr);
    while(!stk1.empty()){
        ptr=stk1.top();
        stk1.pop();
        stk2.push(ptr->key);
        if(ptr->left!=NULL)stk1.push(ptr->left);
        if(ptr->right!=NULL)stk1.push(ptr->right);
    }
    while(!stk2.empty())
    {
        cout<<stk2.top()<<"  ";
        stk2.pop();
    }
}

void bst::delete_node(int n)
{
    head=delete_node(head,n);
}

bst::node* bst::delete_node(node* ptr,int n)
{
    if(ptr==NULL)
        return ptr;
    if(ptr->key<n)      ptr->right= delete_node(ptr->right,n);
    else if(ptr->key>n) ptr->left=delete_node(ptr->left,n);
    
    else{
        if(ptr->left==NULL){
            node* temp= ptr->right;
            delete ptr;
            return temp;
            
        }
        else if(ptr->right==NULL){
            node* temp= ptr->left;
            delete ptr;
            return temp;
        }
        
        int min=min_value(ptr->right);
        ptr->key=min;
        ptr->right= delete_node(ptr->right,min);
    }
    return ptr;
    
}
int bst::min_value()
{
    return min_value(head);
}

int bst::min_value(node* ptr)
{
    if(ptr->left==NULL)
        return ptr->key;
    else return min_value(ptr->left);
}

void bst::inorder_array(int* arr,int n)
{
    cout<<"Sorting the matrix form BST: "<<endl;
    int i=0;
    inorder_array(arr,n,i);
    
}

void bst::inorder_array(int* arr,int n, int i)
{
    if(2*i+1<n) inorder_array(arr,n,2*i+1);
    cout<<arr[i]<<"  ";
    if(2*i+2<n) inorder_array(arr,n,2*i+2);
    
}


int bst::largest_bst()
{
    
    int size=0;
    largest_bst(head,INT_MAX,INT_MIN,&size);
    return size;
}

int bst::largest_bst(node* root, int low, int high,int* size)
{
    static bool check=true;
    if(root==NULL) return 0;
    //if(root->left==NULL&&root->right==NULL) return 1;
    
    int left= largest_bst(root->left,root->key,high,size);
    int right= largest_bst(root->right,low, root->key,size);
    int total=left+right+1;
    if( root->key<low&&root->key>high&&check==true) *size=max(total,*size);
    else check=false;
    cout<<"Check is: "<<check<<endl;
    return total;
    
}

void bst::all_greater_vals()
{
    int sum=0;
    all_greater_vals(head,&sum);
}

void bst::all_greater_vals(node* root,int* sum)
{
    if(root==NULL) return;
    all_greater_vals(root->right,sum);
    *sum+=root->key;
    root->key=*sum;
    all_greater_vals(root->left,sum);
}

int bst::sum_tree(node* root)
{
    if(root==NULL) return 0;
    return root->key+sum_tree(root->left)+sum_tree(root->right);
}


bool bst::check_single_child(int* arr,int n)
{
    int low=INT_MIN;
    int high=INT_MAX;
    
    for(int i=1;i<n;i++)
    {
        if(arr[i]<low||arr[i]>high) return false;
        if(arr[i]<arr[i-1]) high=arr[i-1];
        else if(arr[i]>arr[i-1]) low=arr[i-1];
    }
    return true;
}
