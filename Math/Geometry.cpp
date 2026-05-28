/*
Points & Vectors — sq, dot, cross, sgn, isPerp, prep
Transformations — translate, scale, rot, linearTransfo
Angles — orient, angle, orientedAngle, angleTravelled, inAngle
Lines — line struct (side, dist, sqDist, proj, refl, shiftLeft, ...), inter, bisector
Segments — inDisk, onSegment, properInter, inters, segPoint, segSeg
Polygons — areaTriangle, areaPolygon, inPolygon
*/
typedef ld T;
typedef complex<T> pt;
#define x real()
#define y imag()

// Returns the squared magnitude (length^2) of point/vector p.
T sq(pt p){
    return p.x * p.x + p.y * p.y;
}

// Returns the dot product of vectors v and w.
T dot(pt v, pt w){
    return v.x * w.x + v.y * w.y;
}

// Returns the 2D cross product of vectors v and w (signed area of parallelogram).
T cross(pt v, pt w){
    return v.x * w.y - v.y * w.x;
}

// Returns the sign of a value: +1, -1, or 0 (within EPS tolerance).
int sgn(T val){
    if(val > EPS) return 1;
    if(val < -EPS) return -1;
    return 0;
}

// Checks if vectors v and w are perpendicular ( عمودي يعني ) (dot product => 0).
bool isPerp(pt v, pt w){
    return fabs(dot(v, w)) < EPS;
}

// Returns a vector perpendicular to p (rotated 90° CCW).
pt prep(pt p){
    return {-p.y, p.x};
}

//////////////// TRASFORMATIONS ////////////////////////

// Translates point p by vector v.
pt translate(pt v, pt p) {return p+v;}

// Scales point p around center c by the given factor.
pt scale(pt c, ld factor, pt p) {
    return c + (p-c)*factor;
}

// Rotates point p around center c by angle a (in radians).
pt rot(pt p, pt c, ld a){
    pt v = p - c;
    pt rotate = {cos(a), sin(a)};
    return c + rotate * v;
}

// Applies a linear transformation mapping segment [p,q] to [fp,fq], then transforms point r.
pt linearTransfo(pt p, pt q, pt r, pt fp, pt fq) {
    return fp + (r-p) * (fq-fp) / (q-p);
}

/////////////// Angles //////////////////////////

// CCW ==> Counter ClockWise عكس عقارب الساعة
// CW  ==> ClockWise مع عقارب الساعة
// Returns twice the 2 * (signed) area of triangle (a,b,c); positive = CCW, negative = CW.
T orient(pt a, pt b, pt c){
    return cross(b - a, c - a);
}

// Returns the unsigned angle (in radians) between vectors v and w ( range from 0 to 180 )
T angle(pt v, pt w){
    return acos(clamp(dot(v, w) / abs(v) / abs(w), (T)-1.0, (T)1.0));
}

// Returns the oriented angle from ray (a→b) to ray (a→c), measured CCW in [0, 2π).
T orientedAngle(pt a, pt b, pt c){
    ld ampli = angle(b - a, c - a);
    if(orient(a, b, c) > 0) return ampli;
    else return 2 * M_PI - ampli;
}

// Returns the signed angle from ray (a→b) to ray (a→c); positive = CCW, negative = CW.
T angleTravelled(pt a, pt b, pt c){
    ld ampli = angle(b - a, c - a);
    if(orient(a, b, c) > 0) return ampli;
    else return -ampli;
}

// Checks if point p lies inside the angle ∠BAC (going CCW from AB to AC).
bool inAngle(pt a, pt b, pt c, pt p) {
    T abp = orient(a, b, p), acp = orient(a, c, p), abc = orient(a, b, c);
    if (abc < 0) swap(abp, acp);
    return (abp >= 0 && acp <= 0) ^ (abc < 0);
}

struct line{
    pt v; T c;

    line(pt v, T c) : v(v), c(c) {}

    // Constructs a line from equation ax + by = c.
    line(T a, T b, T _c){
        v = {b, -a};
        c = _c;
    }

    // Constructs a line passing through two points p and q.
    line(pt p, pt q){
        v = q - p;
        c = cross(v, p);
    }

    // Returns signed distance (side) of point p from the line (unnormalized).
    T side(pt p) {return cross(v,p)-c;}

    // Returns the true perpendicular distance from point p to the line.
    ld dist(pt p) {return abs(side(p)) / abs(v);}

    // Returns the squared perpendicular distance from point p to the line.
    double sqDist(pt p) {return side(p)*side(p) / (T)sq(v);}

    // Returns the line perpendicular to this one passing through point p.
    line prepThrought(pt p){ return {p, p + prep(v)};}

    // Compares the projections of p and q along the line direction.
    bool cmpProj(pt p, pt q){
        return dot(v, p) < dot(v, q);
    }

    // Returns a translated copy of this line shifted by vector t.
    line translate(pt t) {return {v, c + cross(v,t)};}

    // Returns a parallel line shifted left by the given perpendicular distance.
    line shiftLeft(T dist) {return {v, c + dist*abs(v)};}

    // Returns the orthogonal projection of point p onto the line.
    pt proj(pt p) {return p - prep(v)*side(p)/sq(v);}

    // Returns the reflection of point p across the line.
    pt refl(pt p) {return p - prep(v) * (T)2.0 * side(p)/sq(v);}
};

// Finds the intersection point of two non-parallel lines; returns false if parallel.
bool inter(line l1, line l2, pt &out) {
    T d = cross(l1.v, l2.v);
    if (fabs(d) < EPS) return false;
    out = (l2.v*l1.c- l1.v*l2.c) / d;
    return true;
}

