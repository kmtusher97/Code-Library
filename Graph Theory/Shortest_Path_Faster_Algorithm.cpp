/**
 * SPFA from Competitive Programming III Book
 */
/// inside int main()
/// initially, only S has dist = 0 and in the queue
vi dist(n, INF);
dist[S] = 0;
queue<int> q;
q.push(S);
vi in_queue(n, 0);
in_queue[S] = 1;
while (!q.empty())
{
    int u = q.front();
    q.pop();
    in_queue[u] = 0;
    for (j = 0; j < (int)AdjList[u].size(); j++)   /// all neighbors of u
    {
        int v = AdjList[u][j].first, weight_u_v = AdjList[u][j].second;
        if (dist[u] + weight_u_v < dist[v])   /// if can relax
        {
            dist[v] = dist[u] + weight_u_v; /// relax
            if (!in_queue[v])   /// add to the queue
            {
                q.push(v); /// only if it is not already in the queue
                in_queue[v] = 1;
            }
        }
    }
}
