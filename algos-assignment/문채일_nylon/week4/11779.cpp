// 11779.cpp
#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
#include <algorithm>

using namespace std;

const int INF = INT_MAX;
const int MAX_V = 1001;

int n, m;
int start, e;
vector<tuple<int, int, int>> edges;
int dist[MAX_V];
int parent[MAX_V];

void bellman_ford(int src) {
    fill(dist, dist + MAX_V, INF);
    fill(parent, parent + MAX_V, -1);
    dist[src] = 0;

    for (int i = 1; i < n; ++i) {
        for (const auto& edge : edges) {
            int u, v, cost;
            tie(u, v, cost) = edge;
            if (dist[u] != INF && dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                parent[v] = u;
            }
        }
    }
}

void print_path(int dest) {
    vector<int> path;
    for (int at = dest; at != -1; at = parent[at]) {
        path.push_back(at); // 이미 생성된 객체 추가.
    }
    reverse(path.begin(), path.end());
    cout << path.size() << endl;
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int u, v, cost;
        cin >> u >> v >> cost;
        edges.emplace_back(u, v, cost); // 객체 생성과 동시에 추가.
    }

    cin >> start >> e;

    bellman_ford(start);

    cout << dist[e] << endl;
    print_path(e); // 거쳐가는 도시 프린트.

    return 0;
}
