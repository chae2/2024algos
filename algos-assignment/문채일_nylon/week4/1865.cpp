// 1865.cpp

#include <iostream>
#include <string>
#include <vector>

#define MAX 30'000'000

using namespace std;

int n, m, w;

struct edge {
	int s, e, t; // 출발-끝-비용
};

// 해당 문제는 출발을 하고 나서 시간이 더 지나있는 == 음의 사이클을 판단하는 문제.

bool time_travel(int n, vector<edge> edges) {
	vector<int> dist(n + 1, MAX);

	int s, e, t;
	dist[1] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < edges.size(); j++) { // for (auto [s, e, t] : edges)
			s = edges[j].s;
			e = edges[j].e;
			t = edges[j].t;
			if (dist[e] > dist[s] + t) {
				dist[e] = dist[s] + t;
                if (i==n)
                    return true; // 음의 사이클 존재.
			}
		}
	}

	return false; // 기본
}

int main()
{
	cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false);

	int TC;
	cin >> TC;

	int s, e, t;
	while (TC > 0) {
		cin >> n >> m >> w;

		vector<edge> edges;

		for (int i = 0; i < m; i++) {
			cin >> s >> e >> t;
			edges.push_back({ s,e,t });
			edges.push_back({ e,s,t });
		}
		for (int i = 0; i < w; i++) {
			cin >> s >> e >> t;
			edges.push_back({ s,e,-t });
		}

		if (time_travel(n, edges)) cout << "YES\n";
		else cout << "NO\n";

		TC--;
	}

	return 0;
}
