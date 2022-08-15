// Andrew's Monotone Chiain
template <class F>
using Polygon = vector<Point<F>>;

template <class F>
Polygon<F> getConvexHull(Polygon<F> points)
{
    sort(begin(points), end(points));
    Polygon<F> hull;
    hull.reserve(points.size() + 1);
    for (int phase = 0; phase < 2; ++phase)
    {
        auto start = hull.size();
        for (auto &point : points)
        {
            while (hull.size() >= start + 2 &&
                   Line<F>(hull[hull.size()-2], hull[hull.size() - 1]).ori(point) <= 0)
                hull.pop_back();
            
            // whenever point is at the RIGHT(NEGATIVE) part of the line(hull[size - 1], hull[size-2])
            // pop the last point because it causes concave hull
            hull.push_back(point);
        }
        hull.pop_back();
        reverse(begin(points), end(points));
    }
    if (hull.size() == 2 and hull[0] == hull[1])
        hull.pop_back();
    return hull;
}
