
//  main.cpp
//  binary_trees
//
//  Created by srinija on 10/2/14.
//

#include <iostream>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;
struct node{
    int value;
    node* left;
    node* right;
};

node* newNode(int n);
void pre_order(node* head);
void iterative_pre(node* ptr);
void in_order(node* head);
void level_order(node* ptr);
int get_size(node* head);
void print_leaf_paths(node* ptr);
void print_paths(node* ptr, int* path, int index);
void root_leaf_sum(node* ptr,int num);
bool root_leaf_sum(node* ptr,int* sum,int num);
void level_order_spiral(node* ptr);
bool check_children(node* ptr);
void convert_children_sum(node* ptr);
void increment(node* ptr,int diff);
int diameter(node* ptr);
int get_height(node* ptr);
bool check_balance(node* ptr);
int check_balance(node* ptr, bool* check);
node* inorder_and_preorder(int* in,int size,int* pre);
void inorder_and_preorder(int* in, int size, int* pre, int* pre_index, node** ptr);
void double_tree(node* ptr);
bool check_fold(node* head);
bool check_fold(node* ptr1,node* ptr2);
bool check_sum_tree(node* root);
int check_sum_tree(node* root, bool* check);
int convert_sum_tree(node* head);
node* pre_and_post(int* pre,int* post, int size);
bool check_binary(node* root);
bool check_binary(node* root, int min, int max);
int largest_bst(node* head);
int largest_bst(node* root, int low, int high,int* size);
node* sorted_array_bst(int* arr, int high,int low);
node* tree_DLL(node* head);
void tree_DLL(node** ptr,node* current);
void printList(struct node *root);
int subarray_sum(int* arr, int n,int req_sum);
void two_d_spiral(int** A,int m, int n );


