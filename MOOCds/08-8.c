08-图8 How Long Does It Take   (25分)
Given the relations of all the activities of a project, you are supposed to find the earliest completion time of the project.

Input Specification:

Each input file contains one test case. Each case starts with a line containing two positive integers NN (\le 100≤100), the number of activity check points (hence it is assumed that the check points are numbered from 0 to N-1N−1), and MM, the number of activities. Then MM lines follow, each gives the description of an activity. For the i-th activity, three non-negative numbers are given: S[i], E[i], and L[i], where S[i] is the index of the starting check point, E[i] of the ending check point, and L[i] the lasting time of the activity. The numbers in a line are separated by a space.

Output Specification:

For each test case, if the scheduling is possible, print in a line its earliest completion time; or simply output "Impossible".

Sample Input 1:

9 12
0 1 6
0 2 4
0 3 5
1 4 1
2 4 1
3 5 2
5 4 0
4 6 9
4 7 7
5 7 4
6 8 2
7 8 4
Sample Output 1:

18
Sample Input 2:

4 5
0 1 1
0 2 2
2 1 3
1 3 4
3 2 5
Sample Output 2:

Impossible
