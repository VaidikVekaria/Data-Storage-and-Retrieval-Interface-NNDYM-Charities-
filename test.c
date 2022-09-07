#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define SIZE 60

int counter = 1000;
int sum_money = 0;
int list_print = 1;

struct node {
    int key;            // Unique Key
    char name[SIZE];        // Donar name
    int t_d;            // Total Donation Amount
    int l_d;            // Last Donation Amount
    /*
    char l_d_time[];    // Last Donation Time
    */
    struct node *parent; 
    struct node *left;
    struct node *right;
     
};
// This function creates a new node and recurivesly sets the node in the tree at the correct position

struct node * insert(struct node * root, int key, char * name, int l_d){
  
    if(root == NULL){

        root = malloc(sizeof(struct node));
        root->key = key;
        root->l_d = l_d;
        root->t_d = l_d;
        strcpy(root->name, name);

        root -> parent = NULL;
        root -> left = NULL;
        root -> right = NULL;

    } else if(key < root->key){

        root->left = insert(root->left, key, name, l_d);
        root->left->parent = root;
        
    } else if(key > root->key){

        root->right = insert(root->right,key, name, l_d);
        root->right->parent = root;
    }
    return root;

}

// Allows us to find max depth from the root passed

int findHeight(struct node * root){

    int left_height;
    int right_height;

    if(root == NULL){
        return -1;
    }

    left_height = findHeight(root->left);
    right_height = findHeight(root->right);
    
    return (left_height > right_height ? left_height : right_height) + 1;
}

// returns the node we are trying to search with a specific key, root node should be passed. 

struct node * search(struct node * root, int key){
    
    if(root == NULL){
        return NULL;

    } else if(root->key == key){
        return root;

    } else if(key < root->key){
        return search(root->left, key);

    } else if(key > root->key){
        return search(root->right, key);
    }
};

// Will print out the an inorder list of the tree keys;

void inorder(struct node * root){
    if(root == NULL)
        return;
    inorder(root->left);
    printf("   %d.  $ %d --> Donar ID: %x --> %s  ", list_print++, root->t_d, root->key, root->name);
    inorder(root->right);
}

//returns the node with the max key value in the tree

struct node* findMax(struct node* root)
{
    if(root == NULL)
    	return NULL;
    else if(root->right == NULL)
    	return root;
    else
    	return findMax(root->right);
}
// returns the node with the min key value in the tree

struct node* findMin(struct node* root)
{
    if(root == NULL)
    	return NULL;
    else if(root->left == NULL)
    	return root;
    else
    	return findMin(root->left);
}
// returns 1 is the tree is balance or 0 if the tree is not balanced

int isBalanced(struct node * root){
    
    int maxHeight_leftchild = findHeight(root->left);
    int maxHeight_rightchild = findHeight(root->right);
    int balance = maxHeight_leftchild - maxHeight_rightchild;

    balance = abs(balance);

    if(balance <= 1){
        return 1;
    } else {
        return 0;
    }
};

// Nodes will be placed in the tree based on this key, it starts from 1000 and is incremented by 1, making it unique for every node.

int getKey(){
    counter++;
    //int key = rand() % 0xffffff;
    return counter;
}
// Coverts input string to hexadecimal number
int str_to_hex(char input[]){
    int i = strlen(input) - 2 ;
    int power = 1;
    int result = 0;
    int temp = 0;
    
    while(i != -1){

        if(input[i] < 58){
            temp = input[i] - 48;
        } else {
            temp = input[i] - 87;
        }

        result += (temp * power);
        power *= 16;
        i--;
    }
    return result;
    
};

struct node * getParent(struct node * node)
{
    return node->parent;
};
struct node * leftChild(struct node * node)
{
    return node->left;
};
struct node * rightChild(struct node * node)
{
    return node->right;
};
void setLeft(struct node * parent, struct node * left){
    parent->left = left;
}
void setRight(struct node * parent, struct node * right){
    parent->right = right;
}
void setParent(struct node * child, struct node * parent){
    child->parent = parent;
}

struct node * get_lowest_unbalanced_node(struct node* inserted){
    // NULL returned if tree is already balanced.
    if(inserted == NULL){
        return NULL;
    } else if(!(isBalanced(inserted))){
        return inserted;
    } else {
        return get_lowest_unbalanced_node(inserted->parent);
    }
}

// Returns the total number of internal nodes in the tree i.e total number of donars

int total_nodes(struct node * root){
    int a;
    int b; 

    if(root == NULL){
        return 0;
    } else {
        int a = total_nodes(root->left);
        int b = total_nodes(root->right);
        return a+b+1;
    }
}

//Recursively Balances the tree to allow log(n) runtime on operations

struct node * balance(struct node * root, struct node * last_inserted_node, struct node * lowest_unbalanced_node){
    
