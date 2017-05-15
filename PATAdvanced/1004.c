/**
 * 1004. Counting Leaves (30)
 * 
 * A family hierarchy is usually presented by a pedigree tree. Your job is to 
 * count those family members who have no child.
 * 
 * Input
 * 
 * Each input file contains one test case. Each case starts with a line 
 * containing 0 < N < 100, the number of nodes in a tree, and M (< N), the 
 * number of non-leaf nodes. Then M lines follow, each in the format:
 * 
 * ID K ID[1] ID[2] ... ID[K]
 * where ID is a two-digit number representing a given non-leaf node, K is the 
 * number of its children, followed by a sequence of two-digit ID's of its 
 * children. For the sake of simplicity, let us fix the root ID to be 01.
 * 
 * Output
 * 
 * For each test case, you are supposed to count those family members who have 
 * no child for every seniority level starting from the root. The numbers must 
 * be printed in a line, separated by a space, and there must be no extra space 
 * at the end of each line.
 * 
 * The sample case represents a tree with only 2 nodes, where 01 is the root and
 * 02 is its only child. Hence on the root 01 level, there is 0 leaf node; and 
 * on the next level, there is 1 leaf node. Then we should output "0 1" in a 
 * line.
 * 
 * Sample Input
 * 2 1
 * 01 1 02
 * Sample Output
 * 0 1
 */
#include <stdio.h>

#define MAX 999

typedef struct Member *Member;
typedef struct Child *Child;

struct Member{
    int level;
    Child child;
};

struct Child{
    int ID;
    Child iter;
};

int main()
{
    int N, M, ID, cID, K;
    struct Member nodes[100];
    struct Child children[100];
    
    /* Read data and initiate a adjacent list */
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++)
    {
        nodes[i].level = MAX;
        nodes[i].child = NULL;
    }
    nodes[1].level = 0;         /* root node at level 0 */
    for(int i = 0, k = 0; i < M; i++)
    {
        scanf("%d %d", &ID, &K);
        for(; K--; k++)
        {
            scanf("%d", &cID);
            children[k].ID = cID;
            children[k].iter = nodes[ID].child;
            nodes[ID].child = &children[k];
        }
    }
    
    /* For every level, find leaf nodes */
    int n = N, count;
    for(int level = 0; n; level++)
    {
        count = 0;
        for(int i = 1; i <= N; i++) if(nodes[i].level == level)
        {
            n--;
            if(nodes[i].child == NULL)
                count++;
            /* set the children to next level */
            for(Child c = nodes[i].child; c; c = c->iter)
                nodes[c->ID].level = level + 1;
        }
        
        printf("%d%c", count, n ? ' ' : '\0');
    }
    
    return 0;
}
