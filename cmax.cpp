#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
 
constexpr bool typetest = 0;
constexpr int N = 1e5 + 5;
constexpr int Inf = 1e9 + 7;
 
int n, id[N];
ll a[N], b[N];
 
struct CHT
{
    vector<ld> Point; // Hoành độ của giao điểm
    vector<int> Line; // chỉ số của đường thẳng bắt đầu tại điểm tương ứng
 
    CHT()
    {
        Point.emplace_back(-Inf);
    }
 
    ld intersect(int x, int y)
    {
        return (ld) 1.0 * (b[x] - b[y]) / (a[y] - a[x]);
    }
 
    void Add(int id)
    {
        while(Line.size() > 1 || (Line.size() == 1 && a[Line.back()] == a[id]))
        {
            if(a[Line.back()] == a[id])
            {
                if(b[Line.back()] < b[id])
                {
                    Line.pop_back();
 
                    if(!Line.empty())
                        Point.pop_back();
                }
                else
                    break;
            }
            else
            {
                if(intersect(id, Line.back()) <= Point.back())
                {
                    Line.pop_back();
 
                    if(!Line.empty())
                        Point.pop_back();
                }
                else
                    break;
            }
        }
 
 
        if(Line.empty() || a[Line.back()] != a[id])
        {
            if(!Line.empty())
            {
                Point.emplace_back(intersect(id, Line.back()));
            }
            Line.emplace_back(id);
        }
    }
 
    ll Get(ll v)
    {
        // Tìm max (av + b)
 
        int j = lower_bound(Point.begin(), Point.end(), v) - Point.begin();
        return a[Line[j - 1]] * v + b[Line[j - 1]];
    }
};
 
CHT f;
 
void Read()
{
    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> a[i] >> b[id[i] = i];
}
 
void Solve()
{
    sort(id + 1, id + n + 1, [&](const int &x, const int &y){
        return a[x] < a[y];
    });
 
    for(int i = 1; i <= n; ++i)
        f.Add(id[i]);
 
    int q;
    cin >> q;
 
    while(q--)
    {
        ll x;
        cin >> x;
        cout << f.Get(x) << "\n";
    }
}
 
int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    if (fopen("tests.inp", "r"))
    {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
 
    int t(1);
    if (typetest)
        cin >> t;
 
    for (int _ = 1; _ <= t; ++_)
    {
        // cout << "Case #" << _ << endl;
        Read();
        Solve();
    }
}
