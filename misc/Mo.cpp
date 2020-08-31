// dependency :
// Mo's Algorithm
// Time Complexity : O((N+Q) sqrt N T(N))

struct Query{
    int s, e, x;
    bool operator < (const Query &t) const {
        return tie(s/400, e) < tie(t.s/400, t.e);
    }
};

while(qry[i].s < l) insert(--l);
while(qry[i].e > r) insert(++r);
while(qry[i].s > l) erase(l++);
while(qry[i].e < r) erase(r--);
res[qry[i].x] = get();