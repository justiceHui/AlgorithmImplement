// dependency : ./BaseTool.cpp
// get 2D convex hull
// Time Complexity : O(N log N), Space Complexity : O(N)

vector<Point> ConvexHull(vector<Point> &V){
    swap(V[0], *min_element(all(V)));
    sort(V.begin()+1, V.end(), [&V](const Point &p1, const Point &p2){
        int cw = CCW(V[0], p1, p2);
        if(cw) return cw > 0;
        return D(V[0], p1) < D(V[0], p2);
    });
    vector<Point> hull;
    for(const auto &i : V){
        while(hull.size() >= 2 && CCW(hull[hull.size()-2], hull.back(), i) <= 0) hull.pop_back();
        hull.push_back(i);
    }
    return move(hull);
}