int main(int argc, const char * argv[])
{
    int m=6,n=3;
    int** A=new int*[n];
    for(int i=0;i<n;i++)
        A[i]=new int[m];
    cout<<"Enter the matrix!"<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            cin>>A[i][j];
    }
    two_d_spiral(A,m,n);
    
    int sum_arr[]={1, 11, 100, 1, 0, 200, 3, 2, 1, 250};
    cout<<"Subarray sum prob: "<<subarray_sum(sum_arr, sizeof(sum_arr)/sizeof(sum_arr[0]), 280)<<endl;
    
    node* head1=NULL;
    head1=newNode(1);
    head1->left        = newNode(2);
    head1->right       = newNode(3);
    head1->left->left  = newNode(7);
    head1->left->right = newNode(6);
    head1->right->left  = newNode(5);
    head1->right->right = newNode(4);
    
    node* head11=NULL;
    head11=newNode(1);
    head11->left        = newNode(2);
    head11->right       = newNode(3);
    head11->left->left  = newNode(7);
    head11->left->right = newNode(6);
    head11->right->left  = newNode(5);
    head11->right->right = newNode(4);
    node* head_DLL=tree_DLL(head11);
    printList(head_DLL);
    cout<<endl;
    iterative_pre(head1);
    cout<<"Checking foldability: "<<check_fold(head1)<<endl;
    double_tree(head1);
    level_order(head1);
    
    node* head2        = newNode(20);
    head2->left         = newNode(8);
    head2->right        = newNode(2);
    head2->left->left   = newNode(3);
    head2->left->right  = newNode(5);
    head2->right->right = newNode(2);
    
    cout<<"Checking sum tree: "<<check_sum_tree(head2)<<endl;

    
    node*        head3 = newNode(50);
    head3->left        = newNode(7);
    head3->right       = newNode(2);
    head3->left->left  = newNode(3);
    head3->left->right = newNode(5);
    head3->right->left  = newNode(1);
    head3->right->right = newNode(30);
    /* following binary tree is
     
             1
           /   \
          2      3
         /  \    /
        4     5  6
       /
      7                     */
    node* head4=NULL;
    head4        = newNode(1);
    head4->left = newNode(2);
    head4->right = newNode(3);
    head4->left->left = newNode(4);
    head4->left->right = newNode(5);
    head4->right->left = newNode(6);
    head4->left->left->left = newNode(7);
    /* Constructed binary tree is
            1
          /   \
         2      3
        /  \
       4    5
      /
     6
     */
     node*       head5 = newNode(1);
    head5->left        = newNode(2);
    head5->right       = newNode(3);
    head5->left->left  = newNode(4);
    head5->left->right = newNode(5);
    head5->left->left->left=newNode(6);
    /*cout<<"Pre_order Traversal: ";
    pre_order(head);
    cout<<endl;
    cout<<"In_order Traversal: ";
    in_order(head); //Non recursive version
    cout<<endl;
    cout<<"Level Order Traversal: ";
    level_order(head);
    cout<<endl;
    cout<<"Size of the tree is "<<get_size(head)<<endl;*/
    cout<<"Printing Paths: ";
    print_leaf_paths(head4);
    root_leaf_sum(head4,12);
    cout<<"Level Order Traversal in spiral form: ";
    level_order_spiral(head1);
    cout<<endl;
    cout<<"Diameter of the tree is: "<<diameter(head1)<<endl;
    cout<<"Checking Children sum property: "<<check_children(head1)<<endl;
    cout<<"Converting..."<<endl;
    convert_children_sum(head1);
    cout<<"Checking Children sum property: "<<check_children(head1)<<endl;
    cout<<"Checking balance: "<<check_balance(head4)<<endl;
    int in[] = {4,2,5,1,3,6};
    int pre[] = {1,2,4,5,3,6};
    int len = sizeof(in)/sizeof(in[0]);
    node* result=inorder_and_preorder(in, len, pre);
    cout<<"Printing inorder:  ";
    in_order(result);
    
    node* root = newNode(10);
    root->left = newNode(-2);
    root->right = newNode(6);
    root->left->left = newNode(8);
    root->left->right = newNode(-4);
    root->right->left = newNode(7);
    root->right->right = newNode(5);
    convert_sum_tree(root);
    cout<<"\n Printing level order: "<<endl;
    level_order(root);
    
    int pre1[] = {1, 2, 4, 8, 9, 5, 3, 6, 7};
    int post1[] = {8, 9, 4, 5, 2, 6, 7, 3, 1};
    int size1 = sizeof( pre1 ) / sizeof( pre1[0] );
    
    node *root2 = pre_and_post(pre1, post1, size1);
    cout<<"Printing in order: "<<endl;
    in_order(root2);
    
    node *root1 = newNode(50);
    root1->left        = newNode(10);
    root1->right       = newNode(60);
    root1->left->left  = newNode(5);
    root1->left->right = newNode(20);
    root1->right->left  = newNode(55);
    root1->right->left->left  = newNode(45);
    root1->right->right = newNode(70);
    root1->right->right->left = newNode(65);
    root1->right->right->right = newNode(80);
    
    cout<<"Largest Binary search tree is: "<<largest_bst(root1)<<endl; //wrong!!
    int sorted[]={1, 2, 3, 4, 5, 6, 7};
    node* root3=sorted_array_bst(sorted, sizeof(sorted)/sizeof(sorted[0]), 0);
    in_order(root3);
    
    
}