// Returns the interior or exterior angle bisector of two intersecting lines.
line bisector(line l1, line l2, bool interior) {
    assert(cross(l1.v, l2.v) != 0);
    ld sign = interior ? 1 :-1;
    return {l2.v/abs(l2.v) + l1.v/abs(l1.v) * sign,
            l2.c/abs(l2.v) + l1.c/abs(l1.v) * sign};
}

//////////////////////////////////////////  SEGMENTS   //////////////////////////////////////////

// Checks if point p lies inside or on the disk with diameter [a,b].
bool inDisk(pt a, pt b, pt p) {
    return dot(a-p, b-p) <= EPS;
}

// Checks if point c lies exactly on segment [a,b] .
bool onSegment(pt a, pt b, pt c){
    return orient(a, b, c) == 0 && inDisk(a, b, c);
}

// Returns true if segments [a,b] and [c,d] properly intersect (not at endpoints), and outputs the intersection point.
bool properInter(pt a, pt b, pt c, pt d, pt &out) {
    T oa = orient(c,d,a), ob = orient(c,d,b), oc = orient(a,b,c), od = orient(a,b,d);
    if (sgn(oa)*sgn(ob) < 0 && sgn(oc)*sgn(od) < 0) {
        out = (a*ob - b*oa) / (ob-oa);
        return true;
    }
    return false;
}

// Returns all intersection points between segments [a,b] and [c,d] (handles all cases including overlap).
set<pair<ld,ld>> inters(pt a, pt b, pt c, pt d) {
    set<pair<ld,ld>> s;
    pt out;
    if(a == c || a == d){
        s.insert(make_pair(a.x, a.y));
    }
    if(b == c || b == d){
        s.insert(make_pair(b.x, b.y));
    }
    if(s.size()) return s;

    if (properInter(a,b,c,d,out)) return {make_pair(out.x, out.y)};
    if (onSegment(c,d,a)) s.insert(make_pair(a.x, a.y));
    if (onSegment(c,d,b)) s.insert(make_pair(b.x, b.y));
    if (onSegment(a,b,c)) s.insert(make_pair(c.x, c.y));
    if (onSegment(a,b,d)) s.insert(make_pair(d.x, d.y));

    return s;
}

// Returns the minimum distance from point p to segment [a,b].
ld segPoint(pt a, pt b, pt p) {
    if (a != b) {
        line l(a,b);
        if (l.cmpProj(a,p) && l.cmpProj(p,b))
            return l.dist(p);
    }
    return min(abs(p-a), abs(p-b));
}

// Returns the minimum distance between two segments [a,b] and [c,d].
ld segSeg(pt a, pt b, pt c, pt d) {
    pt dummy;
    if (properInter(a,b,c,d,dummy))
        return 0;
    return min({segPoint(a,b,c), segPoint(a,b,d), segPoint(c,d,a), segPoint(c,d,b)});
}

////////////////////// polygons ////////////////////////////

// Returns the area of triangle (a,b,c).
ld areaTriangle(pt a, pt b, pt c) {
    return abs(cross(b-a, c-a)) / 2.0;
}

// Returns the area of a polygon given its vertices in order (CW or CCW).
ld areaPolygon(vector<pt> p) {
    ld area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++) {
        area += cross(p[i], p[(i+1)%n]);
    }
    return abs(area) / 2.0;
}

// Checks if point p is strictly above (or on) the horizontal ray from a.
bool above(pt a, pt p) {
    return p.y >= a.y;
}

// Checks if segment [p,q] crosses the horizontal ray cast rightward from point a.
bool crossesRay(pt a, pt p, pt q) {
    return (above(a,q)- above(a,p)) * orient(a,p,q) > 0;
}

// Checks if point a is inside polygon p using ray casting; strict=true excludes boundary.
bool inPolygon(vector<pt> p, pt a, bool strict = true) {
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i+1)%n], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[(i+1)%n]);
    }
    return numCrossings & 1;
}

vector < pt > convexHull( vector < pt > pts )
{
    int n = pts.size();
    if( n < 2 ) return pts;
    // first we need (x,y) y is lowest ( if y1 == y2 ==> take lowesr x )
    int idx = 0;
    for(int i = 1 ; i < n ; i++)
    {
        if( (pts[i].y < pts[idx].y) or ( pts[i].y == pts[idx].y and pts[i].x < pts[idx].x ))
        {
           idx = i;
        }
    }
    swap( pts[0] , pts[idx] );
    pt st = pts[0];
    // Sort by polar angle with respect to pivot
    sort(pts.begin() + 1, pts.end(), [&](pt a, pt b) {
        T cr = cross(a - st, b - st);
        if (fabs(cr) > EPS)
            return cr > 0; // a comes before b if CCW turn
        return sq(a - st) < sq(b - st); // closer point first if collinear
    });
    // Graham's
    vector < pt > ans;
    for( auto &p : pts )
    {
        while( ans.size() >= 2 and orient( ans[ ans.size() - 2 ] , ans[ ans.size() - 1 ] , p ) <= 0 ) ans.pop_back();
        ans.push_back(p);
    }
    return ans;
}

T diameterSq(vector<pt>& hull) {
    int n = hull.size();
    if (n == 1) return 0;
    if (n == 2) return sq(hull[1] - hull[0]);
    T Max = 0;
    int j = 1;
    for (int i = 0; i < n; i++) 
    {
        pt A = hull[i], B = hull[(i+1) % n];
        while (cross(B - A, hull[(j+1) % n] - hull[j]) > 0) j = (j + 1) % n;
        Max = max( Max, sq(hull[j] - hull[i]) );
        Max = max( Max, sq(hull[j] - hull[(i+1)%n]) );
    }
    return Max;
}
