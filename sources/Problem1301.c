#include <stdio.h>
#include <stdlib.h>
#define N 100000 + 1
typedef struct node
{
    int id;
    int cost;
    struct node *next;
} NODE;
NODE *tree[N];
int depth[N];
int main()
{
    int T, n, p, s, t, u, v, w;
    scanf("%d", &T);
    while (--T)
    {
        depth[1]=0;//1号节点是根节点，深度为0
        scanf("%d%d%d%d", &n, &p, &s, &t);
        for (int i = 0; i < n - 1; i++)
        {
            scanf("%d%d%d", &u, &v, &w);
            NODE *temp = (NODE *)malloc(sizeof(NODE));
            temp->id = v;
            temp->cost = w;
            temp->next = tree[u];
            tree[u] = temp;
            depth[v]=depth[u]+1;
        }
    }
}