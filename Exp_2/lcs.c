#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LCS(char *X, char* Y) {
    int m = strlen(X);
    int n = strlen(Y);

    // 二维数组c[m+1][n+1]
    int **c = malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        c[i] = calloc((n + 1), sizeof(int)); // 每个元素初始化为0
    }

    // c[0][n]和c[m][0]部分都为0, 因为D[i][j]代表第一个串前i个字符和第二个串前j的字符的最长公共子序列长度, 有一边是前0个字符所以没有公共子序列(i, j从1开始的原因)
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) { // i-1是因为字符数组是从0开始的
                c[i][j] = c[i - 1][j - 1] + 1; // 两个字符相等就让这个值等于左上角的值(D[i][j]=1+D[i-1][j-1])
            } else if (c[i - 1][j] >= c[i][j - 1]) { // 上
                c[i][j] = c[i - 1][j]; // 两个字符不相等就让这个值等于max(左面的值, 上面的值)(D[i][j]=max(D[i-1][j], D[i][j-1]))
            } else {
                c[i][j] = c[i][j - 1]; // 左
            }
        }
    }

    // c[m][n]代表X里前m个字符和Y里前n的字符的最长公共子序列长度
    int lcs_length = c[m][n];

    printf("最长公共子序列长度: %d\n", lcs_length);

    // 倒推求最长公共子序列
    if (lcs_length > 0) {
        char lcs_str[lcs_length + 1]; // 带'\0'
        lcs_str[lcs_length] = '\0';
        int index = lcs_length - 1; // 倒着存

        int i = m, j = n;
        while (i > 0 && j > 0) {
            if (X[i - 1] == Y[j - 1]) { // 字符相等就向左上, 并记录公共的字母
                lcs_str[index--] = X[i - 1];
                i--;
                j--;
            } else if (c[i - 1][j] >= c[i][j - 1]) { // 字符不相等就看左和上, 谁大就向哪走
                i--; // 向上
            } else {
                j--; // 向左
            }
        }
        printf("最长公共子序列: %s\n", lcs_str);
    }

    for (int i = 0; i <= m; i++) {
        free(c[i]);
    }
    free(c);
}

int main() {
    char X[100];
    char Y[100];
    printf("输入第一个字符串: ");
    scanf("%s", X);
    printf("输入第二个字符串: ");
    scanf("%s", Y);

    LCS(X, Y);

    // printf("%s\n", X);
    // printf("%s\n", Y);
}