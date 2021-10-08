/**
 * Source: kks227 Aho Corasick
 * Status: stress-tested
 */
const int MAX_SIZE = 202020;
const char BASE_CHAR = 'a';

struct Node
{
    Node* nxt[26];
    Node* fail;
    bool out;
    Node()
    {
        fill(nxt, nxt+26, nullptr);
        out = false;
    }
    ~Node()
    {
        for (int i = 0; i<26; i++)
            if (nxt[i])
                delete nxt[i];
    }

    void insert(const char *key)
    {
        if (*key == '\0')
        {
            out = true;
            return;
        }
        int c = *key - BASE_CHAR;
        if (!nxt[c])
            nxt[c] = new Node;
        nxt[c]->insert(key+1);
    }

};

struct Trie
{
    Node *root;
    Trie() {root = new Node;}
    void insert(const char *key)
    {
        root->insert(key);
    }
    Node * follow(Node *nd, int ind)
    {
        Node * u = nd;
        while (u != root && !u->nxt[ind])
            u = u -> fail;
        if (u -> nxt[ind])
            u = u -> nxt[ind];
        return u;
    }
    void build()
    {
        queue<Node*> q;
        root->fail = root;
        q.push(root);
        while (!q.empty())
        {
            Node *cur = q.front();
            q.pop();
            for (int i = 0; i<26; i++)
            {
                Node *nxt = cur->nxt[i];
                if (!nxt) continue;
                if (cur == root) nxt->fail = root;
                else
                {
                    Node * prev = cur -> fail;
                    prev = follow(prev, i);
                    nxt->fail = prev;
                }
                if (nxt->fail->out) nxt->out = true;
                q.push(nxt);
            }
        }
    }
    bool find(const char* str)
    {
        Node * rt = root;
        for (int i = 0; str[i]; i++)
        {
            int c = str[i]-BASE_CHAR;
            rt = follow(rt, c);
            if (rt->out)
                return true;
        }
        return false;
    }
} T;