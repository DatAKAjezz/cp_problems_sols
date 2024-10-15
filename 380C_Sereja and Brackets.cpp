#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define pb emplace_back
#define F first
#define S second
#define fora(x, a) for(auto &x : a)
#define mp make_pair
#define inf 1000000007
#define maxn 1000005

struct Node{
    int opt;
    int open;
    int close;

    Node(int optimal = 0, int o = 0, int c = 0){
        opt = optimal;
        open = o;
        close = c;
    }
};


string s;
vector<Node> st(maxn * 4 + 1, Node(0,0,0));

Node operator + (const Node &left, const Node &right){
    
    Node res;
    int tmp = min(left.open, right.close);

    res.opt = left.opt + right.opt + tmp * 2;

    res.open = left.open + right.open - tmp;
    res.close = left.close + right.close - tmp;
    return res;
}

void build(int id, int l, int r){
    if (l == r){
        if (s[l] == '(') st[id] = Node(0,1,0);
        else st[id] = Node(0, 0, 1);
        return;
    }

    int mid = (l + r) >> 1;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);

    st[id] = st[id * 2] + st[id * 2 + 1];
}

Node get(int id, int l, int r, int u, int v){
    if (v < l || r < u){
        return Node(0,0,0);
    }
    if (u <= l && r <= v){
        return st[id];
    }

    int mid = (l + r) >> 1;
    return (get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v));
}

void solve(){

    cin >> s;
    int q; cin >> q;
    
    s = "#" + s;
    build(1, 1, s.size());

    while(q--){
        int u, v;
        cin >> u >> v;
        cout << get(1, 1, s.size(), u, v).opt << '\n';
    }

}

int main() {

    #ifndef ONLINE_JUDGE
    freopen(".inp", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif 

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int t; cin >> t;while(t--) 
    solve();

}