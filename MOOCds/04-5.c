/** passed
 * 04-树5 Root of AVL Tree   (25分)
 * An AVL tree is a self-balancing binary search tree. In an AVL tree, the 
 * heights of the two child subtrees of any node differ by at most one; 
 * if at any time they differ by more than one, rebalancing is done to restore 
 * this property. Figures 1-4 illustrate the rotation rules.
 * Now given a sequence of insertions, you are supposed to tell the root of the 
 * resulting AVL tree.
 * 
 * Input Specification:
 * Each input file contains one test case. For each case, the first line 
 * contains a positive integer N (≤20) which is the total number of keys to be 
 * inserted. Then N distinct integer keys are given in the next line. All 
 * the numbers in a line are separated by a space.
 * 
 * Output Specification:
 * For each test case, print the root of the resulting AVL tree in one line.
 * 
 * Sample Input 1:
5
88 70 61 96 120
 *
 * Sample Output 1:
 * 70
 * 
 * Sample Input 2:
7
88 70 61 96 120 90 65
 * 
 * Sample Output 2:
 * 88
 */
 
#include <stdio.h>
#include <stdlib.h>

typedef struct _avlnode{
    int height;
    int data;
    struct _avlnode* left;
    struct _avlnode* right;
}avlnode;

typedef struct _avlnode *ptrtoavl;
typedef struct _avlnode *avl;

int height(ptrtoavl p)
{
    return (p == NULL ? -1 : p->height);
}

void reheight(ptrtoavl T)
{
    T->height = (height(T->left) > height(T->right) ? height(T->left) : height(T->right)) + 1;
}

ptrtoavl singlerotateleft(ptrtoavl p)
{
    ptrtoavl p1 = p->left;
    p->left = p1->right;
    p1->right = p;
    
    reheight(p);
    reheight(p1);
    return p1;
}

ptrtoavl singlerotateright(ptrtoavl p)
{
    ptrtoavl p1 = p->right;
    p->right = p1->left;
    p1->left = p;
    
    reheight(p);
    reheight(p1);
    return p1;
}

ptrtoavl doublerotateleft(ptrtoavl p)
{
    p->left = singlerotateright(p->left);
    return singlerotateleft(p);
}

ptrtoavl doublerotateright(ptrtoavl p)
{
    p->right = singlerotateleft(p->right);
    return singlerotateright(p);
}

ptrtoavl insert( int x, avl T )
{
    /* insert */
    if( T == NULL )
    {
        T = ( ptrtoavl )malloc( sizeof( struct _avlnode ) );
        T->height = 0;
        T->data = x;
        T->right = NULL;
        T->left = NULL;
    }
    else if(x < T->data)
    {
        T->left = insert(x, T->left);
        /*  keep the balance */
        if(height(T->left) - height(T->right) == 2)
        {
            if(x < T->left->data)
            {
                T = singlerotateleft(T);
            }
            else
            {
                T = doublerotateleft(T);
            }
        }   
    }
    else if( x > T->data )
    {
        T->right = insert( x, T->right );
        /*  keep the balance */
        if(height(T->right) - height(T->left) == 2)
        {
            if(x > T->right->data)
            {
                T = singlerotateright(T);
            }
            else
            {
                T = doublerotateright(T);
            }
        }        
    }
    
    reheight(T);
    return T;
}

int main()
{
    int num;
    scanf("%d", &num);
    
    int data;
    avl t = NULL;
    for(int i = 0; i < num; i++)
    {
        scanf("%d", &data);
        t = insert(data, t);
    }
    printf("%d", t->data);
    return 0;
}