node* newNode(int n)
{
    node* temp=new node;
    temp->value=n;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

//pre order traversal
void pre_order(node* head)  //<root><left><right>
{
    if(head==NULL)
        return;
    cout<<head->value<<"  ";
    pre_order(head->left);
    pre_order(head->right);
}

void iterative_pre(node* root)
{
    if (root == NULL)
        return;
    
    // Create an empty stack and push root to it
    stack<node *> nodeStack;
    nodeStack.push(root);
    
    /* Pop all items one by one. Do following for every popped item
     a) print it
     b) push its right child
     c) push its left child
     Note that right child is pushed first so that left is processed first */
    while (nodeStack.empty() == false)
    {
        // Pop the top item from stack and print it
        struct node *node = nodeStack.top();
        printf ("%d ", node->value);
        nodeStack.pop();
        
        // Push right and left children of the popped node to stack
        if (node->right)
            nodeStack.push(node->right);
        if (node->left)
            nodeStack.push(node->left);
    }

}

void in_order(node* ptr)  //<left> <root> <right>  //Non recursive version
{
    stack<node*> stk;
    while(!stk.empty()||ptr!=NULL)
    {
        while(ptr!=NULL)
        {
            stk.push(ptr);
            ptr=ptr->left;
        }
        ptr=stk.top();
        stk.pop();
        cout<<ptr->value<<"  ";
        ptr=ptr->right;
    }
}


void level_order(node* ptr)
{
    queue<node*> q;
    q.push(ptr);
    while(!q.empty())
    {
        ptr=q.front();
        q.pop();
        cout<<ptr->value<<"  ";
       if(ptr->left) q.push(ptr->left);
        if(ptr->right)q.push(ptr->right);
        
    }
}

int get_size(node* head)    //Size=Number of elements present in the tree
{
    if(head==NULL)
        return 0;
    return 1+get_size(head->left)+get_size(head->right);
}

void print_leaf_paths(node* ptr)        //Do it urself first!! Awesome :)
{
    int size=get_size(ptr);
    int path[size];
    int index=0;
    print_paths(ptr,path,index);

}

void print_paths(node* ptr, int* path, int index)       //Utitlity function for above
{
    if(ptr==NULL)
        return;
    if(ptr!=NULL)
    {
    path[index]=ptr->value;
    index++;
    }
    if(ptr->left==NULL&&ptr->right==NULL)
    {
        for(int i=0;i<index;i++)
            cout<<path[i]<<" ";
        cout<<endl;
        return;
    }
    
    print_paths(ptr->left,path,index);
    print_paths(ptr->right,path, index);
    
}


void level_order_spiral(node* ptr)
{
    int level=0;
    int num;
    queue<node*> q;
    stack<int> stk;
    q.push(ptr);
    q.push(NULL);
    while(!q.empty()&&q.front()!=NULL)
          {

              level++;
              while(q.front()!=NULL)
              {
                  ptr=q.front();
                  q.pop();
                  if(ptr->left) q.push(ptr->left);
                  if(ptr->right) q.push(ptr->right);
                  if(level%2==0)
                      cout<<ptr->value<<"  ";
                  
                  else{
                      stk.push(ptr->value);
                  }
              }
              q.push(NULL);
              q.pop();
              if(!stk.empty())
              {
                  while(!stk.empty()){
                      num=stk.top();
                      cout<<num<<"  ";
                      stk.pop();
                  }
                  
                  
              }
          }
    
}

bool check_children(node* ptr)
{
    stack<node*> stk;
    stk.push(ptr);
    int child1,child2;
    while(!stk.empty())
    {
        ptr=stk.top();
        stk.pop();
        if(ptr->left||ptr->right)
        {
            if(ptr->left){
                child1=ptr->left->value;
                stk.push(ptr->left);
            }
            else child1=0;
            if(ptr->right){
                child2=ptr->right->value;
                stk.push(ptr->right);
            }
            else child2=0;
        if(ptr->value!=child1+child2)
            return false;
        }
        
    }
    return true;
}

void convert_children_sum(node* ptr)
{
    if(ptr==NULL||(ptr->left==NULL&&ptr->right==NULL))
        return;
   
    convert_children_sum(ptr->left);
    convert_children_sum(ptr->right);
    
    int child_left=0, child_right=0;
    if(ptr->left)
        child_left=ptr->left->value;
    if(ptr->right)
        child_right=ptr->right->value;
    int diff=ptr->value-child_left-child_right;
    if(diff<0)
        ptr->value-=diff;
    else if(diff>0)
        increment(ptr,diff);
    
    
}


void increment(node* ptr,int diff)
{
    if(ptr->left==NULL&&ptr->right==NULL)
        return;
    if(ptr->left){
        ptr->left->value+=diff;
        increment(ptr->left,diff);
    }
    else{
        ptr->right->value+=diff;
        increment(ptr->right,diff);
    }
}

int diameter(node* ptr)
{
    if(ptr==NULL)
        return 0;

    return max(max(diameter(ptr->left),diameter(ptr->right)),get_height(ptr->left)+get_height(ptr->right)+1);
}

int get_height(node* ptr)
{
    if(ptr==NULL)
        return 0;
    return max(get_height(ptr->left),get_height(ptr->right))+1;
}


bool check_balance(node* ptr)
{
    bool check=true;
    check_balance(ptr,&check);
    return check;
}
    
int check_balance(node* ptr, bool* check)
{
    
    
    if(ptr==NULL){
        return 0;
    }

    int hl=check_balance(ptr->left);
    int hr=check_balance(ptr->right);
    if(!(hl-hr==1||hl-hr==0||hl-hr==-1))
        *check=false;
    return max(hl,hr)+1;
}

void root_leaf_sum(node* ptr,int num)       //function checks if Root to leaf path sum equal to a given number
{
    int sum=0;
    bool check=root_leaf_sum(ptr, &sum,num);
    check? cout<<"Sum tallys"<<endl:cout<<"Sum doesnt tally"<<endl;
}

    bool root_leaf_sum(node* ptr,int* sum,int num)   //Utility function for the above
    {
    if(ptr==NULL)
        return false;
    (*sum)+=ptr->value;
    if(ptr->left==NULL&&ptr->right==NULL){
        if(*sum==num){
            (*sum)-=ptr->value;
            return true;
        }
    }
    bool check1=root_leaf_sum(ptr->left,sum,num);
    bool check2=root_leaf_sum(ptr->right,sum,num);
    (*sum)-=ptr->value;
        return check1||check2;
}


node* inorder_and_preorder(int* in,int size,int* pre)       //Construct Tree from given Inorder and Preorder traversals-- Did it by myself! :D
{
    node* head=NULL;
    int pre_index=0;
    inorder_and_preorder(in,size,pre,&pre_index,&head);
    return head;
}

void inorder_and_preorder(int* in, int size, int* pre, int* pre_index, node** ptr)
{
    if(size<=0)
        return;
    //find in_index=pre_index;
    int in_index;
    for(in_index=0;in_index<size;in_index++)
    {
        if(in[in_index]==pre[*pre_index])
            break;
    }
    
    *ptr=newNode(in[in_index]);
    (*pre_index)++;
    inorder_and_preorder(in, in_index,pre, pre_index,&((*ptr)->left));
    inorder_and_preorder(in+in_index+1, size-in_index-1,pre, pre_index, &((*ptr)->right));
    
    
}


void double_tree(node* ptr)
{
    
    stack<node*> stk;
    stk.push(ptr);
    while(!stk.empty())
    {
    
        node* temp=stk.top();
        stk.pop();
        if(temp->left)stk.push(temp->left);
        if(temp->right)stk.push(temp->right);
        node* temp2=temp->left;
        temp->left = newNode(temp->value);
        temp->left->left=temp2;
        
    }
    
}

bool check_fold(node* head)
{
    return check_fold(head->left,head->right);
}

bool check_fold(node* ptr1,node* ptr2)
{
    if(ptr1==NULL&&ptr2==NULL)
        return true;
    else if((ptr1==NULL&&ptr2!=NULL)||(ptr1!=NULL&&ptr2==NULL))
        return false;
    
    return check_fold(ptr1->left,ptr2->right) && check_fold(ptr1->right,ptr2->left);
}

bool check_sum_tree(node* root)
{
    bool check=true;
    check_sum_tree(root,&check);
    return check;
}


int check_sum_tree(node* root, bool* check)
{
    if(!root)
        return 0;
    int left=check_sum_tree(root->left,check);
    int right=check_sum_tree(root->right,check);
    if(root->left!=NULL||root->right!=NULL){
        if(root->value!=left+right){
        *check=false;
        }
    }
    return left+right+root->value;
}

int convert_sum_tree(node* head)
{
    if(head==NULL)
        return 0;
    int orig_value=head->value;
    if(head->left==NULL&&head->right==NULL)
    {
        head->value=0;
    }
    else
        head->value=convert_sum_tree(head->left)+convert_sum_tree(head->right);
    return orig_value+head->value;
}

node* special_tree(int* in,int size)        //Different approach
{
    node* root=newNode(in[0]);
    for(int i=1;i<size;i++)
    {
        if(in[i]>root->value)
        {
            node* temp=root;
            root=newNode(in[i]);
            root->left=temp;
        }
        
        if(in[i]<root->value)
        {
            node* ptr=root;
            while(ptr->right!=NULL&&ptr->right->value>in[i])
            {
                ptr=ptr->right;
            }
            if(ptr->right==NULL)
                ptr->right=newNode(in[i]);
            else{
                node* temp=ptr->right;
                ptr->right=newNode(in[i]);
                ptr->right->left=temp;
            }
        }
    }
    return root;
}



node* pre_and_post(int* pre,int* post, int size)
{
    if(size==0)
        return NULL;
    if(size==1)
    {
        node* root=newNode(pre[0]);
        return root;
    }
    node* root=newNode(pre[0]);
    int index;
    for(index=0;index<size;index++){
        if(post[index]==pre[1]) break;
    }
    pre++;
    root->left=pre_and_post(pre, post, index+1);
    root->right=pre_and_post(pre+index+1, post+index+1, size-index-2);
    return root;

}

//WRONG METHOD TO CHECK IF BINARY!!
bool check_binary_wrong(node* root)
{
    if(root==NULL||(root->left==NULL&&root->right==NULL))
        return true;
       
    if(root->left!=NULL&& root->left->value>root->value)
        return false;
    
    if(root->right!=NULL&&root->right->value<root->value)
        return false;
    
    if(check_binary(root->left)&&check_binary(root->right))
        return true;
    
    return false;
}

//CORRECT METHOD:
bool check_binary(node* root)
{
    return check_binary(root, INT_MIN, INT_MAX);
}

bool check_binary(node* root, int min, int max)
{
    if(root==NULL)return true;
    
    if(root->value<min||root->value>max) return false;
    
    return check_binary(root->left,min,root->value-1)&&check_binary(root->right,root->value+1,max);
}


int largest_bst(node* head)
{
    
    int size=0;
    largest_bst(head,INT_MAX,INT_MIN,&size);
    return size;
}

int largest_bst(node* root, int low, int high,int* size)
{
    static bool check=true;
    if(root==NULL)
        return 0;
    //if(root->left==NULL&&root->right==NULL) return 1;
    
    int left= largest_bst(root->left,root->value,high,size);
    int right= largest_bst(root->right,low, root->value,size);
    int total=left+right+1;
    if( root->value<low&&root->value>high&&check==true) *size=max(total,*size);
    else check=false;
    cout<<"Check is: "<<check<<endl;
    return total;
}

node* sorted_array_bst(int* arr, int high,int low)
{
    if(high>low){
        int mid=(high+low)/2;
        node* head=new node;
        head->value=arr[mid];
        head->left=sorted_array_bst(arr, mid, low);
        head->right=sorted_array_bst(arr, high, mid+1);
        return head;
    }
    return NULL;
}

node* tree_DLL(node* head)
{
    node** ptr;
    node* new_head=new node;
    
    *ptr=new_head;
    tree_DLL(ptr,head);
    (*ptr)->right=NULL;
    new_head->right->left=NULL;

    return new_head->right;
}

void tree_DLL(node** ptr,node* current)
{
    if(current==NULL)return;
    tree_DLL(ptr,current->left);
    (*ptr)->right=current;
    current->left=*ptr;
    *ptr=(*ptr)->right;
    tree_DLL(ptr,current->right);
}



void printList(struct node *root)
{
    node* root2=NULL;
    while (root != NULL)
    {
        printf("\t%d", root->value);
        if(root->right!=NULL)root2=root;
        root = root->right;
        
    }
    cout<<"Printing in reverse:"<<endl;
    while(root2!=NULL)
    {
        cout<<root2->value<<"  ";
        root2=root2->left;
    }
    
}

int subarray_sum(int* arr, int n,int req_sum)
{
    int sum=0;
    int count=INT_MAX;
    for(int i=0,j=0;i<n;i++)
    {
        sum+=arr[i];
        while(sum>req_sum){
            count=min(count,i-j+1);
            sum-=arr[j];
            j++;
        }
    }
    return count;
}


void two_d_spiral(int** A,int m, int n )
{
    int i1=0,i2=n-1,j1=0,j2=m-1;
    int i,j;
    cout<<"Yo! Printing the array in spiral form: "<<endl;
    while(i1<i2&&j1<j2)
    {
        for(j=j1;j<=j2;j++)
        {
            cout<<A[i1][j]<<"  ";
        }
        for(i=i1+1;i<=i2;i++)
        {
            cout<<A[i][j2]<<"  ";
        }
        for(j=j2-1;j>=j1;j--)
        {
            cout<<A[i2][j]<<"  ";
        }
        for(i=i2-1;i>=i1+1;i--)
        {
            cout<<A[i][j1]<<"  ";
        }
        i1=i1+1; i2=i2-1; j1=j1+1; j2=j2-1;
    }

    if(i1<i2&&j1==j2)
    {
        for(i=i1;i<=i2;i++)
            cout<<A[i][j1]<<"  ";
    }
    else if(j1<j2&&i1==i2)
    {
        for(j=j1;j<=j2;j++)
            cout<<A[i1][j]<<"  ";
    }
    
}




