#include <stdio.h>

typedef struct {
    double weight;
    double value;
    double fraction; // 装入比例
} Item;

void knapsack() {
    int capacity;
    printf("请输入背包容量: ");
    scanf("%d", &capacity);
    int n;
    printf("请输入物品数量: ");
    scanf("%d", &n);

    Item items[n];
    for (int i = 0; i < n; i++) {
        printf("请输入第%d个物品的重量和价值: ", i + 1);
        scanf("%lf %lf", &items[i].weight, &items[i].value);
        items[i].fraction = 0;
    }

    double totalValue = 0;
    double currentWeight = 0; // 当前背包装的重量

    // 已经按照单位重量价值递减的次序排序, 直接依次放入
    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].weight <= capacity) {
            items[i].fraction = 1;
            currentWeight += items[i].weight;
            totalValue += items[i].value;
        } else {
            double remainCapacity = capacity - currentWeight;
            items[i].fraction = remainCapacity / items[i].weight;
            totalValue += items[i].value * items[i].fraction;
            break;
        }
    }

    printf("%-10s %-10s %-15s\n", "物品", "价值", "装入比例");
    for (int i = 0; i < n; i++) {
        if (items[i].fraction > 0) {
            // 左对齐, 保留两位小数
            printf("%-10d %-10.2f %.2f\n", i + 1, items[i].value, items[i].fraction);
        }
    }

    printf("总价值: %.2f\n", totalValue);

    // for (int i = 0; i < n; i++) {
    //     printf("第%d个物品的重量和价值: %lf %lf\n", i + 1, items[i].weight, items[i].value);
    // }
}

int main() {
    knapsack();
}