#include <stdio.h>
#include <stdlib.h>

int *S; // 集合S
int *x; // 解, 0代表不加, 1代表加
int n;
int M;
int solution_count = 0;

// t-当前元素下标
void backtrack(int t, int current_sum, int remaining_sum) {
    if (current_sum == M) {
        solution_count++;

        printf("\n第 %d 个解: \n", solution_count);
        printf("S1 = {");
        int is_first = 1;
        // 只需要遍历到当前元素下标, 因为后面的还没加或者舍弃
        for (int i = 0; i < t; i++) {
            if (x[i] == 1) {
                if (!is_first) {
                    printf(", ");
                }
                printf("%d", S[i]);
                is_first = 0;
            }
        }
        printf("}\n");
        return;
    }

    if (t == n) {
        return;
    }

    // 当前的和加上当前元素(S[t])小于等于M, 把当前的数加到和里(如果大于M后面不加也大于M, 不能继续加了)
    if (current_sum + S[t] <= M) {
        x[t] = 1;
        backtrack(t + 1, current_sum + S[t], remaining_sum - S[t]);
    }

    // 不选当前元素S[t]
    // 当前的和加上集合里剩下元素的和(不带S[t])大于等于M, 就不选当前元素向后递归(如果小于M后面怎么加都加不到M)
    if (current_sum + remaining_sum - S[t] >= M) {
        x[t] = 0;
        backtrack(t + 1, current_sum, remaining_sum - S[t]);
    }
}

int main() {
    int total_sum = 0; // 集合内所有元素的和

    printf("请输入集合S中元素的个数: ");
    scanf("%d", &n);

    S = (int *)malloc(n * sizeof(int));
    x = (int *)malloc(n * sizeof(int));

    printf("请输入集合S中的正整数: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &S[i]);
        total_sum += S[i];
    }

    printf("请输入正整数M: ");
    scanf("%d", &M);

    backtrack(0, 0, total_sum);

    if (solution_count == 0) {
        printf("无解\n");
    }

    free(S);
    free(x);
    
    return 0;
}