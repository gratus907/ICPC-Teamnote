/**
 * Description: Simplest bipartite check
 */
vector <int> graph[20200];
vector <pair <int, int>> edge;
bool visited[202020];
int color[202020];

void dfs(int root)
{
    for (auto it:graph[root])
    {
        if (!visited[it])
        {
            visited[it] = true;
            color[it] = color[root]%2+1;
            dfs(it);
        }
    }
}
bool is_bipartite(vector <int> &mygraph, int v, int e)
{
    for (int i = 1; i<=v; i++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            color[i] = 1;
            dfs(i);
        }
    }
    for (int i = 0; i<e; i++)
        if (color[edge[i].first]==color[edge[i].second])
            return false;
    return true;
}