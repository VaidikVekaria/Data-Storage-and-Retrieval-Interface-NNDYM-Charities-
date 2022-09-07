# NNDYM-Charities-Interface
Database built using Balanced Binary Search Tree and written in C language.  

NNDYM is a non-profit organization that keeps a record of its donar list and the amount of money they have donated.

This Project aims to create a database system together with a Linux Terminal based user interface that allows a NNDYM admin to efficiently store and retrieve data from a Balanced Binary Search Tree.

txt file contains 274 names of donars corresponding to a digit. i.e 10 Vaidik_Vekaria. Therefor 10 * 5 = $50 is amount donated by vaidik_vekaria to nndym charities.

nndym.c is the core project file that contains all the functions and structures. The main{} in nndym.c will successively read the name and digit in txt file, automatically generate a unique key, create a node with all the information within the node, insert the node into the BST using the key and finally Balance the Tree. 

After Every Node Insertion the tree is recursively balanced, therefore insertion, search, and balance operations have a runtime of O(log2(n)). This can be very help when large data is involved. 

The main{} in nndym.c also provides a user friendly interface for NNDYM admin to insert new users, modify existing user, allow admin to print an inorder list of donars, get statistical information amount NNDYM Charities, and get more information about the data structure used in this program.

To run the program on Linux Terminal. Download the files and navigate to the location of the files. Then type "gcc nndym.c -lm && a.out" in the Terminal. 

The file test.c contains a copy of the functions and structures in nndym.c. The purpose of test.c is to demonstrate the reliability of my code when large scale data in involved.

The file txt_test contains 844800 names. Test.c will process this names in exactly the same maner as nndym.c 

To run the test.c on Linux Terminal. Download the files and natigate to the location of the files. Then type "gcc test.c -lm && a.out" in the Terminal.

This will print out the height of the tree = 19. log2(844800) is 19.69

