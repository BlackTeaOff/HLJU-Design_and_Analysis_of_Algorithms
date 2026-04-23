#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *x; // 结果数组, x[i]代表第i行皇后在哪一列
int sum = 0;

// 约束函数, 检查第k行的皇后能否放在这个位置, 不用传具体放在了哪一列, 因为x[k]里就有
int constraint(int k) {
    // 遍历每一行
    for (int i = 1; i < k; i++) {
        // 如果第i行和当前第k行皇后位置(列)相同(处在同一列), 或处在同一对角线(行-行的绝对值等于列-列的绝对值), 返回0代表有冲突
        if (x[i] == x[k] || abs(i - k) == abs(x[i] - x[k])) {
            return 0;
        }
    }
    return 1;
}

void print_solution(int n) {
    sum++;
    printf("第 %d 个解:\n", sum);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i] == j) {
                printf(" x ");
            } else {
                printf(" . ");
            }
        }
        printf("\n");
    }
}

// k-当前的行数, n-皇后的个数(一行放一个皇后, 有n个皇后棋盘就是n×n的大小, n行n列)
void backtrack(int k, int n) {
    if (k > n) { // 如果当前行数大于棋盘行数, 代表找到一个解
        print_solution(n);
    } else {
        // 放置第k行皇后的位置(放在哪一列), 若有多个解会回溯继续进行for循环, 找下一个能放的列
        for (int i = 1; i <= n; i++) {
            x[k] = i; // 第k行的皇后放在第i列(这个位置如果冲突也不需要改回0, 回溯后还会回来, 覆盖掉这个值)
            if (constraint(k)) { // 如果当前位置可行, 继续找下一行皇后的位置
                backtrack(k + 1, n);
            }
        }
    }
}

int main() {
    int n;
    printf("请输入皇后的个数: ");
    scanf("%d", &n);

    x = (int *)malloc((n + 1) * sizeof(int));
    backtrack(1, n);

    if (sum == 0) {
        printf("无可行解\n");
    }

    free(x);

    return 0;
}