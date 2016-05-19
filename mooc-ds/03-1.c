/**
 * 03-树1 树的同构   (25分)
 * 
 * 给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换就变成T2，则我们称两棵树是“同构”的。
 * 例如图1给出的两棵树就是同构的，因为我们把其中一棵树的结点A、B、G的左右孩子互换后，就得
 * 到另外一棵树。而图2就不是同构的。
 * 
 * 现给定两棵树，请你判断它们是否是同构的。
 * 输入格式:
 * 输入给出2棵二叉树树的信息。对于每棵树，首先在一行中给出一个非负整数N(≤10)，即该树的结点数
 * （此时假设结点从0到N-1编号）；随后N行，第i行对应编号第i个结点，给出该结点中存储的1个英文
 * 大写字母、其左孩子结点的编号、右孩子结点的编号。如果孩子结点为空，则在相应位置上给出“-”。
 * 给出的数据间用一个空格分隔。注意：题目保证每个结点中存储的字母是不同的。
 * 
 * 输出格式:
 * 如果两棵树是同构的，输出“Yes”，否则输出“No”。
 * 
 * 输入样例1（对应图1）：
 * 8
 * A 1 2
 * B 3 4
 * C 5 -
 * D - -
 * E 6 -
 * G 7 -
 * F - -
 * H - -
 * 8
 * G - 4
 * B 7 6
 * F - -
 * A 5 1
 * H - -
 * C 0 -
 * D - -
 * E 2 -
 * 
 * 输出样例1:
 * Yes
 * 
 * 输入样例2（对应图2）：
 * 8
 * B 5 7
 * F - -
 * A 0 
 * 3
 * C 6 -
 * H - -
 * D - -
 * G 4 -
 * E 1 -
 * 8
 * D 6 -
 * B 5 -
 * E - -
 * H - -
 * C 0 2
 * G - 3
 * F - -
 * A 1 4
 * 
 * 输出样例2:
 * No
 *
 **/

/**
 * tip:所有的父子关系保持不变
 */

/**
 * pseudo code:
 *  read
 *      prepare 4 arrays: char c[26], int l[26], int r[26], int i[26] = {-1...}
 *      read total num
 *      for n = 0 -> num-1
 *          read a line: "c[n] l[n] r[n]"
 *          set corresponding i[]
 *  check parent-child relations
 *      from ch = 'A' -> 'Z'
 *          find pos of ch in Tree1 & Tree2
 *              pos1
 *              pos2
 *          get two childs of ch
 *              l[pos1] r[pos1]
 *              l[pos2] r[pos2]
 *          if not l1=l2&r1=r2 or l1=r2&l2=r1
 *              NO
 *      all ch passed: YES
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main()
{
    int a[1000];
    char c;
    int i=0;
    int n=0;
    while((c=getchar())!='\n')
    {
        if(isdigit(c))
        {
            ungetc(c,stdin);//将c送回输入流
            scanf("%d",&a[n]); n++;
        }
    }
    for(i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}
