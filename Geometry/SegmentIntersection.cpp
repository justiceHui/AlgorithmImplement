// dependency : ./BaseTool.cpp
// line cegment intersection test
// Time Complexity : O(1), Space Complexity : O(1)

bool segment_crash(p a, p b, p c, p d){
	int ab = ccw(a, b, c) * ccw(a, b, d);
	int cd = ccw(c, d, a) * ccw(c, d, b);
	if(!ab && !cd){
		if(a > b) swap(a, b);
		if(c > d) swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}