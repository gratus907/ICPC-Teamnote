/**
 * Author: Gratus907
 * Date: 2020-10-08
 * License: CC0
 * Source: 
 * Description: For NTT, change second loop of above FFT Code as:
 * Time: O(N \log N)
 * Status: 
 */

vector<base> root(n/2); 
int ang = modpow(3, (mod - 1) / n); 
if(invert) ang = modpow(ang, mod - 2); 
root[0] = 1; 
for(int i = 1; i<n/2; i++) 
    root[i] = (root[i-1]*ang)%mod; 
for (int len = 2; len <= n; len <<= 1)
{ 
    int step = n / len; 
    for (int i = 0; i<n; i+= len) 
    { 
        for (int j = 0; j<len/2; j++) 
        { 
            base u = a[i+j], v = (a[i+j+len/2]*root[step*j])%mod;
            a[i+j] = (u+v)%mod; 
            a[i+j+len/2] = (u-v)%mod; 
        } 
    } 
} 
if (invert) 
{ 
    for (int i = 0; i<n; i++) 
        a[i] = frac(a[i],n); 
} 
for (int i = 0; i<n; i++) 
    a[i] = (a[i]+10*mod)%mod;
