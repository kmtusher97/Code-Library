vector<int> dist( V, INF );    // initialize dist with inf
dist[s] = 0;          //s = source

priority_queue< pii, vector<pii>, greater<pii> > pq;
pq.push({0, s});

while( !pq.empty() )
{
  pii front = pq.top();
  pq.pop();
  int d = front.first;
  int u = front.second;
  if( d > dist[u] )
    continue;     // optimization

  for(int i = 0; i < G[u].size(); i++)
  {
    pii v = G[u][j];
    if( dist[u] + v.second < dist[v.first] )
    {
      dist[v.first] = dist[u] + v.second; // relax
      pq.push({dist[v.first], v.first});
    }
  }
}
