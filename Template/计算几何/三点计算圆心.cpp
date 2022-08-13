// 三点 算圆心
const double eps = 1e-10;
struct Point {
    double x, y;
    bool operator<(const Point& oth)const {
        if (x != oth.x)
            return x < oth.x;
        return y < oth.y;
    }
    bool operator==(const Point& oth)const {
        return (fabs(x - oth.x) < eps) && (fabs(y - oth.y) < eps);
    }
};

Point P[2001];

bool cal_center(Point A, Point B, Point C, Point& res) {
    double a1 = A.x, a2 = B.x, a3 = C.x, b1 = A.y, b2 = B.y, b3 = C.y;
    double x = (b1 - b3) * (a1 * a1 - a2 * a2 + b1 * b1 - b2 * b2) - (b1 - b2) * (a1 * a1 - a3 * a3 + b1 * b1 - b3 * b3);
    x /= 2.0 * (a1 - a2) * (b1 - b3) - 2.0 * (a1 - a3) * (b1 - b2);
    double y = (a1 - a3) * (a1 * a1 - a2 * a2 + b1 * b1 - b2 * b2) - (a1 - a2) * (a1 * a1 - a3 * a3 + b1 * b1 - b3 * b3);
    y /= 2.0 * (a1 - a2) * (b1 - b3) - 2.0 * (a1 - a3) * (b1 - b2);

    double k1 = (a2 - a1) / (b2 - b1);
    double k2 = (a3 - a2) / (b3 - b2);
    if (fabs(k1 - k2) < eps) {
        return false;
    }

    res.x = x; res.y = y;
    return true;


}