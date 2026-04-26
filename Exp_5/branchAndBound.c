#include <stdio.h>
#include <stdlib.h>

#define INF 999999 // 无穷大
#define MAX_N 100 // 最大顶点数
#define MAX_HEAP 10000 // 堆的最大容量

int Matrix[MAX_N][MAX_N]; // 邻接矩阵
int dist[MAX_N]; // 源点到每个顶点的当前已知最短距离
int pre[MAX_N]; // 该顶点在最短路径上的前驱结点, 用来找回原路
int n; // 顶点数

// 小根堆中一个节点的结构体
typedef struct {
    int id; // 顶点编号
    int length; // 当前路径长度, 该节点到源点目前的最短路径
} Node;

Node heap[MAX_HEAP];
int heap_size = 0;

void swap(Node *a, Node *b) { // 交换堆中的两个节点
    Node temp = *a; // 解指针
    *a = *b;
    *b = temp;
}

// 入堆, 从下向上浮(活节点)
void push(int id, int length) {
    heap[++heap_size] = (Node){id, length}; // 堆从下标1开始存
    int curr = heap_size; // heap_size就是最后一个元素的下标(刚加进去的)

    // 上浮, 看这个节点和它的父节点谁更小, 更小的当父节点(维护小根堆)
    while (curr > 1 && heap[curr].length < heap[curr / 2].length) {
        swap(&heap[curr], &heap[curr / 2]);
        curr /= 2;
    }
}

Node pop() {
    Node min_node = heap[1]; // 从堆顶取出最小元素, 返回
    heap[1] = heap[heap_size--]; // 堆中最后一个元素取出放到堆顶, 维护小根堆(下沉)

    int curr = 1; // 堆顶下沉, 看它的左右孩子和它本身, 它更大就向下沉
    while (curr * 2 <= heap_size) { // 当前节点没有左孩子(肯定也没有右孩子), 代表到叶子节点了, 不用继续调整
        int child = curr * 2;
        // 找左右孩子中更小的那个, 右面的孩子更小就child++(首先要有右孩子)
        if (child + 1 <= heap_size && heap[child + 1].length < heap[child].length) {
            child++;
        }
        if (heap[curr].length <= heap[child].length) { // 当前节点已经小于或等于左右孩子更小的一个, 就不用调整了
            break;
        }
        swap(&heap[curr], &heap[child]); // 交换当前节点和左右孩子更小的那个
        curr = child; // 当前节点设为交换后的节点下标
    }
    return min_node;
}

int is_empty() {
    return heap_size == 0;
}

// source-起点节点编号
void branch_and_bound(int source) {
    // 初始化, 节点i到源点的距离设为无穷大, 前驱设为-1
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        pre[i] = -1;
    }

    // 初始化源点
    dist[source] = 0;
    push(source, 0); // 放入小根堆中

    while (!is_empty()) {
        Node current = pop(); // 每次将最小活节点(堆顶)取出来(length最小, 离源点最近)
        int u = current.id;
        int d = current.length;

        if (d > dist[u]) { // 取出的路径长度大于当前已知最短路径, 舍弃该路径
            continue;
        }

        // 以该节点更新最短路径
        // 遍历该节点能到的所有节点, 如果比当前已知最短路径还短就保存并放入堆中
        for (int v = 0; v < n; v++) {
            // 源点-u-v比源点-v更短, 更新源点到v的最短路径
            if (Matrix[u][v] != INF && dist[u] + Matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + Matrix[u][v];
                pre[v] = u;

                push(v, dist[v]); // 把这个新节点v放入堆中
            }
        }
    }
}

void print_result(int source) {
    printf("源点 %d 到各顶点的最短路径: \n", source);
    // 遍历除了源点的所有节点
    for (int i = 0; i < n; i++) {
        if (i == source) {
            continue;
        }

        if (dist[i] == INF) {
            printf("由源点 %d 无法到达顶点 %d\n", source, i);
        } else {
            printf("到顶点 %d 的最短距离为: %d \n路径为: ", i, dist[i]);

            int path[MAX_N];
            int top = -1;
            int current = i;

            while (current != -1) {
                path[++top] = current;
                current = pre[current];
            }

            while (top >= 0) {
                printf("%d", path[top--]);
                if (top >= 0) {
                    printf(" -> ");
                }
            }
            printf("\n");
        }
    }
}

int main() {
    n = 5;
    
    int graph[5][5] = {
        {0,   10,  INF, 30,  100},
        {INF, 0,   50,  INF, INF},
        {INF, INF, 0,   INF, 10},
        {INF, INF, 20,  0,   60},
        {INF, INF, INF, INF, 0}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Matrix[i][j] = graph[i][j];
        }
    }

    int source = 0;

    branch_and_bound(source);

    print_result(source);

    return 0;
}
