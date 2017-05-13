/**
 * 1002. A+B for Polynomials (25)
 * 
 * This time, you are supposed to find A+B where A and B are two polynomials.
 * 
 * Input
 * 
 * Each input file contains one test case. Each case occupies 2 lines, and each 
 * line contains the information of a polynomial: K N1 a_N1 N2 a_N2 ... NK a_NK,
 * where K is the number of nonzero terms in the polynomial, Ni and a_Ni (i=1, 
 * 2, ..., K) are the exponents and coefficients, respectively. It is given that
 * 1 <= K <= 10，0 <= NK < ... < N2 < N1 <=1000.
 * 
 * Output
 * 
 * For each test case you should output the sum of A and B in one line, with the
 * same format as the input. Notice that there must be NO extra space at the end
 * of each line. Please be accurate to 1 decimal place.
 * 
 * Sample Input
 * 2 1 2.4 0 3.2
 * 2 2 1.5 1 0.5
 * Sample Output
 * 3 2 1.5 1 2.9 0 3.2
 */

#include <stdio.h>
#include <math.h>

typedef struct Poly{
    double coef;
    int exp;
} Poly[20];

int main()
{
    int KA, KB, Ksum = 0;
    Poly A, B, sum;
    
    scanf("%d", &KA);
    for(int i = 0; i < KA; i++) scanf("%d %lf", &A[i].exp, &A[i].coef);
    scanf("%d", &KB);
    for(int i = 0; i < KB; i++) scanf("%d %lf", &B[i].exp, &B[i].coef);
    
    int i = 0, j = 0;
    while(i < KA || j < KB)
    {
        if(i == KA || (j < KB && A[i].exp < B[j].exp))
        {
            sum[Ksum].exp = B[j].exp;
            sum[Ksum].coef = B[j++].coef;
        }
        else if(j == KB || (i < KA && A[i].exp > B[j].exp))
        {
            sum[Ksum].exp = A[i].exp;
            sum[Ksum].coef = A[i++].coef;
        }
        else
        {
            sum[Ksum].exp = A[i].exp;
            sum[Ksum].coef = A[i++].coef + B[j++].coef;
        }
        if(fabs(sum[Ksum].coef) >= 0.05) Ksum++;
    }
    
    printf("%d", Ksum);
    
    for(int i = 0; i < Ksum; i++) 
        printf(" %d %.1lf", sum[i].exp, sum[i].coef);
    
    return 0;
}
