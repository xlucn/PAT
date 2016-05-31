/** passed
 * 03-树2 List Leaves   (25分)
 * Given a tree, you are supposed to list all the leaves in the order of top 
 * down, and left to right.
 * 
 * Input Specification:
 * Each input file contains one test case. For each case, the first line gives 
 * a positive integer N (≤10) which is the total number of nodes in the tree -- 
 * and hence the nodes are numbered from 0 to N-1. Then N lines follow, each 
 * corresponds to a node, and gives the indices of the left and right children 
 * of the node. If the child does not exist, a "-" will be put at the position. 
 * Any pair of children are separated by a space.
 * 
 * Output Specification:
 * For each test case, print in one line all the leaves' indices in the order 
 * of top down, and left to right. There must be exactly one space between any 
 * adjacent numbers, and no extra space at the end of the line.
 * 
 * Sample Input:
 * 
8
1 -
- -
0 -
2 7
- -
- -
5 -
4 6
 * Sample Output:
 * 
 * 4 1 5
 */
 
/**
 * tip:
 * 
 */
#include <stdio.h>
#include <stdlib.h>

void _buildbt(int bt[], int node, char l[], char r[], int root)
{
    bt[node] = root;
    if(l[root] != '-')
        _buildbt(bt, node * 2, l, r, l[root] - '0');
    if(r[root] != '-')
        _buildbt(bt, node * 2 + 1, l, r, r[root] - '0');
}

void buildbt(int bt[], char l[], char r[], int root)
{
    _buildbt(bt, 1, l, r, root);
}

int main()
{
    char l[10], r[10];
    int num;
    scanf("%d", &num);
    for(int i = 0; i < num; i++)
    {
        scanf("\n%c %c", &l[i], &r[i]);
    }
    
    /* find the line number of root node */
    int root;
    int arraynoroot[10] = {0};
    for(int i = 0 ;i < 10; i++)
    {
        if(l[i] != '-') arraynoroot[l[i] - '0'] = 1;
        if(r[i] != '-') arraynoroot[r[i] - '0'] = 1;
    }
    for(int i = 0; i < num; i++)
        if(arraynoroot[i] == 0)
            root = i;
    
    /* build a binary tree in a array */
    int BTree[2048];
    for(int i = 0; i < 2048; i++)
    {
        BTree[i] = -1;
    }
    buildbt(BTree, l, r, root);
    
    /* find the leaves */
    int count = 0;
    for(int i = 0; i < 1024; i++)
    {
        if(BTree[i] != -1 && BTree[2*i] == -1 && BTree[2*i+1] == -1)
        {
            count++;
            printf("%s", count == 1 ? "" : " ");
            printf("%d", BTree[i]);
        }
    }   
    return 0;
}
