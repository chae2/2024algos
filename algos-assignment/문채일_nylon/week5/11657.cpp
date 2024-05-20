// 11657.cpp
#include <iostream>
#include <vector>

#define MAX 510
#define INF 987654321
using namespace std;
 
int N, M;
long long Dist[MAX]; // 각정점까지의 최단거리 저장하는 배열.
vector<pair<pair<int, int>, int>> Edge; // 간선 정보 <<출발-도착>-비용>
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); // C표준, C++ 표준입출력 + 입출력 스트림 비동기화해서 입출력 기능 향상.

    cin >> N >> M;
    for (int i = 1; i <= N; i++) Dist[i] = INF; // 모든 정점까지 거리 초기화.
    for (int i = 0; i < M; i++)
    {
        int From, To, Cost;
        cin >> From >> To >> Cost; // 간선 정보 입력받아 Edge 벡터에 저장.
        Edge.push_back(make_pair(make_pair(From, To), Cost));
    }

    Dist[1] = 0; // 출발정점 거리 0 초기화

    // 벨만포드 알고리즘

    for (int i = 1; i <= N - 1; i++)
    {
        for (int j = 0; j < Edge.size(); j++)
        {
            int From = Edge[j].first.first;
            int To = Edge[j].first.second;
            int Cost = Edge[j].second;
 
            if (Dist[From] == INF) continue; // skip
 
            if (Dist[To] > Dist[From] + Cost) Dist[To] = Dist[From] + Cost; // 현재경로가 더 짧을 시 업뎃
        }
    }

    // 음수 사이클 확인
 
    for (int i = 0; i < Edge.size(); i++)
    {
        int From = Edge[i].first.first;
        int To = Edge[i].first.second;
        int Cost = Edge[i].second;
 
        if (Dist[From] == INF) continue;
        if (Dist[To] > Dist[From] + Cost)
        {
            cout << -1 << '\n';
            return 0;
        }
    }
 

    // 결과(최단거리) 출력
    for (int i = 2; i <= N; i++)
    {
        if (Dist[i] == INF) cout << -1 << endl; // 도달할 수 없는 정점
        else cout << Dist[i] << endl;
    }

 
    return 0;
}
