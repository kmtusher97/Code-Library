ll tree[MX_N];

void update( int id, ll vlu )
{
  for(; id <= n; tree[id] += vlu, id += (id & -id));
}

ll query( int id )
{
  ll ret = 0;
  for(; id > 0; ret += tree[id], id -= (id & -id));
  return ret;
}

/*-------------------------------------------------------*/

template <class T> class Fenwick_tree
{
private:
  int n;
  vector<T> tree;

public:
  Fenwick_tree()
  {
    n = 0, tree.clear();
  }
  Fenwick_tree( int _n )
  {
    n = _n;
    tree = vector<T> (n + 2, 0);
  }
  void update( int id, T vlu )
  {
   for(; id <= n; tree[id] += vlu, id += (id & -id));
  }
  T query( int id )
  {
    T ret = 0;
    for(; id > 0; ret += tree[id], id -= (id & -id));
    return ret;
  }
};


