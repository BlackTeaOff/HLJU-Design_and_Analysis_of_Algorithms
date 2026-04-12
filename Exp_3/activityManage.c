#include <stdio.h>

typedef struct {
    int id;
    int start;
    int finish;
} Activity;

void activityManage() {
    int n;
    printf("请输入活动的个数: ");
    scanf("%d", &n);

    Activity activities[n];
    Activity selected[n];

    for (int i = 0; i < n; i++) {
        printf("请输入第%d个活动的开始时间和结束时间: ", i + 1);
        scanf("%d %d", &activities[i].start, &activities[i].finish);
        activities[i].id = i + 1;
    }

    int count = 0; // 选中的个数, 也当selected下标
    // 已按结束时间升序排序, 第一个就是结束时间最早的, 必选
    selected[count++] = activities[0];
    int lastFinishTime = activities[0].finish; // 下节课的开始时间需要大于等于这节课的结束时间

    for (int i = 1; i < n; i++) {
        if (activities[i].start >= lastFinishTime) {
            selected[count++] = activities[i];
            lastFinishTime = activities[i].finish; // 更新最后结束时间
        }
    }

    printf("%-10s %-10s %-10s\n", "活动号", "开始时间", "结束时间");
    for (int i = 0; i < count; i++) {
        printf("%-10d %-10d %-10d\n", selected[i].id, selected[i].start, selected[i].finish);
    }
}

int main() {
    activityManage();
}