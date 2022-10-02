// Miminimum Li Chao Tree
typedef long long ftype;
typedef complex<ftype> point;
#define x real
#define y imag

ftype dot(point a, point b) {
    return (conj(a) * b).x();
}

ftype f(point a,  ftype x) {
    return dot(a, {x, 1});
}

const int maxn = 2e5;

point line[4 * maxn];

/*
a line is  y = k * x + b, using point to represent it.
y = (k, b) * (x, 1) (dot operation).
*/
// y = nw.real() * x + nw.imag().
void add_line(point nw, int idx = 1, int l = 0, int r = maxn)
{
    int m = (l + r) / 2;
    bool lef = f(nw, l) < f(line[idx], l);
    bool mid = f(nw, m) < f(line[idx], m);
    if(mid) {
        swap(line[idx], nw);
    }
    if(r - l == 1) {
        return;
    } else if(lef != mid) {
        add_line(nw, 2 * idx, l, m);
    } else {
        add_line(nw, 2 * idx + 1, m, r);
    }
}

// get minimum in some point x;
ftype get(int x, int idx = 1, int l = 0, int r = maxn)
{
    int m = (l + r) / 2;
    if(r - l == 1) {
        return f(line[idx], x);
    } else if(x < m) {
        return min(f(line[idx], x), get(x, 2 * idx, l, m));
    } else {
        return min(f(line[idx], x), get(x, 2 * idx + 1, m, r));
    }
}
