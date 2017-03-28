/** passed
 * 05-树8 File Transfer   (25分)
 * We have a network of computers and a list of bi-directional connections. 
 * Each of these connections allows a file transfer from one computer to 
 * another. Is it possible to send a file from any computer on the network to 
 * any other?
 * 
 * Input Specification:
 * Each input file contains one test case. For each test case, the first line 
 * contains N (2≤N≤10^4), the total number of computers in a network. Each 
 * computer in the network is then represented by a positive integer between 1 
 * and N. Then in the following lines, the input is given in the format:
 * I c1 c2
 * where I stands for inputting a connection between c1 and c2; or
 * C c1 c2
 * where C stands for checking if it is possible to transfer files between c1 
 * and c2; or
 * S
 * where S stands for stopping this case.
 * 
 * Output Specification:
 * For each C case, print in one line the word "yes" or "no" if it is possible 
 * or impossible to transfer files between c1 and c2, respectively. At the end 
 * of each case, print in one line "The network is connected." if there is a 
 * path between any pair of computers; or "There are k components." where k is 
 * the number of connected components in this network.
 * 
 * Sample Input 1:
5
C 3 2
I 3 2
C 1 5
I 4 5
I 2 4
C 3 5
S
 * 
 * Sample Output 1:
 * no
 * no
 * yes
 * There are 2 components.
 * 
 * Sample Input 2:
5
C 3 2
I 3 2
C 1 5
I 4 5
I 2 4
C 3 5
I 1 3
C 1 5
S
 * 
 * Sample Output 2:
 * no
 * no
 * yes
 * yes
 * The network is connected.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find(int d[], int n)
{
    return (d[n] == 0) ? n : (d[n] = find(d, d[n]));
}

int main()
{
    int disjoint[10001] = {0};
    int N;
    scanf("%d", &N);
    
    char line[15];
    int num1, num2, root1, root2;
    while(1)
    {
        fgets(line, 15, stdin);
        if(line[0] == 'I')
        {
            num1 = atoi(strtok(line + 2, " "));
            num2 = atoi(strtok(NULL, " "));
            root1 = find(disjoint, num1);
            root2 = find(disjoint, num2);
            if(root1 > root2)
            {
                disjoint[root1] = root2;
            }
            else if(root1 < root2)
            {
                disjoint[root2] = root1;
            }
        }
        else if(line[0] == 'C')
        {
            num1 = atoi(strtok(line + 2, " "));
            num2 = atoi(strtok(NULL, " "));
            printf("%s", find(disjoint, num1) == find(disjoint, num2) ? "yes\n" : "no\n");
        }
        else if(line[0] == 'S')
        {
            break;
        }
    }
    int count = 0;
    for(int i = 1; i <= N; i++)
    {
        if(disjoint[i] == 0)
        {
            count++;
        }
    }
    if(count > 1)
    {
        printf("There are %d components.", count);
    }
    else
    {
        printf("The network is connected.");
    }
    
    return 0;
}
