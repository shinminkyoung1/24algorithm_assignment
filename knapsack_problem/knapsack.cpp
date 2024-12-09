#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n = 4;             // 물건의 개수
int W = 16;            // 최대 허용 무게
vector<int> p(5);      // 물건의 가치 배열 (인덱스 1부터 사용)
vector<int> w(5);      // 물건의 무게 배열 (인덱스 1부터 사용)
int maxprofit = 0;  
vector<string> include(5, "NO"); // 현재 포함 여부
vector<string> bestset(5, "NO"); // 최적 포함 여부

bool promising(int i, int profit, int weight) {
    if (weight >= W) return false;

    int j = i + 1;
    int totweight = weight;
    float bound = profit;

    // 가능한 최대 bound 계산
    while (j <= n && totweight + w[j] <= W) {
        totweight += w[j];
        bound += p[j];
        j++;
    }

    // 남은 공간에 부분적으로 물건 추가
    if (j <= n) {
        bound += (W - totweight) * (float)p[j] / w[j];
    }

    return bound > maxprofit;
}

void knapsack(int i, int profit, int weight) {
    // maxprofit 업데이트
    if (weight <= W && profit > maxprofit) {
        maxprofit = profit;
        bestset = include;
    }

    // promising한 경우 탐색
    if (promising(i, profit, weight)) {
        include[i + 1] = "YES"; // 현재 물건 포함
        knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);

        include[i + 1] = "NO";  // 현재 물건 미포함
        knapsack(i + 1, profit, weight);
    }
}

int main() {
    // 인덱스 1부터 시작
    p[1] = 40;
    p[2] = 30;
    p[3] = 50;
    p[4] = 10;

    w[1] = 2;
    w[2] = 5;
    w[3] = 10;
    w[4] = 5;

    knapsack(0, 0, 0);

    cout << "maxProfit: " << maxprofit << endl;

    cout << "best set:" << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << ": " << bestset[i] << endl;
    }

    return 0;
}
