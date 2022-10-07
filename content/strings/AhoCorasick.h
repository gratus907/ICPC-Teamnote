/**
 * Source: My implementation
 * Status: stress-tested
 */
struct Trie {
    int score = 0, id = 0;
    string prefix;
    Trie *next[26];
    Trie *fail;
    Trie(string s) {
        score = 0;
        id = trie_node_list.size();
        prefix = s;
        memset(next, 0, sizeof(next));
        trie_node_list.push_back(this);
    }
    void insert(string &s, int p) {
        if (p >= s.length())
            return;
        else {
            int cur = s[p] - 'A';
            if (next[cur] == NULL) {
                string nxt_str = prefix;
                nxt_str.push_back(s[p]);
                next[cur] = new Trie(nxt_str);
            }
            next[cur]->insert(s, p+1);
        }
    }
};
Trie* root = new Trie("");

Trie* follow(Trie* node, int ind) {
    Trie* u = node;
    while (u != root && !u->next[ind])
        u = u -> fail;
    if (u -> next[ind])
        u = u -> next[ind];
    return u;
}

void build_failure_links() {
    queue<Trie*> q;
    root->fail = root;
    q.push(root);
    while (!q.empty()) {
        Trie *cur = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            Trie *nxt = cur->next[i];
            if (!nxt) continue;
            if (cur == root) nxt->fail = root;
            else {
                Trie * prev = cur -> fail;
                prev = follow(prev, i);
                nxt->fail = prev;
            }
            q.push(nxt);
        }
    }
}

bool match(string text) {
    Trie* current = root;
    bool result = false;
    for(char _c : text){
        int c = _c - 'a';
        while(current != root && !current->next[c])
            current = current->fail;
        // move if next node is present.
        if(current->next[c])
            current = current->next[c];
        // found output!
        if(current->output){
            result = true;
            break;
        }
    }
}