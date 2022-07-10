template <typename T>
T ClosestPairSquareDistance(typename vector<Point<T>>::iterator l,
                            typename vector<Point<T>>::iterator r)
{
    auto delta = numeric_limits<T>::max();
    if (r - l > 1)
    {
        auto m = l + (r - l >> 1);
        nth_element(l, m, r); // Lexicographical order in default
        auto x = m->x;
        delta = min(ClosestPairSquareDistance<T>(l, m),
                    ClosestPairSquareDistance<T>(m, r));
        auto square = [&](T y) { return y * y; };
        auto sgn = [=](T a, T b) {
            return square(a - b) <= delta ? 0 : a < b ? -1 : 1;
        };
        vector<Point<T>> x_near[2];
        copy_if(l, m, back_inserter(x_near[0]), [=](Point<T> a) {
            return sgn(a.x, x) == 0;
        });
        copy_if(m, r, back_inserter(x_near[1]), [=](Point<T> a) {
            return sgn(a.x, x) == 0;
        });
        for (int i = 0, j = 0; i < x_near[0].size(); ++i)
        {
            while (j < x_near[1].size() and
                   sgn(x_near[1][j].y, x_near[0][i].y) == -1)
                ++j;
            for (int k = j; k < x_near[1].size() and
                            sgn(x_near[1][k].y, x_near[0][i].y) == 0;
                 ++k)
            {
                delta = min(delta, (x_near[0][i] - x_near[1][k]).norm());
            }
        }
        inplace_merge(l, m, r, [](Point<T> a, Point<T> b) {
            return a.y < b.y;
        });
    }
    return delta;
}