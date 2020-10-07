int modpow(int x, int y, int p = mod)
{
    int res = 1;
    x = x % p;
    while (y > 0)
    {
        if (y & 1)
            res = (res*x) % p;
        y = y>>1;
        x = (x*x) % p;
    }
    return res;
}

int fact[MAX_N+5];
int invfact[MAX_N+5];

int binom(int n, int r)
{
    int t = (fact[n]*(invfact[r]))%mod;
    return (t*invfact[n-r])%mod;
}

void precompute()
{
    fact[0] = 1; invfact[0] = 1;
    for (int i = 1; i<=MAX_N; i++)
    {
        fact[i] = fact[i-1]*i;
        fact[i] %= mod;
    }
    invfact[MAX_N] = modpow(fact[MAX_N],mod-2);
    for (int i = MAX_N-1; i>=1; i--)
    {
        invfact[i] = invfact[i+1]*(i+1);
        invfact[i] %= mod;
    }
}
