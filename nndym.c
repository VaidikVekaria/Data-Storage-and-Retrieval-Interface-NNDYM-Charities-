#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define SIZE 60

int counter = 10000;
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

struct node * insert(struct node * root, int key, char * name, int l_d ){
  
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
    printf("        :- %x  -> $ %d  -->  %s  ", root->key, root->t_d, root->name);
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

//Balances the tree to allow log(n) runtime on operations

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
    
    record = fopen("txt", "r");

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
    
   
    while(1)
    {
    printf("\n\n********************************* JAY SHREE SWAMINARAYAN **********************************\n\n");
    printf("--------------------------Welcome to the NNDYM Donation Interface--------------------------\n\n");
    printf("  Type:\n");
    printf("       'A' to add a new donar. \n       'B' to add funds from existing donars. \n       'C' to know more about NNDYM Charities.\n       'D' to get more information on the Data Structure used to build this Database.\n       'E' For Admins Only. (List of Members & Total Amount Donated) \n\n  To quit type 'exit'\n\n");
    printf("Your Response: ");

    fgets(input, 10, stdin);

    if(strcmp(input, "exit\n") == 0){
        break;

    } else if(input[0] =='A' || input[0] == 'a'){
        
        printf("\nPlease enter your name in this format 'Firstname_LastName': ");
        fgets(name, SIZE - 1, stdin);
        
        printf("\nPlease enter your Donation Amount: "); 
        fgets(last_donation, SIZE -1, stdin);

        l_d = atoi(last_donation);
        sum_money += l_d;

        key = getKey();
        root = insert(root, key, name, l_d);
        //balance the tree
        printf("\n");
        printf("                         <<<<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>>>>\n");
        printf("\n~~ Thank You for your contribution to NNDYM. We really appretiate your support %s\n", name);
        printf("~~ Your Donar ID is: %x \n\n~~ Please take note of this Donar ID.\n\n~~ It will come handy in your future contributions to NNDYM charities \n\n~~ Thank You :) \n", key);
        
 

    } else if(input[0] == 'B' || input[0] == 'b'){

        printf("\nPlease Enter Your Donar ID: "); 
        fgets(input, 10, stdin );

        temp_key = str_to_hex(input);
        temp = search(root,temp_key);

        if(temp != NULL){

        printf("\nPlease enter the Donation Amount: "); 
        fgets(last_donation, SIZE -1, stdin);

        printf("\n");
        printf("                         <<<<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>>>>\n\n");
        printf("~~ Welcome Back %s\n",temp->name);
        printf("~~ Your last contribution was: $%d\n\n", temp->l_d);
        printf("~~ Your continued support means a world to our NNDYM community !!\n\n");

        l_d = atoi(last_donation);
        sum_money += l_d;

        temp->t_d += l_d;
        temp->l_d = l_d; 

        printf("~~ Your Total Contribution is: $%d\n", temp->t_d);

        } else {
            printf("\nSorry, The Donar ID is incorrect, Please try again.\n\n");
        }

        

    } else if(input[0] == 'D' || input[0] == 'd'){

        int sum_nodes = total_nodes(root);
        double log_n = log2((double)sum_nodes);

        printf("\n");
        printf("                      <<<<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>>>>\n");
        printf("\nThis Database is built on a Optimised Binary Search Tree.\n\n");
        printf("~ Total Number of Nodes (Equal to total Donars till date): %d\n", total_nodes(root));
        printf("~ Height of the Balanced BST: %d\n", findHeight(root));
        printf("~ Log base 2 of %d is approximately %.2f.\n", sum_nodes, log_n);
        printf("~ This means that runtime of search, insert and many other operations is just log(n)\n");
        printf("~ This database can store unlimited donars with no additional costs.\n");

    } else if(input[0] == 'C' || input[0] == 'c'){
        
        printf("\n");
        printf("                      <<<<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>>>>\n\n");
        
        printf(" NNDYM aims to nurture its members to firstly become good human being and then arouses feelings \n of responsibility, spiritual consciousness and dedication. \n\n To achieve these goals, youths are encouraged to: \n\n  ~~ Participate in humanitarian efforts\n  ~~ Seek cultural awareness\n  ~~ Welcome guidance through personal spiritual development\n\n");
        printf(" As NNDYM actively grows, we have accumulated a total fund of $%d from %d members.\n\n", sum_money, counter-10000);
    
    } else if(input[0] == 'E' || input[0] == 'e'){

        printf("\n");
        printf("                      <<<<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>>>>\n");
        printf("\n");
        printf("  Total Members: %d, Total Funds: %d\n\n", counter-10000, sum_money);
        printf("  List is inorder format of Donar ID\n\n");
        printf("  Donar ID:----------CAD-------------NAME--------------\n\n");
                           
        printf("  ");
        inorder(root);
        printf("\n\n");

    }else {
        printf("\nSorry, Please try again.");
    }
        
    } 
    
    
    return 0;
    
}
