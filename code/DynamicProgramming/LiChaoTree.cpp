/*
    Objective
    (1) Line insert query (ax + b)
    (2) Max / Min on x = t query
    Current Implementation : Max query
*/
struct LiChao
{
    struct Line // Linear function ax + b
    {
        int a, b;
        int eval(int x)
        {
            return a*x + b;
        }
    };
    struct Node // [start, end] has line f
    {
        int left, right;
        int start, end;
        Line f;
    };

    Node new_node(int a, int b)
    {
        return {-1,-1,a,b,{0,-INF}};
        // for min, change -INF to INF
    }

    vector <Node> nodes;

    void init(int min_x, int max_x)
    {
        nodes.push_back(new_node(min_x, max_x));
    }
    void insert(int n, Line new_line)
    {
        int xl = nodes[n].start, xr = nodes[n].end;
        int xm = (xl + xr)/2;
        Line llo, lhi;
        llo = nodes[n].f, lhi = new_line;
        if (llo.eval(xl) >= lhi.eval(xl))
            swap(llo, lhi);
        if (llo.eval(xr) <= lhi.eval(xr))
        {
            nodes[n].f = lhi;
            // for min, lhi -> llo
            return;
        }
        else if (llo.eval(xm) > lhi.eval(xm))
        {
            nodes[n].f = llo;
            // for min, llo -> lhi
            if (nodes[n].left == -1)
            {
                nodes[n].left = nodes.size();
                nodes.push_back(new_node(xl,xm));
            }
            insert(nodes[n].left, lhi);
            // for min, lhi -> llo
        }
        else
        {
            nodes[n].f = lhi;
            // for min, lhi -> llo
            if (nodes[n].right == -1)
            {
                nodes[n].right = nodes.size();
                nodes.push_back(new_node(xm+1,xr));
            }
            insert(nodes[n].right,llo);
            // for min, llo -> lhi
        }
    }
    void insert(Line f)
    {
        insert(0, f);
    }
    int get(int n, int q)
    {
        // for min, max -> min, -INF -> INF
        if (n == -1) return -INF;
        int xl = nodes[n].start, xr = nodes[n].end;
        int xm = (xl + xr)/2;
        if (q > xm)
            return max(nodes[n].f.eval(q), get(nodes[n].right, q));
        else return max(nodes[n].f.eval(q), get(nodes[n].left, q));
    }
    int get(int pt)
    {
        return get(0, pt);
    }
};
