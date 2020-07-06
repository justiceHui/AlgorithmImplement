// dependency : ./BaseTool.cpp
// get farthest pair in 2D
// Time Complexity : O(N), Space Complexity : O(N)
// input : convex hull, output : {p1, p2}

bool cali_chk(const p &s1, const p &e1, const p &s2, const p &e2){
    p t1 = make_pair(e1.x - s1.x, e1.y - s1.y);
    p t2 = make_pair(e2.x - s2.x, e2.y - s2.y);
    return ccw(p(0, 0), t1, t2) >= 0;
}
pair<p, p> rotating_calipers(const vector<p> &hull){
    auto n = hull.size(); int pv = 0;
    ll mx = 0; p a, b;
    for(int i=0; i<n; i++){
        while(pv+1 < n && cali_chk(hull[i], hull[i+1], hull[pv], hull[pv+1])){
            ll now = dst(hull[i], hull[pv]);
            if(mx < now){ mx = now; a = hull[i], b = hull[pv]; }
            pv++;
        }
        ll now = dst(hull[i], hull[pv]);
        if(mx < now){ mx = now; a = hull[i], b = hull[pv]; }
    }
    return make_pair(a,b);
}