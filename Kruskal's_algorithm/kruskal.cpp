#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef int Index;
typedef Index SetPointer;

struct NodeType {
    Index parent; // 부모 노드
    int depth;    // 트리 깊이
};

const int MAXN = 100; // 최대 정점 개수
typedef NodeType universe[MAXN]; // Universe 정의

universe U;

// Makeset: 새로운 집합 초기화
void makeset(Index i) {
    U[i].parent = i;
    U[i].depth = 0;
}

// Find: 루트 노드 찾음 
SetPointer find(Index i) {
    Index j = i;
    while (U[j].parent != j) {
        j = U[j].parent;
    }
    return j;
}

// Merge: 두 집합 병합
void merge(SetPointer p, SetPointer q) {
    if (U[p].depth == U[q].depth) {
        U[p].depth += 1;
        U[q].parent = p;
    } else if (U[p].depth < U[q].depth) {
        U[p].parent = q;
    } else {
        U[q].parent = p;
    }
}

// Equal: 두 집합 같은지 확인
bool equal(SetPointer p, SetPointer q) {
    return p == q;
}

// Initial: 모든 정점을 독립된 집합으로 초기화
void initial(int n) {
    for (int i = 1; i <= n; i++) {
        makeset(i);
    }
}

// 간선 구조체
struct Edge {
    int u, v, weight;

    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

// 간선 정렬을 위한 비교 함수
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// Kruskal 알고리즘
void kruskal(int n, vector<Edge>& edges, vector<Edge>& mst) {

    // 1. 간선 가중치 기준으로 정렬
    sort(edges.begin(), edges.end(), compareEdges);

    // 2. Disjoint Set 초기화
    initial(n);

    // 3. MST 구성
    for (const auto& edge : edges) {
        int rootU = find(edge.u);
        int rootV = find(edge.v);

        if (!equal(rootU, rootV)) {
            merge(rootU, rootV); // 두 정점 병합
            mst.push_back(edge); // 최소 신장 트리에 간선 추가
            if (mst.size() == n - 1) break; 
        }
    }
}


int main() {
    int n = 5; // 정점 개수
    vector<Edge> edges = {
        Edge(1, 2, 1),
        Edge(1, 3, 3),
        Edge(2, 4, 6),
        Edge(3, 4, 4),
        Edge(3, 5, 2),
        Edge(4, 5, 5),
        Edge(2, 3, 3),
    };
    vector<Edge> mst; // MST 결과 저장

    kruskal(n, edges, mst);

    // 결과 출력
    for (const auto& edge : mst) {
        cout << "(" << edge.u << ", " << edge.v << ", " << edge.weight << ")\n";
    }

    return 0;
}
