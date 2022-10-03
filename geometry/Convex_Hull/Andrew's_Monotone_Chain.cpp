using Polygon = vec<Point>;

Polygon getConvexHull(Polygon poly) {
    sort(poly.begin(), poly.end());
    
    Polygon hull;
    hull.reserve(poly.size() + 1);
    for (int round = 0; round < 2; round++) {
        int start = hull.size();
        for (Point &pt: poly) {
            while (hull.size() - start >= 2 && Line(hull[hull.size() - 2], hull[hull.size() - 1]).ori(pt) <= 0) 
                hull.pop_back();
                
            hull.emplace_back(pt);
        }
        
        hull.pop_back();
        
        reverse(poly.begin(), poly.end());
    }
    
    if (hull.size() == 2 && hull[0] == hull[1])
        hull.pop_back();
        
    return hull;
}