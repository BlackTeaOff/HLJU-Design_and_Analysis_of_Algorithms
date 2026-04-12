#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void findMode(int a[], int low, int high, int *mode_val, int *max_count) {
    // 左右范围, 众数值及重数
    if (low > high) {
        return;
    }

    int mid = (high + low) / 2; // 中间位置
    int mid_val = a[mid]; // 中间位置的值

    int l = mid; // 从中间找相同连续元素的左边界
    while (l >= low && a[l] == mid_val) { // 不能超过左边界, 而且该值等于中间值
        l--; // 边界向左移
    }
    l++; // 多移的一位加回来

    int r = mid;
    while (r <= high && a[r] == mid_val) { // 同上, 向上找右边界
        r++; // 相等且不超边界就向右移
    }
    r--; // 多移的一位减回去

    // 此时数组被l和r分成了三组, low——l-1, l——r, r+1——high
    int current_count = r - l + 1; // 中间元素有多少个相同的, 也就是中间元素的重数

    if (current_count > *max_count) { // 如果这个重数大于最大重数
        *max_count = current_count; // 更新最大重数
        *mode_val = mid_val; // 更新众数
    }

    // 接下来找左右两个组里的
    if (l - low > *max_count) { // 左组的元素总数大于当前最大重数, 才有可能出现新的众数
        findMode(a, low, l - 1, mode_val, max_count);
    }

    if (high - r > *max_count) { // 右半区同理
        findMode(a, r + 1, high, mode_val, max_count);
    }
}

int main() {
    int n = 0;
    printf("请输入元素个数: ");
    scanf("%d", &n);

    int a[n];
    printf("请输入各个元素: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    qsort(a, n, sizeof(int), cmp);

    int mode_val = a[0]; // 众数
    int max_count = 0; // 重数

    findMode(a, 0, n - 1, &mode_val, &max_count);

    printf("众数是: %d\n", mode_val);
    printf("重数是: %d\n", max_count);

    return 0;
}