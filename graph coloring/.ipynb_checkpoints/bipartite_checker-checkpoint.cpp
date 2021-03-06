//
//  bipartite_checker.cpp
//  practice
//
//  Created by Mahmud on 12/11/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#pragma GCC optimize("-0g")

template <class T>
void fastInput(T &N) {
    char ch;
    int sign = 1;
    N = 0;
    while ((ch = getchar_unlocked()) && ch == ' ') {};
    if (ch == '-') sign = -1;
    else if (isdigit(ch)) N = ch - '0';
    while ((ch = getchar_unlocked()) && isdigit(ch)) {
        N = (N << 1) + (N << 3) + ch - '0';
    }
    if (sign == -1) N = ~N + 1;
}
template<class T> void fastPrint(T n){
    if(n == 0){
        puts("0");
        return;
    }
    char buffer[256];
    int ptr = 0, sign = 1;
    
    if(n < 0){
        sign = -1;
        n *= -1;
    }
    while(n > 0){
        buffer[ptr ++] = (char)(n % 10 + '0');
        n /= 10;
    }
    if(sign == -1)
        putchar_unlocked('-');
    for(int i = ptr - 1; i >= 0; i --)
        putchar_unlocked(buffer[i]);
    putchar_unlocked('\n');
}


typedef vector<vector<int> > graph;

int N, M;
graph G;
vector<int> colors;
bool cycle = false;

void dfs(int node, int parent, int c) {
    if (cycle) {
        return;
    }
    colors[node] = c;
    for (int i = 0; i < (int)G[node].size(); i ++) {
        int neighbor = G[node][i];
        if (colors[neighbor] == c) {
            cycle = true;
            break;
        }
        if (colors[neighbor] == -1) {
            dfs(neighbor, node, 1 - c);
        }
    }
}
bool bipartiteColorableviaDFS(graph G) {
    cycle = false;
    colors = vector<int>(N, -1);
    for (int i = 0; i < N; i ++) {
        if (colors[i] == -1) {
            dfs(i, -1, 0);
        }
    }
    return cycle;
}
bool bipartiteColorableviaBFS(graph G) {
    bool cycle = false;
    colors = vector<int>(N, -1);
    for (int i = 0; i < N; i ++) {
        if (cycle == true) {
            break;
        }
        if (colors[i] != -1) {
            continue;
        }
        queue<int> Q;
        colors[i] = 0;
        Q.push(i);
        while (!Q.empty()) {
            int current = Q.front();
            Q.pop();
            for (int j = 0; j < (int)G[current].size(); j ++) {
                int neighbor = G[current][neighbor];
                if (colors[neighbor] == colors[current]) {
                    cycle = true;
                    break;
                }
                if (colors[neighbor] == -1) {
                    colors[neighbor] = colors[current] ^ 1;
                    Q.push(neighbor);
                }
            }
        }
    }
    return cycle;
}

int main(int argv, char** argc) {
    char* filename = argc[1];
    char* method = argc[2];
    //filename = "./data/gc_4_1";
    //freopen(filename.c_str(), "r", stdin);
    freopen(filename, "r", stdin);
    
    cin >> N >> M;
    G.resize(N);
    for (int i = 0; i < M; i ++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    string sm(method);
    transform(sm.begin(), sm.end(), sm.begin(), ::toupper);
    //cout << sm << endl;
    
    
    if (sm == "DFS") {
        cycle = bipartiteColorableviaDFS(G);
    }
    else {
        cycle = bipartiteColorableviaBFS(G);
    }
    if (cycle) {
        cout << "Graph can not be bicolored due to odd cycle." << endl;
    } else {
        cout << "Graph is bicolorable." << endl;
//        for (int i = 0; i < N; i ++) {
//            cout << "color of node i = " << i << " is " << colors[i] << endl;
//        }
    }
    
    return 0;
}
