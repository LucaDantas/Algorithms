/**
 * Author: tdas
 * Description: Sort points by angle arround a chosen pivot, untied by distance.
 * ccw, starting at quadrant x>0,y<0.
 * Time: $O(N log(N))$
*/

sort(all(pts) , [&](P a , P b){
	a = a - pivot , b = b - pivot;
	int hp1 = a < P(0,0) , hp2 = b < P(0,0);
	if(hp1 != hp2) return hp1 < hp2;
	if(a.cross(b) != 0){
		return a.cross(b)  > 0;
	}
	return a.dist2() < b.dist2();
});
