#include <bits/stdc++.h>

#define FASTIO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define FOR(i, N) for(int i=1; i <= N; ++i)
#define NEG(i) (i > N ? i - N : i + N)
#define SET(i) (i < 0 ? N - i : i)
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef stack<int> si;

vvi v;
vi scc, id;
int N, M, cur_id{0};
//
//int dfs(int cur, int idx, si &s) {
//    id[cur] = ++cur_id;
//    s.push(cur);
//
//    int link = id[cur];
//
//    for (auto next: v[cur]) {
//        if (id[next] == 0) link = min(link, dfs(next, idx, s));
//        if (scc[next] == -1) link = min(link, id[next]);
//    }
//
//    if (link == id[cur]) {
//        while (true) {
//            int t = s.top();
//            s.pop();
//
//            scc[t] = idx;
//            if (t == cur) break;
//        }
//    }
//
//    return link;
//}

int dfs(int cur, int &idx, si &s){
    id[cur] = ++cur_id;
    s.push(cur);

    int link{id[cur]};
    for(int i : v[cur]){
        if(!id[i]) link = min(link, dfs(i, idx, s));
        if(scc[i] == -1) link = min(link, id[i]);
    }

    if(link == id[cur]){
        while(true){
            int t = s.top();
            s.pop();

            scc[t] = idx;
            if(t == cur) break;
        }
        ++idx;
    }

    return link;
}

void init() {
    v.clear();
    v.resize(2 * N + 10);

    scc.clear();
    scc.resize(2 * N + 10, -1);

    id.clear();
    id.resize(2 * N + 10);
}

bool check() {
    FOR(i, N) {
        if (scc[i] == scc[i + N]) return false;
    }
    return true;
}

int main() {
    FASTIO
    string s1, s2;
    int c1, c2;
    while (cin >> M >> N) {
        if(N == 0 && M == 0) break;
        init();

        FOR(i, M) {
            cin >> c1 >> c2;
//            cout << c1 << c2 << "\n";

            c1 = SET(c1), c2 = SET(c2);
            v[NEG(c1)].push_back(c2);
            v[NEG(c2)].push_back(c1);
        }

        int idx{1};
        stack<int> s;


        FOR(i, N) {
            if (!id[i]) dfs(i, idx, s);
        }

        cout << (check()) << "\n";
    }
}