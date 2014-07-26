#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
#define inf  1 << 30
#define M 5005
int n, m, countt, ans;
int map1[55][55], head[M], pre_node[M], distances[M];
bool visited[M];
 
struct node {
	int u, v, weight, flow, next;
} edge[100005];
void add(int u, int v, int w, int f) {
	edge[countt].u = u;
	edge[countt].v = v;
	edge[countt].weight = w;
	edge[countt].flow = f;
	edge[countt].next = head[u];
	head[u] = countt;
	countt++;
	edge[countt].u = v;
	edge[countt].v = u;
	edge[countt].weight = -w;
	edge[countt].flow = 0;
	edge[countt].next = head[v];
	head[v] = countt;
	countt++;
}
bool spfa() {
	for (int i = 0; i <= n * n * 2 + 1; i++) {
		pre_node[i] = -1;
		distances[i] = inf;
		visited[i] = false;
	}
	queue <int> q;
	distances[n * n * 2] = 0;
	visited[n * n * 2] = true;
	q.push(n * n * 2);
	int i;
	while (!q.empty()) {
		int t = q.front();
		q.pop();
		i = head[t];
		visited[t] = false;
		while (i != -1) {
			if (edge[i].flow > 0 && distances[edge[i].v] > distances[t] + edge[i].weight) {
				distances[edge[i].v] = distances[t] + edge[i].weight;
				pre_node[edge[i].v] = i;
				if (!visited[edge[i].v]) {
					visited[edge[i].v] = true;
					q.push(edge[i].v);
				}
			}
			i = edge[i].next;
		}
	}
	if (pre_node[n * n * 2 + 1] == -1) {
		return false;
	}
	return true;
}
void getMaxflow() {
	while (spfa()) {
		int max1 = inf;
		int p = pre_node[n * n * 2 + 1];
		while (p != -1) {
			max1 = min(max1, edge[p].flow);
			p = pre_node[edge[p].u];
		}
		p = pre_node[n * n * 2 + 1];
		while (p != -1) {
			edge[p].flow -= max1;
			edge[p ^ 1].flow += max1;
			ans += max1 * edge[p].weight;
			p = pre_node[edge[p].u];
		}
	}
}
 
int main() {
	while (cin >> n >> m) {
		int i, j;
		countt = 0;
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				cin >> map1[i][j];
			}
		}
		memset(head, -1, sizeof(head));
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				int u = (i - 1) * n + j - 1;
				add(u * 2, u * 2 + 1, -map1[i][j], 1);
				add(u * 2, u * 2 + 1, 0, m - 1);
			}
		}
		for (i = 1; i <= n; i++) {
			for (j = 1; j < n; j++) {
				int u = (i - 1) * n + j - 1;
				add(u * 2 + 1, (u + 1) * 2, 0, m);
			}
		}
		for (i = 1; i < n; i++) {
			for (j = 1; j <= n; j++) {
				int u = (i - 1) * n + j - 1;
				add(u * 2 + 1, (u + n) * 2, 0, m);
			}
		}
		add(n * n * 2, 0, 0, m);
		add(n * n * 2 - 1, n * n * 2 + 1, 0, m);
		ans = 0;
		getMaxflow();
		cout << -ans << endl;
	}
	return 0;
}
