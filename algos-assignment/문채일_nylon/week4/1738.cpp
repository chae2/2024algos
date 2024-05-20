// 1738.cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

const int MAX_V = 101;
const int INF = INT_MAX; // climits에 정의됨.

int n, m, a, b, c, cycle = 0;
vector<pair<int, int>> adj[MAX_V];
vector<int> rev[MAX_V];
int dist[MAX_V], pre[MAX_V], vis[MAX_V];

void bellman_ford(int st) {
    fill(dist, dist + MAX_V, INF); // 메모리 최적화.
    fill(pre, pre + MAX_V, -1);
    dist[st] = 0;

    for (int iter = 1; iter <= n; iter++) {
        for (int cur = 1; cur <= n; cur++) {
            if (dist[cur] == INF) continue;
            for (auto &u : adj[cur]) {
                int next = u.first, cost = u.second;
                if (dist[next] > dist[cur] + cost) {
                    dist[next] = dist[cur] + cost;
                    pre[next] = cur;
                    if (iter == n && vis[next]) cycle = 1; // 음의사이클 존재.
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        adj[a].push_back({b, -c});
        rev[b].push_back(a);
    }

    queue<int> q;
    q.push(n);
    vis[n] = 1;
    while (!q.empty()) { // visited 체크.
        int cur = q.front();
        q.pop();
        for (int next : rev[cur]) {
            if (!vis[next]) {
                vis[next] = 1;
                q.push(next);
            }
        }
    }

    bellman_ford(1);

    if (cycle) {
        cout << -1 << endl;
    } else {
        if (dist[n] == INF) {
            cout << -1 << endl;
        } else {
            vector<int> path;
            for (int at = n; at != -1; at = pre[at]) {
                path.push_back(at);
            }
            reverse(path.begin(), path.end());
            for (int i = 0; i < path.size(); i++) {
                if (i > 0) cout << " ";
                cout << path[i];
            }
            cout << endl;
        }
    }

    return 0;
}
