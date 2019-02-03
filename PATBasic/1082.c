#include <stdio.h>

int main()
{
    int best_id, worst_id, cur_id;
    int x, y, N;
    int min_dist_sq = 99999, max_dist_sq = -1, cur_dist_sq;

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%d %d %d", &cur_id, &x, &y);
        cur_dist_sq = x * x + y * y;
        if(min_dist_sq > cur_dist_sq)
        {
            min_dist_sq = cur_dist_sq;
            best_id = cur_id;
        }
        if(max_dist_sq < cur_dist_sq)
        {
            max_dist_sq = cur_dist_sq;
            worst_id = cur_id;
        }
    }

    printf("%04d %04d", best_id, worst_id);

    return 0;
}
