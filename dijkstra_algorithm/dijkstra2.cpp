#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

void dijkstra(int n, const vector<vector<int>>& W, vector<pair<int, int>>& F) {
    vector<int> touch(n);   // 각 정점에 연결된 가장 가까운 정점
    vector<int> length(n);  // 시작 정점(0)부터 각 정점까지의 최단 거리
    vector<bool> visited(n, false); // 방문 여부를 추적

    F.clear(); // 최단 경로 트리를 저장할 집합 F 초기화

    // 초기화: v0에서 각 정점까지의 거리와 연결 정보를 설정
    for (int i = 1; i < n; i++) {
        touch[i] = 0;       // 초기에는 모든 정점이 v0과 연결되어 있다고 가정
        length[i] = W[0][i]; // v0에서 각 정점까지의 거리
    }

    visited[0] = true; // 시작 정점 v0은 방문했다고 표시

    // n-1번 반복: 모든 정점을 추가
    for (int step = 1; step < n; step++) {
        int min = INT_MAX;
        int vnear = -1;

        // 방문하지 않은 정점 중 최단 거리의 정점을 찾음
        for (int i = 1; i < n; i++) {
            if (!visited[i] && length[i] < min) {
                min = length[i];
                vnear = i;
            }
        }

        // vnear가 유효하지 않은 경우 종료
        if (vnear == -1) {
            break; // 더 이상 연결 가능한 정점이 없으면 종료
        }

        // 최단 거리의 정점을 최단 경로 트리 집합 F에 추가
        F.push_back({touch[vnear], vnear});
        visited[vnear] = true;

        // 나머지 정점들의 최단 거리와 연결 정보를 갱신
        for (int i = 1; i < n; i++) {
            if (!visited[i] && W[vnear][i] < INT_MAX) {
                if (length[vnear] + W[vnear][i] < length[i]) {
                    length[i] = length[vnear] + W[vnear][i];
                    touch[i] = vnear;
                }
            }
        }
    }
}

int main() {
    int n = 6; // 정점의 개수
    vector<vector<int>> W = {
        {0, 2, 4, INT_MAX, INT_MAX, 1}, // vertex 1
        {INT_MAX, 0, 1, 7, INT_MAX, INT_MAX}, // vertex 2
        {INT_MAX, INT_MAX, 0, 3, INT_MAX, INT_MAX}, // vertex 3
        {INT_MAX, INT_MAX, INT_MAX, 0, 2, INT_MAX}, // vertex 4
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0, 5}, // vertex 5
        {INT_MAX, INT_MAX, INT_MAX, 2, 1, 0} // vertex 6
    };

    vector<pair<int, int>> F; // 최단 경로 트리의 간선 집합

    dijkstra(n, W, F);

    // 결과 출력
    for (const auto& edge : F) {
        cout << "(" << edge.first + 1 << ", " << edge.second + 1 << ") " << W[edge.first][edge.second] << endl;
    }

    return 0;
}
