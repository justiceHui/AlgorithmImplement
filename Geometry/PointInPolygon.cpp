// dependency : ./SegmentIntersection.cpp
// point in polygon test
// Time Complexity : O(N)
// input : (sorted polygon, point)

const ll MAX_COORD = 1e15;
bool pip(const vector<p> &v, p p1){
    int n = v.size(), cnt = 0;
    p p2 = p(MAX_COORD+1, p1.y+1);
    for(int i=0; i<n; i++){
        int j = i+1 == n ? 0 : i+1;
        if(!ccw(v[i], v[j], p1) && min(v[i], v[j]) <= p1 && p1 <= max(v[i], v[j])) return 1;
        cnt += segment_crash(v[i], v[j], p1, p2);
    }
    return cnt & 1;
}