    if(lowest_unbalanced_node == NULL){
        return root;
    } else {

    struct node * a = lowest_unbalanced_node;
    struct node * b = findHeight(a->left) > findHeight(a->right) ? a->left : a->right;
    struct node * c = findHeight(b->left) > findHeight(b->right) ? b->left : b->right;

    //left_Rotation
    if(a->right == b && b->right == c){

        if(a == root){

            if((b->left) != NULL)
                (b->left)->parent = a;
           
            a->right = b->left;
            b->left = a;
            a->parent = b;
            b->parent = NULL;
            root = b;
          
        } else if(a->parent->right == a){
            
            if((b->left) != NULL)
                (b->left)->parent = a;

            a->right = b->left;
            b->parent = a->parent;
            a->parent->right = b;
            b->left = a;
            a->parent = b;

        } else if(a->parent->left == a){

            if((b->left) != NULL)
                (b->left)->parent = a;

            a->right = b->left;
            b->parent = a->parent;
            a->parent->left = b;
            b->left = a;
            a->parent = b;

        } 

        return root;

    } else if (a->left == b && b->left == c) /*right rotation */ {
            
            if(a == root){

            if((b->right) != NULL)
                (b->right)->parent = a;
           
            a->left = b->right;
            b->right = a;
            a->parent = b;
            b->parent = NULL;
            root = b;
          
        } else if(a->parent->left == a){
            
             if((b->right) != NULL)
                (b->right)->parent = a;

            a->left = b->right;
            b->parent = a->parent;
            a->parent->left = b;
            b->right = a;
            a->parent = b;

        } else if(a->parent->right == a){

            if((b->right) != NULL)
                (b->right)->parent = a;

            a->left = b->right;
            b->parent = a->parent;
            a->parent->right = b;
            b->right = a;
            a->parent = b;

        } 
        
    } else if(a->right == b && b->left == c){

        //First well perform a right rotation followed by a left rotation
       
        if(c->right != NULL) 
            (c->right)->parent = b;

        b->left = c->right;
        c->right = b;
        b->parent = c;
        a->right = c;
        c->parent = a;
        
        if(c->left != NULL)
            (c->left)->parent = a; 

        a->right = c->left;
        
        if(a->parent == NULL){

            c->left = a;
            a->parent = c;
            c->parent = NULL;
            root = c;

        } else if(a->parent->right == a){
            a->parent->right = c;
            c->parent = a->parent;
            c->left = a;
            a->parent = c;
            

        } else if(a->parent->left == a){
            a->parent->left = c;
            c->parent = a->parent;
            c->left = a;
            a->parent = c;
            
        }
       
    } else if(a->left == b && b->right == c){

        //First well perform a left rotation followed by a right rotation
       
        if(c->left != NULL) 
            (c->left)->parent = b;

        b->right = c->left;
        c->left = b;
        b->parent = c;
        a->left = c;
        c->parent = a;
        
        if(c->right != NULL)
            (c->right)->parent = a; 

        a->left = c->right;
        
        if(a->parent == NULL){

            c->right = a;
            a->parent = c;
            c->parent = NULL;
            root = c;

        } else if(a->parent->left == a){
            a->parent->left = c;
            c->parent = a->parent;
            c->right = a;
            a->parent = c;
            

        } else if(a->parent->right == a){
            a->parent->right = c;
            c->parent = a->parent;
            c->right = a;
            a->parent = c;
            
        } 
       
    }
        return balance(root, last_inserted_node, get_lowest_unbalanced_node(last_inserted_node));
    }
    
};


int main(int argc, char * argv){
    struct node *root = NULL;
    struct node *temp = NULL;
    struct node * newNode;
    struct node * last_inserted_node = NULL;
    char name[SIZE];
    int count;
    int key;
    int temp_key;
    int l_d; //last donation amount 
    char last_donation[SIZE]; // char input from user
    
    char input[10]; //To get input for the user;
    //int i = 0;

    FILE * record;

    // We will automate the building of a tree using the data available in file txt.
    
    record = fopen("txt_test", "r");

    fscanf(record,"%d %s", &count, name);
    strcat(name,"\n");
    l_d = count * 5;
    sum_money = l_d;

    while(count!= 0){
        //i++;
        key = getKey();
        root = insert(root, key, name,l_d);
        last_inserted_node = search(root,key);
        temp = get_lowest_unbalanced_node(last_inserted_node);
        
        //After every insertion, Check if the tree is balanced. if not then balance the tree before inserting the next node.
        
        root = balance(root, last_inserted_node, temp);
        
        

        fscanf(record,"%d %s", &count, name);
        strcat(name,"\n");
        l_d = count * 5;
        sum_money += l_d;
    }
    
    last_inserted_node = search(root,key);
    /*
    key = getKey();
    root = insert(root,key,"Vaidik_Vekaria");
    key = getKey();
    root = insert(root,key, "Anjali_varsani");
    key = getKey();
    root = insert(root,key, "Dhanvanti _Varsani");
    key = getKey();
    root = insert(root,key, "Ankush _Varsani");
    key = getKey();
    root = insert(root,key, "Rushi _Varsani");
    
    struct node head = {10,"swaminarayan",NULL,NULL,NULL};
    struct node l1 = {5,"Nilkanth", &head, NULL, NULL};
    struct node r1 = {15,"loej", &head, NULL,NULL};
    struct node l2 = {2,"Ghanshyam", &l1, NULL, NULL};
    struct node l3 = {1,"Balsharma", &l2, NULL, NULL};
    setLeft(&head,&l1);
    setRight(&head,&r1);
    setLeft(&l1,&l2);
    setLeft(&l2,&l3);

    root = &head;
    
    last_inserted_node = search(root,model_key[8]);
    
    root = balance(root, last_inserted_node);
    */
    //inorder(root);
    int sum_nodes = total_nodes(root);
    double log_n = log2((double)sum_nodes);
    printf("\n");
    printf(" Total number of nodes in tree = %d \n", sum_nodes);
    printf(" Log base 2 of %d is approximately %.2f.\n", sum_nodes, log_n);
    printf(" Max Height from root: %d\n", findHeight((root)));
    printf(" Height of leftchild from root: %d\n", findHeight(leftChild(root)));
    printf(" Height of rightchild from root: %d\n", findHeight(rightChild(root)));
    //printf("The tree is balanced (1:True -- 0:False) === %d\n", isBalanced(root));
   
    
    temp = get_lowest_unbalanced_node(last_inserted_node);
    
    if( temp == NULL)
        printf(" This Tree is Balanced\n");
    else 
        printf(" The lowest unbalanced node is %s-%d\n", temp->name, temp->key);

    printf("\n");
return 0;
    
}
