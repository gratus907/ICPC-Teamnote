vector<int> getPi(string p) {
	int j = 0, plen = p.length();
	vector<int> pi;
	pi.resize(plen);
	for(int i = 1; i< plen; i++) {
		while((j > 0) && (p[i] !=  p[j]))
			j = pi[j-1];
		if(p[i] == p[j]) {
			j++;
			pi[i] = j;
		}
	}
	return pi;
}
vector <int> kmp(string s, string p) {
	vector<int> ans;
	auto pi = getPi(p);
	int slen = s.length(), plen = p.length(), j = 0;
	for(int i = 0 ; i < slen ; i++)	{
		while(j>0 && s[i] != p[j])
			j = pi[j-1];
		if(s[i] == p[j]) {
			if(j==plen-1) {
				ans.push_back(i-plen+1);
				j = pi[j];
			}
			else
				j++;
		}
	}
	return ans;
}
