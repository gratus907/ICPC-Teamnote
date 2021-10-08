/**
 * Author: DHDroid
 * Description: Manber Myers
 */
string s;
int length;
vector<int> idx;	
vector<int> rev_idx(500020, 0);
vector<int> group(500020, 0);

bool compare(int a, int b, int t) {
	if(group[a] != group[b])
		return group[a] < group[b];
	return group[a + (1<<t)] < group[b + (1<<t)];
}

void update_group(int t) {
	vector<int> new_group(500020, 0);
	new_group[idx[0]] = 0;
	for(int i=1; i<length; i++) {
		new_group[idx[i]] = new_group[idx[i-1]] + compare(idx[i-1], idx[i], t); 
	}
	group = new_group;
	group[length] = -1;
}

void manber_myers(string s) {
	length = s.length();
	
	// SA
	for(int i=0; i<length; i++) {
		idx.push_back(i);
	}
	sort(idx.begin(), idx.end(), [](int i, int j){
		return s[i] < s[j];
	});
	for(int i=0; i<length; i++) {
		group[idx[i]] = s[idx[i]];
	}
	for(int t=0; t<20; t++) {
		sort(idx.begin(), idx.end(), [&t](int i, int j){
			return compare(i, j, t);
		});
		update_group(t);
	}
	for(auto i: idx) {
		cout << i+1 << " ";
	}
	cout << "\n";

	// LCP
	vector<int> LCP(length, 0);
	for(int i=0; i<length; i++) {
		rev_idx[idx[i]] = i;
	}
	int h = 0;
	for(int i=0; i<length; i++) {
		if(rev_idx[i] == 0) {
			h=0;
			continue;
		}
		int prev = idx[rev_idx[i] - 1];
		while(s[i+h] == s[prev+h] && i+h < length && prev+h < length) {
			h++;
		}
		LCP[rev_idx[i]] = h;
		if(h > 0) {
			h--;
		}
	}
}