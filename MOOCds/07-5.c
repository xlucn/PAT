07-图5 Saving James Bond - Hard Version   (30分)
This time let us consider the situation in the movie "Live and Let Die" in which James Bond, the world's most famous spy, was captured by a group of drug dealers. He was sent to a small piece of land at the center of a lake filled with crocodiles. There he performed the most daring action to escape -- he jumped onto the head of the nearest crocodile! Before the animal realized what was happening, James jumped again onto the next big head... Finally he reached the bank before the last crocodile could bite him (actually the stunt man was caught by the big mouth and barely escaped with his extra thick boot).

Assume that the lake is a 100 by 100 square one. Assume that the center of the lake is at (0,0) and the northeast corner at (50,50). The central island is a disk centered at (0,0) with the diameter of 15. A number of crocodiles are in the lake at various positions. Given the coordinates of each crocodile and the distance that James could jump, you must tell him a shortest path to reach one of the banks. The length of a path is the number of jumps that James has to make.

Input Specification:

Each input file contains one test case. Each case starts with a line containing two positive integers NN (\le 100≤100), the number of crocodiles, and DD, the maximum distance that James could jump. Then NN lines follow, each containing the (x, y)(x,y) location of a crocodile. Note that no two crocodiles are staying at the same position.

Output Specification:

For each test case, if James can escape, output in one line the minimum number of jumps he must make. Then starting from the next line, output the position (x, y)(x,y) of each crocodile on the path, each pair in one line, from the island to the bank. If it is impossible for James to escape that way, simply give him 0 as the number of jumps. If there are many shortest paths, just output the one with the minimum first jump, which is guaranteed to be unique.

Sample Input 1:

17 15
10 -21
10 21
-40 10
30 -50
20 40
35 10
0 -10
-25 22
40 -40
-30 30
-10 22
0 11
25 21
25 10
10 10
10 35
-30 10
Sample Output 1:

4
0 11
10 21
10 35
Sample Input 2:

4 13
-12 12
12 12
-12 -12
12 -12
Sample Output 2:

0
