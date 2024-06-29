typedef long long ll;
const ll mod = 1e9+7;
const ll maxn = 1e5 + 1;
ll fac[maxn], invfact[maxn];
ll power(ll x, ll y)
{
    ll res = 1;
    x = x % mod;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % mod;
        y = y >> 1;
        x = (x * x) % mod;
    }
    return res;
}
ll modInverse(ll n)
{
    return power(n, mod - 2);
}
ll NCR(ll n, ll r, ll p = mod)
{
    if (r < 0 || n < 0)
        assert(false);
    if (n < r)
        return 0;
    if (r == 0 || r == n)
        return 1;
    return (fac[n] * invfact[r] % mod) * invfact[n - r] % mod;
}
void compu()
{
    fac[0] = 1, invfact[0] = 1;
    for (ll i = 1; i < maxn; i++)
    {
        fac[i] = (fac[i - 1] * i) % mod;
        invfact[i] = modInverse(fac[i]);
    }
}
bool comp(const pair<int, char>& a, const pair<int, char>& b) 
    {
    if (a.first != b.first) {
        return a.first > b.first;
    }
    return a.second < b.second;
}
class Solution {
public:
    int countKSubsequencesWithMaxBeauty(string s, int k) {
        map<char,int> hsh;
        for(auto x:s)
            hsh[x]++;
        if(k>hsh.size())
            return 0;
        vector<pair<int,char>> vp;
        for(auto &[x,f] : hsh)
        {
            vp.push_back({f,x});
        }
        sort(vp.begin(),vp.end(),comp);
        long long ans=1;
        ll q = -1;
        for(int i=0;i<k;i++)
        {
            ans*=vp[i].first;
            ans %= mod;
            if(q==-1 && vp[i].first == vp[k-1].first)
                q = i;
        }
        ll r = k-1;
        while(r<vp.size() && vp[r].first==vp[k-1].first)
        {
            r++;
        }
        if(fac[0]!=1)
            compu();
        long long cas = NCR(r-q,k-q,mod);
        ans *= cas;
        ans %= mod;
        return (int)ans;
    }
};
