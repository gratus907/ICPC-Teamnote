/**
 * Author: Wonseok Shin
 * Date: 2022-07-21
 * Source: own work
 * Description: Rabin-Karp rolling hash, always use multiple modulos and bases when unsure.
 * Status: BOJ 1786
 */
vector <ll> RabinKarp(string &s, ll window, ll mod, ll p) {
    vector <ll> hash_values;
    ll cur = 0;
    ll hash_offset = 1;
    for (int i = 0; i < window; i++) {
        cur *= p;
        cur += s[i];
        cur %= mod;
        if (i > 0) hash_offset = (hash_offset * p)%mod;
    }
    hash_values.push_back(cur);
    for (int i = window; i < s.length(); i++) {
        cur = (mod + cur - (s[i-window] * hash_offset)%mod)%mod;
        cur = (cur * p + s[i]) % mod;
        hash_values.push_back(cur);
    }
    return hash_values;
}