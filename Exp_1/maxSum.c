#include <stdio.h>

typedef struct {
    int sum; // 最大字段和
    int start; // 起始下标
    int end; // 终止下标
} SubInfo;

// int max(int a, int b) {
//     return a > b ? a : b;
// }

SubInfo acrossSum(int a[], int l, int r, int m) { // 横跨最大子段和
    int sum = 0;
    SubInfo info;
    int L = a[m]; // L是左面最大和, 防止左面都是负数, L设置为从中间开始第一个数
    int L_index = m; // 左半边最大和停止下标
    for (int i = m; i >= l; i--) { // 计算左面最大和
        sum += a[i];
        if (sum > L) { // 如果发现更大的和, 更新左部分最大和及下标
            L = sum;
            L_index = i;
        }
    }
    sum = 0;
    int R = a[m + 1]; // R是右面最大和, 防止右面都是负数, R设置为从中间右面开始第一个数
    int R_index = m + 1; // 记录右半边最大和停止的下标
    for (int i = m + 1; i <= r; i++) { // 计算右面最大和
        sum += a[i];
        if (sum > R) { //  同上
            R = sum;
            R_index = i;
        }
    }

    info.sum = L + R; // 左半部分最大和加右半部分最大和就是横跨最大子段和
    info.start = L_index; // 左右最大和停止下标就是起点和终点
    info.end = R_index;
    return info;
}

SubInfo maxSum(int a[], int l, int r) {
    if (l == r) { // 分到只剩一个数字, 它本身就是最大子段和
        SubInfo info;
        info.sum = a[l];
        info.start = l; // 只有一个元素, 起点和终点都是自己
        info.end = l;
        return info;
    }
    int m = (l + r) / 2;
    SubInfo L = maxSum(a, l, m);
    SubInfo R = maxSum(a, m + 1, r);
    SubInfo LR = acrossSum(a, l, r, m);

    SubInfo best = L; // 返回L, R, LR里最大的子段和
    if (R.sum > best.sum) {
        best = R;
    }
    if (LR.sum > best.sum) {
        best = LR;
    }

    return best;
}

int main() {
    int n = 0;
    printf("请输入元素个数: ");
    scanf("%d", &n);
    int a[n];
    printf("请输入各项元素: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    SubInfo result = maxSum(a, 0, n - 1);
    printf("最大子段和为: %d\n", result.sum);
    printf("起始下标: %d\n", result.start);
    printf("终止下标: %d\n", result.end);
    // for (int i = 0; i < n; i++) {
    //     printf("%d ", a[i]);
    // }
}