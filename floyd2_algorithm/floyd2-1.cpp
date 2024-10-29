#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max(); // 무한대 정의 (경로가 없는 경우)

void floyd2(int n, const vector<vector<int>>& W, vector<vector<int>>& D, vector<vector<int>>& P) {
    int i, j, k;

    // P와 D 초기화
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            P[i][j] = 0; // 경로를 추적하기 위한 중간 vertex
        }
    }

    D = W; // D 행렬을 초기 가중치 행렬 W로 설정

    // floyd's algorithm
    for (k = 1; k <= n; k++) { // 중간 정점 k를 통해 최단 경로 갱신 (path)
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                // D[i][k]와 D[k][j]가 INF가 아니고, 경유 경로가 더 짧다면 갱신
                if (D[i][k] != INF && D[k][j] != INF && (D[i][k] + D[k][j] < D[i][j])) {
                    P[i][j] = k; // 최단 경로 상의 중간 정점을 P에 저장
                    D[i][j] = D[i][k] + D[k][j]; // 최단 거리 갱신
                }
            }
        }
    }
}

// 중간 경유 정점을 통해 경로를 출력하는 함수
void path(int q, int r, const vector<vector<int>>& P) {
    if (P[q][r] != 0) { // 중간 정점이 존재하는 경우에만 출력
        path(q, P[q][r], P); // q에서 중간 정점으로의 경로 출력
        cout << "v" << P[q][r]; // 중간 정점 출력
        path(P[q][r], r, P); // 중간 정점에서 r로 가는 경로 출력
    }
}

// 행렬을 출력하는 함수
void printMatrix(const vector<vector<int>>& matrix, int n, const string& name) {
    cout << name << " matrix:\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (matrix[i][j] == INF)
                cout << "INF "; // 무한대 = "INF"
            else
                cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    int n = 5; // 정점의 개수

    // W 정의
    vector<vector<int>> W = {
        {INF, INF, INF, INF, INF, INF},  // index 0 (출력에서는 사용되지 않음)
        {INF, 0, 1, INF, 1, 5},         // W[i][j] for i, j = 1 to n
        {INF, 9, 0, 3, 2, INF},
        {INF, INF, INF, 0, 4, INF},
        {INF, INF, INF, 2, 0, 3},
        {INF, 3, INF, INF, INF, 0}
    };

    // D와 P 행렬 초기화
    vector<vector<int>> D(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> P(n + 1, vector<int>(n + 1, 0));

    floyd2(n, W, D, P);

    // 결과 출력
    printMatrix(W, n, "W"); // 초기 가중치 W
    printMatrix(D, n, "D"); // 최단 거리 D
    printMatrix(P, n, "P"); // 경유 정점 P

    // 특정 경로의 최단 경로 출력
    int start = 2, end = 5;
    path(start, end, P);

    return 0;
}
