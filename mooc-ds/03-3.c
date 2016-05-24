/**
 * 03-树3 Tree Traversals Again   (25分)
 * An inorder binary tree traversal can be implemented in a non-recursive way 
 * with a stack. For example, suppose that when a 6-node binary tree (with the 
 * keys numbered from 1 to 6) is traversed, the stack operations are: push(1); 
 * push(2); push(3); pop(); pop(); push(4); pop(); pop(); push(5); push(6); 
 * pop(); pop(). Then a unique binary tree (shown in Figure 1) can be generated 
 * from this sequence of operations. Your task is to give the postorder 
 * traversal sequence of this tree.
 * 
 * Input Specification:
 * Each input file contains one test case. For each case, the first line 
 * contains a positive integer N (<=30) which is the total number of nodes in a 
 * tree (and hence the nodes are numbered from 1 to N). Then 2N lines follow, 
 * each describes a stack operation in the format: "Push X" where X is the index
 * of the node being pushed onto the stack; or "Pop" meaning to pop one node 
 * from the stack.
 * 
 * Output Specification:
 * For each test case, print the postorder traversal sequence of the 
 * corresponding tree in one line. A solution is guaranteed to exist. All the 
 * numbers must be separated by exactly one space, and there must be no extra 
 * space at the end of the line.
 * 
 * Sample Input:
6
Push 1
Push 2
Push 3
Pop
Pop
Push 4
Pop
Pop
Push 5
Push 6
Pop
Pop
 * 
 * Sample Output:
 * 3 4 2 6 5 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACKNUM 30

typedef struct _treenode{
    int data;
    struct _treenode *left;
    struct _treenode *right;
}treenode, *tree, *ptrtotreenode;



typedef struct _stack{
    int top;
    ptrtotreenode array[STACKNUM];
}*stack;

stack newstack()
{
    stack s = malloc(sizeof(struct _stack));
    s->top = -1;
    return s;
}

void push(stack s, ptrtotreenode t)
{
    s->top++;
    s->array[s->top] = t;
}

ptrtotreenode pop(stack s)
{
    ptrtotreenode tmp = s->array[s->top];
    s->top--;
    return tmp;
}

/**
 * @brief non-recursive in order traversal of a tree using a stack
 * @param t pointer to the root of a tree
 * 
 * How this work:
 * push(root)
 * while(stack not empty)
 *   if top.left is not null: push(top.left)
 *   else if top.right is not null: pop() and push(this right)
 *   else: pop()
 */
void inorderwithstack(tree t)
{
    stack s = newstack();
    
    /*  push the root */
    push(s, t);
    
    int count = 0;
    tree l, r;
    while(s->top != -1)
    {
        l = s->array[s->top]->left;
        r = s->array[s->top]->right;
        if(l != NULL)
        {
            push(s, l);
        }
        else
        {
            /* pop */
            tree tmp = pop(s);
            printf("%s", count == 0 ? "" : " ");
            printf("%d ", tmp->data);
            count ++;
            /* after pop this node, set its parent node to point to NULL */
            if(s->top != -1)
            {
                if(s->array[s->top]->left == tmp)
                {
                    s->array[s->top]->left = NULL;
                }
                else if(s->array[s->top]->right == tmp)
                {
                    s->array[s->top]->right = NULL;
                }
            }
            if(r != NULL)
            {
                /* push the right child */
                push(s, r);
            }
        }
    }
}

/**
 * @brief non-recursive post order traversal of a tree using a stack
 * @param t pointer to the root of a tree
 * 
 * How this work:
 * push(root)
 * while(stack not empty)
 *   if top.left is not null: push(top.left)
 *   else if top.right is not null: push(this right)
 *   else: pop()
 */
void postorderwithstack(tree t)
{
    stack s = newstack();
    
    /*  push the root */
    push(s, t);
    
    int count = 0;
    tree l, r;
    while(s->top != -1)
    {
        l = s->array[s->top]->left;
        r = s->array[s->top]->right;
        if(l != NULL)
        {
            push(s, l);
        }
        else if(r != NULL)
        {
            /* push the right child */
            push(s, r);
        }
        else
        {
            /* pop */
            tree tmp = pop(s);
            printf("%s", count == 0 ? "" : " ");
            printf("%d", tmp->data);
            count++;
            /* after pop this node, set its parent node to point to NULL */
            if(s->top != -1)
            {
                if(s->array[s->top]->left == tmp)
                {
                    s->array[s->top]->left = NULL;
                }
                else if(s->array[s->top]->right == tmp)
                {
                    s->array[s->top]->right = NULL;
                }
            }
        }
    }
}

#define PUSH 1
#define POP 0

/**
 * How to solve:
 * There is a relation between
 *  the order of push and pop and their parent-child relation:
 *  1.push(a) and then push(b):
 *      b is the left child of a;
 *  2.pop->a and push(b):
 *      b is the right child of a;
 * e.g. 
 * ACTION   CONCLUSION(look at the line and the line above it)
 * Push 1   1 is the root
 * Push 2   2 is 1's left child
 * Push 3   3 is 2's left child
 * Pop->3
 * Pop->2
 * Push 4   4 is 2's right child
 * Pop->4
 * Pop->1
 * Push 5   5 is 1's right child
 * Push 6   6 is 5's left child
 * Pop->6
 * Pop->5
 */
int main()
{
    char line[20];
    int num;
    fgets(line, 20, stdin);
    num = atoi(line);
    
    /* create a tree and a stack */
    tree root = NULL;
    tree tmp;
    stack s = newstack();
    
    int data;
    int action, lastaction;
    for(int i = 0; i < 2 * num; i++)
    {
        /* read */
        fgets(line, 20, stdin);
        if(strcmp(strtok(line, " "), "Push") == 0)
        {
            action = PUSH;
            data = atoi(strtok(NULL, " "));
        }
        else
        {
            action = POP;
        }
        
        /* anylasis and build a tree */
        if(action == PUSH) 
        {
            tree tn = malloc(sizeof(treenode));
            tn->data = data; tn->left = NULL; tn->right = NULL;
            if(root == NULL) /* root */
            {
                root = tn;
            }
            else if(lastaction == PUSH) /* left child */
            {
                s->array[s->top]->left = tn;
            }
            else if(lastaction == POP) /* right child */
            {
                tmp->right = tn;
            }
            push(s, tn);
        }
        else if(action == POP)
        {
            tmp = pop(s);
        }
        lastaction = action;
    }
    postorderwithstack(root);
    
    return 0;
}
