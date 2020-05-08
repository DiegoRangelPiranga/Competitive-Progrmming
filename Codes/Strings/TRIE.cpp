struct no{
  bool end;
  int cnt;
  no *g[27];
  no(){
    cnt = 1;
    end = false;
    for(int i = 0; i < 27; i++)
      g[i] = NULL;
  }
};

no* Trie;

void add(string s){
  no *p = Trie;
  for(auto i : s){
    int u = i-'a';
    if(p->g[u] == NULL)
      p->g[u] = new no();
    else
      p->g[u]->cnt++;
    p = p->g[u];
  }
  p->end = true;
}
