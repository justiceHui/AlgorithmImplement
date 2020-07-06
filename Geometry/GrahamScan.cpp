// dependency : ./BaseTool.cpp
// get 2D convex hull
// Time Complexity : O(N log N), Space Complexity : O(N)

vector<p> convex_hull(vector<p> &v){
    vector<p> ret;
    swap(v[0], *min_element(all(v)));
    sort(v.begin()+1, v.end(), [&](const p &a, const p &b){
        auto cw = ccw(v[0], a, b);
        if(cw) return cw > 0;
        return dst(v[0], a) < dst(v[0], b);
    });
    for(const auto &i : v){
        while(ret.size() >= 2 && ccw(ret[ret.size()-2], ret.back(), i) <= 0) ret.pop_back();
        ret.push_back(i);
    }
    return ret;
}