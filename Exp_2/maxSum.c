#include <stdio.h>
#include <stdlib.h>

// 数组, 大小, 左右区间
void maxSum(int *a, int size, int left, int right) {
    int maxSum = a[left]; // 最大子段和(不能等于0, 因为如果都是负数, 那0就是最大的)
    int currentSum = a[left]; // 当前子段的和
    int start = left; // 起始下标
    int end = left; // 终止下标
    int tempStart = left; // 临时起点下标(因为新开的子段不一定比之前的子段的子段和大, 所以新开子段的时候用它来记录, 如果这个子段更大的情况下, 再把起始下标设置为新开的这个子段的下标)

    for (int i = left + 1; i <= right; i++) {
        if (currentSum > 0) { // 如果当前子段和大于0, 那就把当前的数加到里面
            currentSum += a[i];
        } else {
            currentSum = a[i]; // 如果当前子段和小于等于0, 那就抛弃前面的子段, 从当前位置新开一个子段(任何数加上负数都比本身小)
            tempStart = i; // 更新临时子段下标
        }

        if (currentSum > maxSum) {
            maxSum = currentSum; // 加完当前数后, 当前子段和大于最大子段和, 更新最大子段和
            start = tempStart; // 更新起始下标(如果没开新子段, tempStart和start相等)
            end = i; // 更新终止下标
        }
    }

    printf("最大子段和: %d\n", maxSum);
    printf("起始下标: %d\n", start);
    printf("终止下标: %d\n", end);

    // printf("%p\n", a);
    // printf("%d\n", size);
    // printf("%d\n", left);
    // printf("%d\n", right);
}

int main() {
    int n;
    printf("请输入元素个数: ");
    scanf("%d", &n);
    int *a = malloc(n * sizeof(int));
    printf("请输入各个元素: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int left, right;
    printf("请输入左右区间: ");
    scanf("%d %d", &left, &right);

    maxSum(a, n, left, right);

    free(a);

    // for (int i = 0; i < n; i++) {
    //     printf("%d\n", a[i]);
    // }
}