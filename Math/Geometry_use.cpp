void solve() {

    // ==================== Points & Vectors ====================
    pt a = {3, 4}, b = {1, 2};

    cout << sq(a) << nl;               // 25
    cout << dot(a, b) << nl;           // 11
    cout << cross(a, b) << nl;         // 2
    cout << sgn(-5) << nl;             // -1
    cout << isPerp(a, b) << nl;        // 0 (not perpendicular)
    cout << prep(a) << nl;             // (-4, 3)

    // ==================== Transformations ====================
    pt p = {1, 0}, center = {0, 0};

    cout << translate({2,3}, p) << nl;                            // (3, 1)
    cout << scale(center, 2.0, p) << nl;                          // (2, 0)
    cout << rot(p, center, M_PI / 2) << nl;                       // (0, 1)
    cout << linearTransfo({0,0},{1,0},{0.5,0},{0,0},{4,0}) << nl; // (2, 0)

    // ==================== Angles ====================
    pt o = {0,0}, px = {1,0}, py = {0,1};

    cout << orient(o, px, py) << nl;           // 1 (CCW)
    cout << angle(px, py) << nl;               // π/2
    cout << orientedAngle(o, px, py) << nl;    // π/2 (CCW)
    cout << angleTravelled(o, px, py) << nl;   // π/2 (positive = CCW)
    cout << inAngle(o, px, py, pt(1,1)) << nl; // 1 (inside angle)

    // ==================== Lines ====================
    line l1(pt(0,0), pt(4,0));  // line on X-axis
    line l3(pt(0,0), pt(0,4));  // line on Y-axis

    pt q = {2, 3};
    cout << l1.side(q) << nl;       // -3 (below line)
    cout << l1.dist(q) << nl;       // 3
    cout << l1.sqDist(q) << nl;     // 9
    cout << l1.proj(q) << nl;       // (2, 0)
    cout << l1.refl(q) << nl;       // (2, -3)

    pt inter_pt;
    inter(l1, l3, inter_pt);
    cout << inter_pt << nl;         // (0, 0)

    line bis = bisector(l1, l3, true);
    cout << bis.v << nl;            // bisector direction

    // ==================== Segments ====================
    pt s1 = {0,0}, s2 = {4,0};
    pt s3 = {2,-1}, s4 = {2,1};

    cout << inDisk(s1, s2, pt(1,0)) << nl;          // 1 (inside)
    cout << onSegment(s1, s2, pt(1,0)) << nl;        // 1 (on segment)

    pt out;
    cout << properInter(s1,s2,s3,s4,out) << nl;     // 1 (they intersect)
    cout << out << nl;                               // (2, 0)

    auto pts = inters(s1,s2,s3,s4);
    for(auto& pp : pts) cout << pp.first << " " << pp.second << nl;

    cout << segPoint(s1, s2, pt(2,3)) << nl;        // 3
    cout << segSeg(s1,s2,s3,s4) << nl;              // 0 (they intersect)

    // ==================== Polygons ====================
    vector<pt> poly = {pt(0,0), pt(4,0), pt(4,3), pt(0,3)}; // rectangle

    cout << areaTriangle(pt(0,0), pt(4,0), pt(0,3)) << nl;  // 6
    cout << areaPolygon(poly) << nl;                         // 12
    cout << inPolygon(poly, pt(2,1)) << nl;                  // 1 (inside)
    cout << inPolygon(poly, pt(5,5)) << nl;                  // 0 (outside)
    cout << inPolygon(poly, pt(4,0), false) << nl;           // 1 (on boundary)
}
